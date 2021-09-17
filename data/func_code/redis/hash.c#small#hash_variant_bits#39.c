static int
hash_variant_bits(hash_variant_t variant) {
	switch (variant) {
	case hash_variant_x86_32: return 32;
	case hash_variant_x86_128: return 128;
	case hash_variant_x64_128: return 128;
	default: not_reached();
	}
}
