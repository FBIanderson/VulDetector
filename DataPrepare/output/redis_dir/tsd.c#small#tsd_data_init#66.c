static bool
tsd_data_init(tsd_t *tsd) {
	/*
	 * We initialize the rtree context first (before the tcache), since the
	 * tcache initialization depends on it.
	 */
	rtree_ctx_data_init(tsd_rtree_ctxp_get_unsafe(tsd));

	/*
	 * A nondeterministic seed based on the address of tsd reduces
	 * the likelihood of lockstep non-uniform cache index
	 * utilization among identical concurrent processes, but at the
	 * cost of test repeatability.  For debug builds, instead use a
	 * deterministic seed.
	 */
	*tsd_offset_statep_get(tsd) = config_debug ? 0 :
	    (uint64_t)(uintptr_t)tsd;

	return tsd_tcache_enabled_data_init(tsd);
}
