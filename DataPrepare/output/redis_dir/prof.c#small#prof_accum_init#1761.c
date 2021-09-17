bool
prof_accum_init(tsdn_t *tsdn, prof_accum_t *prof_accum) {
	cassert(config_prof);

#ifndef JEMALLOC_ATOMIC_U64
	if (malloc_mutex_init(&prof_accum->mtx, "prof_accum",
	    WITNESS_RANK_PROF_ACCUM, malloc_mutex_rank_exclusive)) {
		return true;
	}
	prof_accum->accumbytes = 0;
#else
	atomic_store_u64(&prof_accum->accumbytes, 0, ATOMIC_RELAXED);
#endif
	return false;
}
