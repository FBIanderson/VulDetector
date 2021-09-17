void
arena_prefork1(tsdn_t *tsdn, arena_t *arena) {
	if (config_stats) {
		malloc_mutex_prefork(tsdn, &arena->tcache_ql_mtx);
	}
}
