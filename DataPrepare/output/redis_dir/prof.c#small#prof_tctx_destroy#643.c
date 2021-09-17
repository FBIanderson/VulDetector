static void
prof_tctx_destroy(tsd_t *tsd, prof_tctx_t *tctx) {
	prof_tdata_t *tdata = tctx->tdata;
	prof_gctx_t *gctx = tctx->gctx;
	bool destroy_tdata, destroy_tctx, destroy_gctx;

	malloc_mutex_assert_owner(tsd_tsdn(tsd), tctx->tdata->lock);

	assert(tctx->cnts.curobjs == 0);
	assert(tctx->cnts.curbytes == 0);
	assert(!opt_prof_accum);
	assert(tctx->cnts.accumobjs == 0);
	assert(tctx->cnts.accumbytes == 0);

	ckh_remove(tsd, &tdata->bt2tctx, &gctx->bt, NULL, NULL);
	destroy_tdata = prof_tdata_should_destroy(tsd_tsdn(tsd), tdata, false);
	malloc_mutex_unlock(tsd_tsdn(tsd), tdata->lock);

	malloc_mutex_lock(tsd_tsdn(tsd), gctx->lock);
	switch (tctx->state) {
	case prof_tctx_state_nominal:
		tctx_tree_remove(&gctx->tctxs, tctx);
		destroy_tctx = true;
		if (prof_gctx_should_destroy(gctx)) {
			/*
			 * Increment gctx->nlimbo in order to keep another
			 * thread from winning the race to destroy gctx while
			 * this one has gctx->lock dropped.  Without this, it
			 * would be possible for another thread to:
			 *
			 * 1) Sample an allocation associated with gctx.
			 * 2) Deallocate the sampled object.
			 * 3) Successfully prof_gctx_try_destroy(gctx).
			 *
			 * The result would be that gctx no longer exists by the
			 * time this thread accesses it in
			 * prof_gctx_try_destroy().
			 */
			gctx->nlimbo++;
			destroy_gctx = true;
		} else {
			destroy_gctx = false;
		}
		break;
	case prof_tctx_state_dumping:
		/*
		 * A dumping thread needs tctx to remain valid until dumping
		 * has finished.  Change state such that the dumping thread will
		 * complete destruction during a late dump iteration phase.
		 */
		tctx->state = prof_tctx_state_purgatory;
		destroy_tctx = false;
		destroy_gctx = false;
		break;
	default:
		not_reached();
		destroy_tctx = false;
		destroy_gctx = false;
	}
	malloc_mutex_unlock(tsd_tsdn(tsd), gctx->lock);
	if (destroy_gctx) {
		prof_gctx_try_destroy(tsd, prof_tdata_get(tsd, false), gctx,
		    tdata);
	}

	malloc_mutex_assert_not_owner(tsd_tsdn(tsd), tctx->tdata->lock);

	if (destroy_tdata) {
		prof_tdata_destroy(tsd, tdata, false);
	}

	if (destroy_tctx) {
		idalloctm(tsd_tsdn(tsd), tctx, NULL, NULL, true, true);
	}
}
