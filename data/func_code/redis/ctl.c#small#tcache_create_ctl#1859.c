static int
tcache_create_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	unsigned tcache_ind;

	READONLY();
	if (tcaches_create(tsd, &tcache_ind)) {
		ret = EFAULT;
		goto label_return;
	}
	READ(tcache_ind, unsigned);

	ret = 0;
label_return:
	return ret;
}
