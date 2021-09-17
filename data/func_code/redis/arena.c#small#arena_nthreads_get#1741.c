unsigned
arena_nthreads_get(arena_t *arena, bool internal) {
	return atomic_load_u(&arena->nthreads[internal], ATOMIC_RELAXED);
}
