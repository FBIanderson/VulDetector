static void
ctl_accum_arena_stats_u64(arena_stats_u64_t *dst, arena_stats_u64_t *src) {
#ifdef JEMALLOC_ATOMIC_U64
	uint64_t cur_dst = atomic_load_u64(dst, ATOMIC_RELAXED);
	uint64_t cur_src = atomic_load_u64(src, ATOMIC_RELAXED);
	atomic_store_u64(dst, cur_dst + cur_src, ATOMIC_RELAXED);
#else
	*dst += *src;
#endif
}
