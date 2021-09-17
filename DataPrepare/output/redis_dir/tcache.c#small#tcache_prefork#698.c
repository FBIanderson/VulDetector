void
tcache_prefork(tsdn_t *tsdn) {
	if (!config_prof && opt_tcache) {
		malloc_mutex_prefork(tsdn, &tcaches_mtx);
	}
}
