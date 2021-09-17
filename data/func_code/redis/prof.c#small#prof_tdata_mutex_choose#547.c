static malloc_mutex_t *
prof_tdata_mutex_choose(uint64_t thr_uid) {
	return &tdata_locks[thr_uid % PROF_NTDATA_LOCKS];
}
