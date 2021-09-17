bool
arena_retain_grow_limit_get_set(tsd_t *tsd, arena_t *arena, size_t *old_limit,
    size_t *new_limit) {
	assert(opt_retain);

	pszind_t new_ind JEMALLOC_CC_SILENCE_INIT(0);
	if (new_limit != NULL) {
		size_t limit = *new_limit;
		/* Grow no more than the new limit. */
		if ((new_ind = sz_psz2ind(limit + 1) - 1) >
		     EXTENT_GROW_MAX_PIND) {
			return true;
		}
	}

	malloc_mutex_lock(tsd_tsdn(tsd), &arena->extent_grow_mtx);
	if (old_limit != NULL) {
		*old_limit = sz_pind2sz(arena->retain_grow_limit);
	}
	if (new_limit != NULL) {
		arena->retain_grow_limit = new_ind;
	}
	malloc_mutex_unlock(tsd_tsdn(tsd), &arena->extent_grow_mtx);

	return false;
}
