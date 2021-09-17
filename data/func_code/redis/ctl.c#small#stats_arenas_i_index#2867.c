static const ctl_named_node_t *
stats_arenas_i_index(tsdn_t *tsdn, const size_t *mib, size_t miblen, size_t i) {
	const ctl_named_node_t *ret;
	size_t a;

	malloc_mutex_lock(tsdn, &ctl_mtx);
	a = arenas_i2a_impl(i, true, true);
	if (a == UINT_MAX || !ctl_arenas->arenas[a]->initialized) {
		ret = NULL;
		goto label_return;
	}

	ret = super_stats_arenas_i_node;
label_return:
	malloc_mutex_unlock(tsdn, &ctl_mtx);
	return ret;
}
