static void
prof_tdata_detach(tsd_t *tsd, prof_tdata_t *tdata) {
	bool destroy_tdata;

	malloc_mutex_lock(tsd_tsdn(tsd), tdata->lock);
	if (tdata->attached) {
		destroy_tdata = prof_tdata_should_destroy(tsd_tsdn(tsd), tdata,
		    true);
		/*
		 * Only detach if !destroy_tdata, because detaching would allow
		 * another thread to win the race to destroy tdata.
		 */
		if (!destroy_tdata) {
			tdata->attached = false;
		}
		tsd_prof_tdata_set(tsd, NULL);
	} else {
		destroy_tdata = false;
	}
	malloc_mutex_unlock(tsd_tsdn(tsd), tdata->lock);
	if (destroy_tdata) {
		prof_tdata_destroy(tsd, tdata, true);
	}
}
