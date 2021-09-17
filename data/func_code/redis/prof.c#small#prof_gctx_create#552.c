static prof_gctx_t *
prof_gctx_create(tsdn_t *tsdn, prof_bt_t *bt) {
	/*
	 * Create a single allocation that has space for vec of length bt->len.
	 */
	size_t size = offsetof(prof_gctx_t, vec) + (bt->len * sizeof(void *));
	prof_gctx_t *gctx = (prof_gctx_t *)iallocztm(tsdn, size,
	    sz_size2index(size), false, NULL, true, arena_get(TSDN_NULL, 0, true),
	    true);
	if (gctx == NULL) {
		return NULL;
	}
	gctx->lock = prof_gctx_mutex_choose();
	/*
	 * Set nlimbo to 1, in order to avoid a race condition with
	 * prof_tctx_destroy()/prof_gctx_try_destroy().
	 */
	gctx->nlimbo = 1;
	tctx_tree_new(&gctx->tctxs);
	/* Duplicate bt. */
	memcpy(gctx->vec, bt->vec, bt->len * sizeof(void *));
	gctx->bt.vec = gctx->vec;
	gctx->bt.len = bt->len;
	return gctx;
}
