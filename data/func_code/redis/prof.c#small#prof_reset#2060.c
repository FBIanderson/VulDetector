void
prof_reset(tsd_t *tsd, size_t lg_sample) {
	prof_tdata_t *next;

	assert(lg_sample < (sizeof(uint64_t) << 3));

	malloc_mutex_lock(tsd_tsdn(tsd), &prof_dump_mtx);
	malloc_mutex_lock(tsd_tsdn(tsd), &tdatas_mtx);

	lg_prof_sample = lg_sample;

	next = NULL;
	do {
		prof_tdata_t *to_destroy = tdata_tree_iter(&tdatas, next,
		    prof_tdata_reset_iter, (void *)tsd);
		if (to_destroy != NULL) {
			next = tdata_tree_next(&tdatas, to_destroy);
			prof_tdata_destroy_locked(tsd, to_destroy, false);
		} else {
			next = NULL;
		}
	} while (next != NULL);

	malloc_mutex_unlock(tsd_tsdn(tsd), &tdatas_mtx);
	malloc_mutex_unlock(tsd_tsdn(tsd), &prof_dump_mtx);
}
