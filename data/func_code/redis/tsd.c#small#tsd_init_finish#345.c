void
tsd_init_finish(tsd_init_head_t *head, tsd_init_block_t *block) {
	malloc_mutex_lock(TSDN_NULL, &head->lock);
	ql_remove(&head->blocks, block, link);
	malloc_mutex_unlock(TSDN_NULL, &head->lock);
}
