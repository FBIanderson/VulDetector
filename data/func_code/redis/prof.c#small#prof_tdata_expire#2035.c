static bool
prof_tdata_expire(tsdn_t *tsdn, prof_tdata_t *tdata) {
	bool destroy_tdata;

	malloc_mutex_lock(tsdn, tdata->lock);
	if (!tdata->expired) {
		tdata->expired = true;
		destroy_tdata = tdata->attached ? false :
		    prof_tdata_should_destroy(tsdn, tdata, false);
	} else {
		destroy_tdata = false;
	}
	malloc_mutex_unlock(tsdn, tdata->lock);

	return destroy_tdata;
}
