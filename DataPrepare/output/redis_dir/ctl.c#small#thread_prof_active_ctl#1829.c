static int
thread_prof_active_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	bool oldval;

	if (!config_prof) {
		return ENOENT;
	}

	oldval = prof_thread_active_get(tsd);
	if (newp != NULL) {
		if (newlen != sizeof(bool)) {
			ret = EINVAL;
			goto label_return;
		}
		if (prof_thread_active_set(tsd, *(bool *)newp)) {
			ret = EAGAIN;
			goto label_return;
		}
	}
	READ(oldval, bool);

	ret = 0;
label_return:
	return ret;
}
