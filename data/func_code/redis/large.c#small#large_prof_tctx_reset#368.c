void
large_prof_tctx_reset(tsdn_t *tsdn, extent_t *extent) {
	large_prof_tctx_set(tsdn, extent, (prof_tctx_t *)(uintptr_t)1U);
}
