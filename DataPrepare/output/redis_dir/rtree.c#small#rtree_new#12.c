bool
rtree_new(rtree_t *rtree, bool zeroed) {
#ifdef JEMALLOC_JET
	if (!zeroed) {
		memset(rtree, 0, sizeof(rtree_t)); /* Clear root. */
	}
#else
	assert(zeroed);
#endif

	if (malloc_mutex_init(&rtree->init_lock, "rtree", WITNESS_RANK_RTREE,
	    malloc_mutex_rank_exclusive)) {
		return true;
	}

	return false;
}
