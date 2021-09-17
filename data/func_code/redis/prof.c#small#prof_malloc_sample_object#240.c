void
prof_malloc_sample_object(tsdn_t *tsdn, const void *ptr, size_t usize,
    prof_tctx_t *tctx) {
	prof_tctx_set(tsdn, ptr, usize, NULL, tctx);

	malloc_mutex_lock(tsdn, tctx->tdata->lock);
	tctx->cnts.curobjs++;
	tctx->cnts.curbytes += usize;
	if (opt_prof_accum) {
		tctx->cnts.accumobjs++;
		tctx->cnts.accumbytes += usize;
	}
	tctx->prepared = false;
	malloc_mutex_unlock(tsdn, tctx->tdata->lock);
}
