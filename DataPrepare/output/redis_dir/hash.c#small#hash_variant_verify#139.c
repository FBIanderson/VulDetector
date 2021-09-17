static void
hash_variant_verify(hash_variant_t variant) {
#define MAX_ALIGN	16
	uint8_t key[KEY_SIZE + (MAX_ALIGN - 1)];
	unsigned i;

	for (i = 0; i < MAX_ALIGN; i++) {
		hash_variant_verify_key(variant, &key[i]);
	}
#undef MAX_ALIGN
}
