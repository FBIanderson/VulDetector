void
prof_free_sampled_object(tsd_t *tsd, size_t usize, prof_tctx_t *tctx) {
	malloc_mutex_lock(tsd_tsdn(tsd), tctx->tdata->lock);
	assert(tctx->cnts.curobjs > 0);
	assert(tctx->cnts.curbytes >= usize);
	tctx->cnts.curobjs--;
	tctx->cnts.curbytes -= usize;

	if (prof_tctx_should_destroy(tsd_tsdn(tsd), tctx)) {
		prof_tctx_destroy(tsd, tctx);
	} else {
		malloc_mutex_unlock(tsd_tsdn(tsd), tctx->tdata->lock);
	}
}
