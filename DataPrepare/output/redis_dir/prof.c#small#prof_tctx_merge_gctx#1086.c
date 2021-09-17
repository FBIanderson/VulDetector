static void
prof_tctx_merge_gctx(tsdn_t *tsdn, prof_tctx_t *tctx, prof_gctx_t *gctx) {
	malloc_mutex_assert_owner(tsdn, gctx->lock);

	gctx->cnt_summed.curobjs += tctx->dump_cnts.curobjs;
	gctx->cnt_summed.curbytes += tctx->dump_cnts.curbytes;
	if (opt_prof_accum) {
		gctx->cnt_summed.accumobjs += tctx->dump_cnts.accumobjs;
		gctx->cnt_summed.accumbytes += tctx->dump_cnts.accumbytes;
	}
}
