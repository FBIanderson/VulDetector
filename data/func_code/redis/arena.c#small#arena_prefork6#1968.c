void
arena_prefork6(tsdn_t *tsdn, arena_t *arena) {
	malloc_mutex_prefork(tsdn, &arena->large_mtx);
}
