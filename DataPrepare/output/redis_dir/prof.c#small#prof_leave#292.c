static void
prof_leave(tsd_t *tsd, prof_tdata_t *tdata) {
	cassert(config_prof);
	assert(tdata == prof_tdata_get(tsd, false));

	malloc_mutex_unlock(tsd_tsdn(tsd), &bt2gctx_mtx);

	if (tdata != NULL) {
		bool idump, gdump;

		assert(tdata->enq);
		tdata->enq = false;
		idump = tdata->enq_idump;
		tdata->enq_idump = false;
		gdump = tdata->enq_gdump;
		tdata->enq_gdump = false;

		if (idump) {
			prof_idump(tsd_tsdn(tsd));
		}
		if (gdump) {
			prof_gdump(tsd_tsdn(tsd));
		}
	}
}
