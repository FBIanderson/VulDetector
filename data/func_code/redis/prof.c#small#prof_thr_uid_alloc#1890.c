static uint64_t
prof_thr_uid_alloc(tsdn_t *tsdn) {
	uint64_t thr_uid;

	malloc_mutex_lock(tsdn, &next_thr_uid_mtx);
	thr_uid = next_thr_uid;
	next_thr_uid++;
	malloc_mutex_unlock(tsdn, &next_thr_uid_mtx);

	return thr_uid;
}
