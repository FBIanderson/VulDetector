static bool
prof_dump(tsd_t *tsd, bool propagate_err, const char *filename,
    bool leakcheck) {
	cassert(config_prof);
	assert(tsd_reentrancy_level_get(tsd) == 0);

	prof_tdata_t * tdata = prof_tdata_get(tsd, true);
	if (tdata == NULL) {
		return true;
	}

	pre_reentrancy(tsd, NULL);
	malloc_mutex_lock(tsd_tsdn(tsd), &prof_dump_mtx);

	prof_gctx_tree_t gctxs;
	struct prof_tdata_merge_iter_arg_s prof_tdata_merge_iter_arg;
	struct prof_gctx_merge_iter_arg_s prof_gctx_merge_iter_arg;
	struct prof_gctx_dump_iter_arg_s prof_gctx_dump_iter_arg;
	prof_dump_prep(tsd, tdata, &prof_tdata_merge_iter_arg,
	    &prof_gctx_merge_iter_arg, &gctxs);
	bool err = prof_dump_file(tsd, propagate_err, filename, leakcheck, tdata,
	    &prof_tdata_merge_iter_arg, &prof_gctx_merge_iter_arg,
	    &prof_gctx_dump_iter_arg, &gctxs);
	prof_gctx_finish(tsd, &gctxs);

	malloc_mutex_unlock(tsd_tsdn(tsd), &prof_dump_mtx);
	post_reentrancy(tsd);

	if (err) {
		return true;
	}

	if (leakcheck) {
		prof_leakcheck(&prof_tdata_merge_iter_arg.cnt_all,
		    prof_gctx_merge_iter_arg.leak_ngctx, filename);
	}
	return false;
}
