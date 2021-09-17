static int
arena_i_reset_destroy_helper(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen, unsigned *arena_ind,
    arena_t **arena) {
	int ret;

	READONLY();
	WRITEONLY();
	MIB_UNSIGNED(*arena_ind, 1);

	*arena = arena_get(tsd_tsdn(tsd), *arena_ind, false);
	if (*arena == NULL || arena_is_auto(*arena)) {
		ret = EFAULT;
		goto label_return;
	}

	ret = 0;
label_return:
	return ret;
}
