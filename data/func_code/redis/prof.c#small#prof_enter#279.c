static void
prof_enter(tsd_t *tsd, prof_tdata_t *tdata) {
	cassert(config_prof);
	assert(tdata == prof_tdata_get(tsd, false));

	if (tdata != NULL) {
		assert(!tdata->enq);
		tdata->enq = true;
	}

	malloc_mutex_lock(tsd_tsdn(tsd), &bt2gctx_mtx);
}
