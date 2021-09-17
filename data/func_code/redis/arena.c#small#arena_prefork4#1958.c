void
arena_prefork4(tsdn_t *tsdn, arena_t *arena) {
	malloc_mutex_prefork(tsdn, &arena->extent_avail_mtx);
}
