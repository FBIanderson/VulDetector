static int
tcache_destroy_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	unsigned tcache_ind;

	WRITEONLY();
	tcache_ind = UINT_MAX;
	WRITE(tcache_ind, unsigned);
	if (tcache_ind == UINT_MAX) {
		ret = EFAULT;
		goto label_return;
	}
	tcaches_destroy(tsd, tcache_ind);

	ret = 0;
label_return:
	return ret;
}
