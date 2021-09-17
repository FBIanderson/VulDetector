void
extent_dalloc(tsdn_t *tsdn, arena_t *arena, extent_t *extent) {
	malloc_mutex_lock(tsdn, &arena->extent_avail_mtx);
	extent_avail_insert(&arena->extent_avail, extent);
	malloc_mutex_unlock(tsdn, &arena->extent_avail_mtx);
}
