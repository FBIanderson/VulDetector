static int
prof_dump_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	const char *filename = NULL;

	if (!config_prof) {
		return ENOENT;
	}

	WRITEONLY();
	WRITE(filename, const char *);

	if (prof_mdump(tsd, filename)) {
		ret = EFAULT;
		goto label_return;
	}

	ret = 0;
label_return:
	return ret;
}
