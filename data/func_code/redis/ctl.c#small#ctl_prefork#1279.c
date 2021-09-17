void
ctl_prefork(tsdn_t *tsdn) {
	malloc_mutex_prefork(tsdn, &ctl_mtx);
}
