static uint64_t
ctl_arena_stats_read_u64(arena_stats_u64_t *p) {
#ifdef JEMALLOC_ATOMIC_U64
	return atomic_load_u64(p, ATOMIC_RELAXED);
#else
	return *p;
#endif
}
