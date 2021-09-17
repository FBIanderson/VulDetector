static int
thread_tcache_flush_ctl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	int ret;

	if (!tcache_available(tsd)) {
		ret = EFAULT;
		goto label_return;
	}

	READONLY();
	WRITEONLY();

	tcache_flush(tsd);

	ret = 0;
label_return:
	return ret;
}
