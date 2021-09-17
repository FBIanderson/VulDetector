static const ctl_named_node_t *
arena_i_index(tsdn_t *tsdn, const size_t *mib, size_t miblen, size_t i) {
	const ctl_named_node_t *ret;

	malloc_mutex_lock(tsdn, &ctl_mtx);
	switch (i) {
	case MALLCTL_ARENAS_ALL:
	case MALLCTL_ARENAS_DESTROYED:
		break;
	default:
		if (i > ctl_arenas->narenas) {
			ret = NULL;
			goto label_return;
		}
		break;
	}

	ret = super_arena_i_node;
label_return:
	malloc_mutex_unlock(tsdn, &ctl_mtx);
	return ret;
}
