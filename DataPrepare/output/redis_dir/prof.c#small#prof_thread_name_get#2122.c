const char *
prof_thread_name_get(tsd_t *tsd) {
	prof_tdata_t *tdata;

	tdata = prof_tdata_get(tsd, true);
	if (tdata == NULL) {
		return "";
	}
	return (tdata->thread_name != NULL ? tdata->thread_name : "");
}
