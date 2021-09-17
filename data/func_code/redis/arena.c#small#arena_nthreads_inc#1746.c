void
arena_nthreads_inc(arena_t *arena, bool internal) {
	atomic_fetch_add_u(&arena->nthreads[internal], 1, ATOMIC_RELAXED);
}
