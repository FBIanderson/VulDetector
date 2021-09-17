void
ctl_postfork_child(tsdn_t *tsdn) {
	malloc_mutex_postfork_child(tsdn, &ctl_mtx);
}
