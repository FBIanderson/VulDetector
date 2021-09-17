static int
arena_i_decay_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	unsigned arena_ind;

	READONLY();
	WRITEONLY();
	MIB_UNSIGNED(arena_ind, 1);
	arena_i_decay(tsd_tsdn(tsd), arena_ind, false);

	ret = 0;
label_return:
	return ret;
}
