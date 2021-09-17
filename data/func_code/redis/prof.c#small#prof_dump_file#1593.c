static bool
prof_dump_file(tsd_t *tsd, bool propagate_err, const char *filename,
    bool leakcheck, prof_tdata_t *tdata,
    struct prof_tdata_merge_iter_arg_s *prof_tdata_merge_iter_arg,
    struct prof_gctx_merge_iter_arg_s *prof_gctx_merge_iter_arg,
    struct prof_gctx_dump_iter_arg_s *prof_gctx_dump_iter_arg,
    prof_gctx_tree_t *gctxs) {
	/* Create dump file. */
	if ((prof_dump_fd = prof_dump_open(propagate_err, filename)) == -1) {
		return true;
	}

	/* Dump profile header. */
	if (prof_dump_header(tsd_tsdn(tsd), propagate_err,
	    &prof_tdata_merge_iter_arg->cnt_all)) {
		goto label_write_error;
	}

	/* Dump per gctx profile stats. */
	prof_gctx_dump_iter_arg->tsdn = tsd_tsdn(tsd);
	prof_gctx_dump_iter_arg->propagate_err = propagate_err;
	if (gctx_tree_iter(gctxs, NULL, prof_gctx_dump_iter,
	    (void *)prof_gctx_dump_iter_arg) != NULL) {
		goto label_write_error;
	}

	/* Dump /proc/<pid>/maps if possible. */
	if (prof_dump_maps(propagate_err)) {
		goto label_write_error;
	}

	if (prof_dump_close(propagate_err)) {
		return true;
	}

	return false;
label_write_error:
	prof_dump_close(propagate_err);
	return true;
}
