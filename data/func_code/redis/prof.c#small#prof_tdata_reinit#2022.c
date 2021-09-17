prof_tdata_t *
prof_tdata_reinit(tsd_t *tsd, prof_tdata_t *tdata) {
	uint64_t thr_uid = tdata->thr_uid;
	uint64_t thr_discrim = tdata->thr_discrim + 1;
	char *thread_name = (tdata->thread_name != NULL) ?
	    prof_thread_name_alloc(tsd_tsdn(tsd), tdata->thread_name) : NULL;
	bool active = tdata->active;

	prof_tdata_detach(tsd, tdata);
	return prof_tdata_init_impl(tsd, thr_uid, thr_discrim, thread_name,
	    active);
}
