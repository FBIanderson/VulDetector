static bool
prof_dump_gctx(tsdn_t *tsdn, bool propagate_err, prof_gctx_t *gctx,
    const prof_bt_t *bt, prof_gctx_tree_t *gctxs) {
	bool ret;
	unsigned i;
	struct prof_tctx_dump_iter_arg_s prof_tctx_dump_iter_arg;

	cassert(config_prof);
	malloc_mutex_assert_owner(tsdn, gctx->lock);

	/* Avoid dumping such gctx's that have no useful data. */
	if ((!opt_prof_accum && gctx->cnt_summed.curobjs == 0) ||
	    (opt_prof_accum && gctx->cnt_summed.accumobjs == 0)) {
		assert(gctx->cnt_summed.curobjs == 0);
		assert(gctx->cnt_summed.curbytes == 0);
		assert(gctx->cnt_summed.accumobjs == 0);
		assert(gctx->cnt_summed.accumbytes == 0);
		ret = false;
		goto label_return;
	}

	if (prof_dump_printf(propagate_err, "@")) {
		ret = true;
		goto label_return;
	}
	for (i = 0; i < bt->len; i++) {
		if (prof_dump_printf(propagate_err, " %#"FMTxPTR,
		    (uintptr_t)bt->vec[i])) {
			ret = true;
			goto label_return;
		}
	}

	if (prof_dump_printf(propagate_err,
	    "\n"
	    "  t*: %"FMTu64": %"FMTu64" [%"FMTu64": %"FMTu64"]\n",
	    gctx->cnt_summed.curobjs, gctx->cnt_summed.curbytes,
	    gctx->cnt_summed.accumobjs, gctx->cnt_summed.accumbytes)) {
		ret = true;
		goto label_return;
	}

	prof_tctx_dump_iter_arg.tsdn = tsdn;
	prof_tctx_dump_iter_arg.propagate_err = propagate_err;
	if (tctx_tree_iter(&gctx->tctxs, NULL, prof_tctx_dump_iter,
	    (void *)&prof_tctx_dump_iter_arg) != NULL) {
		ret = true;
		goto label_return;
	}

	ret = false;
label_return:
	return ret;
}
