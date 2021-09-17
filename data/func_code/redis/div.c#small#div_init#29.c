void
div_init(div_info_t *div_info, size_t d) {
	/* Nonsensical. */
	assert(d != 0);
	/*
	 * This would make the value of magic too high to fit into a uint32_t
	 * (we would want magic = 2^32 exactly). This would mess with code gen
	 * on 32-bit machines.
	 */
	assert(d != 1);

	uint64_t two_to_k = ((uint64_t)1 << 32);
	uint32_t magic = (uint32_t)(two_to_k / d);

	/*
	 * We want magic = ceil(2^k / d), but C gives us floor. We have to
	 * increment it unless the result was exact (i.e. unless d is a power of
	 * two).
	 */
	if (two_to_k % d != 0) {
		magic++;
	}
	div_info->magic = magic;
#ifdef JEMALLOC_DEBUG
	div_info->d = d;
#endif
}
