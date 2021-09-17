static void
prof_dump_gctx_prep(tsdn_t *tsdn, prof_gctx_t *gctx, prof_gctx_tree_t *gctxs) {
	cassert(config_prof);

	malloc_mutex_lock(tsdn, gctx->lock);

	/*
	 * Increment nlimbo so that gctx won't go away before dump.
	 * Additionally, link gctx into the dump list so that it is included in
	 * prof_dump()'s second pass.
	 */
	gctx->nlimbo++;
	gctx_tree_insert(gctxs, gctx);

	memset(&gctx->cnt_summed, 0, sizeof(prof_cnt_t));

	malloc_mutex_unlock(tsdn, gctx->lock);
}
