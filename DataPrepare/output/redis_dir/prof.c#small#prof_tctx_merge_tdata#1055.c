static void
prof_tctx_merge_tdata(tsdn_t *tsdn, prof_tctx_t *tctx, prof_tdata_t *tdata) {
	malloc_mutex_assert_owner(tsdn, tctx->tdata->lock);

	malloc_mutex_lock(tsdn, tctx->gctx->lock);

	switch (tctx->state) {
	case prof_tctx_state_initializing:
		malloc_mutex_unlock(tsdn, tctx->gctx->lock);
		return;
	case prof_tctx_state_nominal:
		tctx->state = prof_tctx_state_dumping;
		malloc_mutex_unlock(tsdn, tctx->gctx->lock);

		memcpy(&tctx->dump_cnts, &tctx->cnts, sizeof(prof_cnt_t));

		tdata->cnt_summed.curobjs += tctx->dump_cnts.curobjs;
		tdata->cnt_summed.curbytes += tctx->dump_cnts.curbytes;
		if (opt_prof_accum) {
			tdata->cnt_summed.accumobjs +=
			    tctx->dump_cnts.accumobjs;
			tdata->cnt_summed.accumbytes +=
			    tctx->dump_cnts.accumbytes;
		}
		break;
	case prof_tctx_state_dumping:
	case prof_tctx_state_purgatory:
		not_reached();
	}
}
