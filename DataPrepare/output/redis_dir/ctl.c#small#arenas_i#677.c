static ctl_arena_t *
arenas_i(size_t i) {
	ctl_arena_t *ret = arenas_i_impl(tsd_fetch(), i, true, false);
	assert(ret != NULL);
	return ret;
}
