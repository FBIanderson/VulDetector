static bool
prof_gctx_should_destroy(prof_gctx_t *gctx) {
	if (opt_prof_accum) {
		return false;
	}
	if (!tctx_tree_empty(&gctx->tctxs)) {
		return false;
	}
	if (gctx->nlimbo != 0) {
		return false;
	}
	return true;
}
