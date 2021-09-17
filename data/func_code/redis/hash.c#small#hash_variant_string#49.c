static const char *
hash_variant_string(hash_variant_t variant) {
	switch (variant) {
	case hash_variant_x86_32: return "hash_x86_32";
	case hash_variant_x86_128: return "hash_x86_128";
	case hash_variant_x64_128: return "hash_x64_128";
	default: not_reached();
	}
}
