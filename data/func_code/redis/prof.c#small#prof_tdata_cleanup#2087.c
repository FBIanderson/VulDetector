void
prof_tdata_cleanup(tsd_t *tsd) {
	prof_tdata_t *tdata;

	if (!config_prof) {
		return;
	}

	tdata = tsd_prof_tdata_get(tsd);
	if (tdata != NULL) {
		prof_tdata_detach(tsd, tdata);
	}
}
