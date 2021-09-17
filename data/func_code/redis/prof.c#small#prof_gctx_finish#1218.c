static void
prof_gctx_finish(tsd_t *tsd, prof_gctx_tree_t *gctxs) {
	prof_tdata_t *tdata = prof_tdata_get(tsd, false);
	prof_gctx_t *gctx;

	/*
	 * Standard tree iteration won't work here, because as soon as we
	 * decrement gctx->nlimbo and unlock gctx, another thread can
	 * concurrently destroy it, which will corrupt the tree.  Therefore,
	 * tear down the tree one node at a time during iteration.
	 */
	while ((gctx = gctx_tree_first(gctxs)) != NULL) {
		gctx_tree_remove(gctxs, gctx);
		malloc_mutex_lock(tsd_tsdn(tsd), gctx->lock);
		{
			prof_tctx_t *next;

			next = NULL;
			do {
				prof_tctx_t *to_destroy =
				    tctx_tree_iter(&gctx->tctxs, next,
				    prof_tctx_finish_iter,
				    (void *)tsd_tsdn(tsd));
				if (to_destroy != NULL) {
					next = tctx_tree_next(&gctx->tctxs,
					    to_destroy);
					tctx_tree_remove(&gctx->tctxs,
					    to_destroy);
					idalloctm(tsd_tsdn(tsd), to_destroy,
					    NULL, NULL, true, true);
				} else {
					next = NULL;
				}
			} while (next != NULL);
		}
		gctx->nlimbo--;
		if (prof_gctx_should_destroy(gctx)) {
			gctx->nlimbo++;
			malloc_mutex_unlock(tsd_tsdn(tsd), gctx->lock);
			prof_gctx_try_destroy(tsd, tdata, gctx, tdata);
		} else {
			malloc_mutex_unlock(tsd_tsdn(tsd), gctx->lock);
		}
	}
}
