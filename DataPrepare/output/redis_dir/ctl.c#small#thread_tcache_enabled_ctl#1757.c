static int
thread_tcache_enabled_ctl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	bool oldval;

	oldval = tcache_enabled_get(tsd);
	if (newp != NULL) {
		if (newlen != sizeof(bool)) {
			ret = EINVAL;
			goto label_return;
		}
		tcache_enabled_set(tsd, *(bool *)newp);
	}
	READ(oldval, bool);

	ret = 0;
label_return:
	return ret;
}
