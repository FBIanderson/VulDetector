int
ctl_nametomib(tsd_t *tsd, const char *name, size_t *mibp, size_t *miblenp) {
	int ret;

	if (!ctl_initialized && ctl_init(tsd)) {
		ret = EAGAIN;
		goto label_return;
	}

	ret = ctl_lookup(tsd_tsdn(tsd), name, NULL, mibp, miblenp);
label_return:
	return(ret);
}
