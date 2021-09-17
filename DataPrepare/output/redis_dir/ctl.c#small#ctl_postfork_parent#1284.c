void
ctl_postfork_parent(tsdn_t *tsdn) {
	malloc_mutex_postfork_parent(tsdn, &ctl_mtx);
}
