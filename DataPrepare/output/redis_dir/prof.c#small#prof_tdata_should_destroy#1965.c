static bool
prof_tdata_should_destroy(tsdn_t *tsdn, prof_tdata_t *tdata,
    bool even_if_attached) {
	malloc_mutex_assert_owner(tsdn, tdata->lock);

	return prof_tdata_should_destroy_unlocked(tdata, even_if_attached);
}
