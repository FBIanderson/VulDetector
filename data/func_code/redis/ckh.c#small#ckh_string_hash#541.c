void
ckh_string_hash(const void *key, size_t r_hash[2]) {
	hash(key, strlen((const char *)key), 0x94122f33U, r_hash);
}
