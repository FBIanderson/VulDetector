bool
mutex_pool_init(mutex_pool_t *pool, const char *name, witness_rank_t rank) {
	for (int i = 0; i < MUTEX_POOL_SIZE; ++i) {
		if (malloc_mutex_init(&pool->mutexes[i], name, rank,
		    malloc_mutex_address_ordered)) {
			return true;
		}
	}
	return false;
}
