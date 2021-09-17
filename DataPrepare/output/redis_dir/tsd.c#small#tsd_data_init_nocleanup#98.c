static bool
tsd_data_init_nocleanup(tsd_t *tsd) {
	assert(tsd->state == tsd_state_reincarnated ||
	    tsd->state == tsd_state_minimal_initialized);
	/*
	 * During reincarnation, there is no guarantee that the cleanup function
	 * will be called (deallocation may happen after all tsd destructors).
	 * We set up tsd in a way that no cleanup is needed.
	 */
	rtree_ctx_data_init(tsd_rtree_ctxp_get_unsafe(tsd));
	*tsd_arenas_tdata_bypassp_get(tsd) = true;
	*tsd_tcache_enabledp_get_unsafe(tsd) = false;
	*tsd_reentrancy_levelp_get(tsd) = 1;
	assert_tsd_data_cleanup_done(tsd);

	return false;
}
