static void
prof_tdata_destroy(tsd_t *tsd, prof_tdata_t *tdata, bool even_if_attached) {
	malloc_mutex_lock(tsd_tsdn(tsd), &tdatas_mtx);
	prof_tdata_destroy_locked(tsd, tdata, even_if_attached);
	malloc_mutex_unlock(tsd_tsdn(tsd), &tdatas_mtx);
}
