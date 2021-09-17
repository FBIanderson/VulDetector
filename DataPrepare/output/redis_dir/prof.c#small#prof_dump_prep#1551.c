static void
prof_dump_prep(tsd_t *tsd, prof_tdata_t *tdata,
    struct prof_tdata_merge_iter_arg_s *prof_tdata_merge_iter_arg,
    struct prof_gctx_merge_iter_arg_s *prof_gctx_merge_iter_arg,
    prof_gctx_tree_t *gctxs) {
	size_t tabind;
	union {
		prof_gctx_t	*p;
		void		*v;
	} gctx;

	prof_enter(tsd, tdata);

	/*
	 * Put gctx's in limbo and clear their counters in preparation for
	 * summing.
	 */
	gctx_tree_new(gctxs);
	for (tabind = 0; !ckh_iter(&bt2gctx, &tabind, NULL, &gctx.v);) {
		prof_dump_gctx_prep(tsd_tsdn(tsd), gctx.p, gctxs);
	}

	/*
	 * Iterate over tdatas, and for the non-expired ones snapshot their tctx
	 * stats and merge them into the associated gctx's.
	 */
	prof_tdata_merge_iter_arg->tsdn = tsd_tsdn(tsd);
	memset(&prof_tdata_merge_iter_arg->cnt_all, 0, sizeof(prof_cnt_t));
	malloc_mutex_lock(tsd_tsdn(tsd), &tdatas_mtx);
	tdata_tree_iter(&tdatas, NULL, prof_tdata_merge_iter,
	    (void *)prof_tdata_merge_iter_arg);
	malloc_mutex_unlock(tsd_tsdn(tsd), &tdatas_mtx);

	/* Merge tctx stats into gctx's. */
	prof_gctx_merge_iter_arg->tsdn = tsd_tsdn(tsd);
	prof_gctx_merge_iter_arg->leak_ngctx = 0;
	gctx_tree_iter(gctxs, NULL, prof_gctx_merge_iter,
	    (void *)prof_gctx_merge_iter_arg);

	prof_leave(tsd, tdata);
}
