static void
hash_variant_verify_key(hash_variant_t variant, uint8_t *key) {
	const int hashbytes = hash_variant_bits(variant) / 8;
	const int hashes_size = hashbytes * 256;
	VARIABLE_ARRAY(uint8_t, hashes, hashes_size);
	VARIABLE_ARRAY(uint8_t, final, hashbytes);
	unsigned i;
	uint32_t computed, expected;

	memset(key, 0, KEY_SIZE);
	memset(hashes, 0, hashes_size);
	memset(final, 0, hashbytes);

	/*
	 * Hash keys of the form {0}, {0,1}, {0,1,2}, ..., {0,1,...,255} as the
	 * seed.
	 */
	for (i = 0; i < 256; i++) {
		key[i] = (uint8_t)i;
		switch (variant) {
		case hash_variant_x86_32: {
			uint32_t out;
			out = hash_x86_32(key, i, 256-i);
			memcpy(&hashes[i*hashbytes], &out, hashbytes);
			break;
		} case hash_variant_x86_128: {
			uint64_t out[2];
			hash_x86_128(key, i, 256-i, out);
			memcpy(&hashes[i*hashbytes], out, hashbytes);
			break;
		} case hash_variant_x64_128: {
			uint64_t out[2];
			hash_x64_128(key, i, 256-i, out);
			memcpy(&hashes[i*hashbytes], out, hashbytes);
			break;
		} default: not_reached();
		}
	}

	/* Hash the result array. */
	switch (variant) {
	case hash_variant_x86_32: {
		uint32_t out = hash_x86_32(hashes, hashes_size, 0);
		memcpy(final, &out, sizeof(out));
		break;
	} case hash_variant_x86_128: {
		uint64_t out[2];
		hash_x86_128(hashes, hashes_size, 0, out);
		memcpy(final, out, sizeof(out));
		break;
	} case hash_variant_x64_128: {
		uint64_t out[2];
		hash_x64_128(hashes, hashes_size, 0, out);
		memcpy(final, out, sizeof(out));
		break;
	} default: not_reached();
	}

	computed = (final[0] << 0) | (final[1] << 8) | (final[2] << 16) |
	    (final[3] << 24);

	switch (variant) {
#ifdef JEMALLOC_BIG_ENDIAN
	case hash_variant_x86_32: expected = 0x6213303eU; break;
	case hash_variant_x86_128: expected = 0x266820caU; break;
	case hash_variant_x64_128: expected = 0xcc622b6fU; break;
#else
	case hash_variant_x86_32: expected = 0xb0f57ee3U; break;
	case hash_variant_x86_128: expected = 0xb3ece62aU; break;
	case hash_variant_x64_128: expected = 0x6384ba69U; break;
#endif
	default: not_reached();
	}

	assert_u32_eq(computed, expected,
	    "Hash mismatch for %s(): expected %#x but got %#x",
	    hash_variant_string(variant), expected, computed);
}
