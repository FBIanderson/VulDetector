void
prof_alloc_rollback(tsd_t *tsd, prof_tctx_t *tctx, bool updated) {
	prof_tdata_t *tdata;

	cassert(config_prof);

	if (updated) {
		/*
		 * Compute a new sample threshold.  This isn't very important in
		 * practice, because this function is rarely executed, so the
		 * potential for sample bias is minimal except in contrived
		 * programs.
		 */
		tdata = prof_tdata_get(tsd, true);
		if (tdata != NULL) {
			prof_sample_threshold_update(tdata);
		}
	}

	if ((uintptr_t)tctx > (uintptr_t)1U) {
		malloc_mutex_lock(tsd_tsdn(tsd), tctx->tdata->lock);
		tctx->prepared = false;
		if (prof_tctx_should_destroy(tsd_tsdn(tsd), tctx)) {
			prof_tctx_destroy(tsd, tctx);
		} else {
			malloc_mutex_unlock(tsd_tsdn(tsd), tctx->tdata->lock);
		}
	}
}
