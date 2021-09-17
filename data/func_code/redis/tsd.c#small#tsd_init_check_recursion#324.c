void *
tsd_init_check_recursion(tsd_init_head_t *head, tsd_init_block_t *block) {
	pthread_t self = pthread_self();
	tsd_init_block_t *iter;

	/* Check whether this thread has already inserted into the list. */
	malloc_mutex_lock(TSDN_NULL, &head->lock);
	ql_foreach(iter, &head->blocks, link) {
		if (iter->thread == self) {
			malloc_mutex_unlock(TSDN_NULL, &head->lock);
			return iter->data;
		}
	}
	/* Insert block into list. */
	ql_elm_new(block, link);
	block->thread = self;
	ql_tail_insert(&head->blocks, block, link);
	malloc_mutex_unlock(TSDN_NULL, &head->lock);
	return NULL;
}
