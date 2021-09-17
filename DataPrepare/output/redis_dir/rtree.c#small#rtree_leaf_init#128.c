static rtree_leaf_elm_t *
rtree_leaf_init(tsdn_t *tsdn, rtree_t *rtree, atomic_p_t *elmp) {
	malloc_mutex_lock(tsdn, &rtree->init_lock);
	/*
	 * If *elmp is non-null, then it was initialized with the init lock
	 * held, so we can get by with 'relaxed' here.
	 */
	rtree_leaf_elm_t *leaf = atomic_load_p(elmp, ATOMIC_RELAXED);
	if (leaf == NULL) {
		leaf = rtree_leaf_alloc(tsdn, rtree, ZU(1) <<
		    rtree_levels[RTREE_HEIGHT-1].bits);
		if (leaf == NULL) {
			malloc_mutex_unlock(tsdn, &rtree->init_lock);
			return NULL;
		}
		/*
		 * Even though we hold the lock, a later reader might not; we
		 * need release semantics.
		 */
		atomic_store_p(elmp, leaf, ATOMIC_RELEASE);
	}
	malloc_mutex_unlock(tsdn, &rtree->init_lock);

	return leaf;
}
