static int
prof_reset_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	size_t lg_sample = lg_prof_sample;

	if (!config_prof) {
		return ENOENT;
	}

	WRITEONLY();
	WRITE(lg_sample, size_t);
	if (lg_sample >= (sizeof(uint64_t) << 3)) {
		lg_sample = (sizeof(uint64_t) << 3) - 1;
	}

	prof_reset(tsd, lg_sample);

	ret = 0;
label_return:
	return ret;
}
