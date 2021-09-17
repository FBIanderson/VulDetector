static int
thread_prof_name_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;

	if (!config_prof) {
		return ENOENT;
	}

	READ_XOR_WRITE();

	if (newp != NULL) {
		if (newlen != sizeof(const char *)) {
			ret = EINVAL;
			goto label_return;
		}

		if ((ret = prof_thread_name_set(tsd, *(const char **)newp)) !=
		    0) {
			goto label_return;
		}
	} else {
		const char *oldname = prof_thread_name_get(tsd);
		READ(oldname, const char *);
	}

	ret = 0;
label_return:
	return ret;
}
