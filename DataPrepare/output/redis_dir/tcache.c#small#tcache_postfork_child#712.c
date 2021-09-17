void
tcache_postfork_child(tsdn_t *tsdn) {
	if (!config_prof && opt_tcache) {
		malloc_mutex_postfork_child(tsdn, &tcaches_mtx);
	}
}
