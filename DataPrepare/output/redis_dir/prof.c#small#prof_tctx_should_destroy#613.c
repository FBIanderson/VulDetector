static bool
prof_tctx_should_destroy(tsdn_t *tsdn, prof_tctx_t *tctx) {
	malloc_mutex_assert_owner(tsdn, tctx->tdata->lock);

	if (opt_prof_accum) {
		return false;
	}
	if (tctx->cnts.curobjs != 0) {
		return false;
	}
	if (tctx->prepared) {
		return false;
	}
	return true;
}
