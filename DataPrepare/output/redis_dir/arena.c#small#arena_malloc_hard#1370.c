void *
arena_malloc_hard(tsdn_t *tsdn, arena_t *arena, size_t size, szind_t ind,
    bool zero) {
	assert(!tsdn_null(tsdn) || arena != NULL);

	if (likely(!tsdn_null(tsdn))) {
		arena = arena_choose(tsdn_tsd(tsdn), arena);
	}
	if (unlikely(arena == NULL)) {
		return NULL;
	}

	if (likely(size <= SMALL_MAXCLASS)) {
		return arena_malloc_small(tsdn, arena, ind, zero);
	}
	return large_malloc(tsdn, arena, sz_index2size(ind), zero);
}
