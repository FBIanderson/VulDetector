void
arena_nthreads_dec(arena_t *arena, bool internal) {
	atomic_fetch_sub_u(&arena->nthreads[internal], 1, ATOMIC_RELAXED);
}
