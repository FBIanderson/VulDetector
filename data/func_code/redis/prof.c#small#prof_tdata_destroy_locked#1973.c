static void
prof_tdata_destroy_locked(tsd_t *tsd, prof_tdata_t *tdata,
    bool even_if_attached) {
	malloc_mutex_assert_owner(tsd_tsdn(tsd), &tdatas_mtx);

	tdata_tree_remove(&tdatas, tdata);

	assert(prof_tdata_should_destroy_unlocked(tdata, even_if_attached));

	if (tdata->thread_name != NULL) {
		idalloctm(tsd_tsdn(tsd), tdata->thread_name, NULL, NULL, true,
		    true);
	}
	ckh_delete(tsd, &tdata->bt2tctx);
	idalloctm(tsd_tsdn(tsd), tdata, NULL, NULL, true, true);
}
