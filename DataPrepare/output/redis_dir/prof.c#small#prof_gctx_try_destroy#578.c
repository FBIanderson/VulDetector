static void
prof_gctx_try_destroy(tsd_t *tsd, prof_tdata_t *tdata_self, prof_gctx_t *gctx,
    prof_tdata_t *tdata) {
	cassert(config_prof);

	/*
	 * Check that gctx is still unused by any thread cache before destroying
	 * it.  prof_lookup() increments gctx->nlimbo in order to avoid a race
	 * condition with this function, as does prof_tctx_destroy() in order to
	 * avoid a race between the main body of prof_tctx_destroy() and entry
	 * into this function.
	 */
	prof_enter(tsd, tdata_self);
	malloc_mutex_lock(tsd_tsdn(tsd), gctx->lock);
	assert(gctx->nlimbo != 0);
	if (tctx_tree_empty(&gctx->tctxs) && gctx->nlimbo == 1) {
		/* Remove gctx from bt2gctx. */
		if (ckh_remove(tsd, &bt2gctx, &gctx->bt, NULL, NULL)) {
			not_reached();
		}
		prof_leave(tsd, tdata_self);
		/* Destroy gctx. */
		malloc_mutex_unlock(tsd_tsdn(tsd), gctx->lock);
		idalloctm(tsd_tsdn(tsd), gctx, NULL, NULL, true, true);
	} else {
		/*
		 * Compensate for increment in prof_tctx_destroy() or
		 * prof_lookup().
		 */
		gctx->nlimbo--;
		malloc_mutex_unlock(tsd_tsdn(tsd), gctx->lock);
		prof_leave(tsd, tdata_self);
	}
}
