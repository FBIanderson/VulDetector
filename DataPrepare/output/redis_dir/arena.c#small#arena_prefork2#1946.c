void
arena_prefork2(tsdn_t *tsdn, arena_t *arena) {
	malloc_mutex_prefork(tsdn, &arena->extent_grow_mtx);
}
