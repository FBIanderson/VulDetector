static int
prof_thread_active_init_ctl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	bool oldval;

	if (!config_prof) {
		return ENOENT;
	}

	if (newp != NULL) {
		if (newlen != sizeof(bool)) {
			ret = EINVAL;
			goto label_return;
		}
		oldval = prof_thread_active_init_set(tsd_tsdn(tsd),
		    *(bool *)newp);
	} else {
		oldval = prof_thread_active_init_get(tsd_tsdn(tsd));
	}
	READ(oldval, bool);

	ret = 0;
label_return:
	return ret;
}
