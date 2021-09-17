static void
accum_atomic_zu(atomic_zu_t *dst, atomic_zu_t *src) {
	size_t cur_dst = atomic_load_zu(dst, ATOMIC_RELAXED);
	size_t cur_src = atomic_load_zu(src, ATOMIC_RELAXED);
	atomic_store_zu(dst, cur_dst + cur_src, ATOMIC_RELAXED);
}
