void
tcache_postfork_parent(tsdn_t *tsdn) {
	if (!config_prof && opt_tcache) {
		malloc_mutex_postfork_parent(tsdn, &tcaches_mtx);
	}
}
