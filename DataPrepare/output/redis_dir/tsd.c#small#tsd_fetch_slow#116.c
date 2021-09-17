tsd_t *
tsd_fetch_slow(tsd_t *tsd, bool minimal) {
	assert(!tsd_fast(tsd));

	if (tsd->state == tsd_state_nominal_slow) {
		/* On slow path but no work needed. */
		assert(malloc_slow || !tsd_tcache_enabled_get(tsd) ||
		    tsd_reentrancy_level_get(tsd) > 0 ||
		    *tsd_arenas_tdata_bypassp_get(tsd));
	} else if (tsd->state == tsd_state_uninitialized) {
		if (!minimal) {
			tsd->state = tsd_state_nominal;
			tsd_slow_update(tsd);
			/* Trigger cleanup handler registration. */
			tsd_set(tsd);
			tsd_data_init(tsd);
		} else {
			tsd->state = tsd_state_minimal_initialized;
			tsd_set(tsd);
			tsd_data_init_nocleanup(tsd);
		}
	} else if (tsd->state == tsd_state_minimal_initialized) {
		if (!minimal) {
			/* Switch to fully initialized. */
			tsd->state = tsd_state_nominal;
			assert(*tsd_reentrancy_levelp_get(tsd) >= 1);
			(*tsd_reentrancy_levelp_get(tsd))--;
			tsd_slow_update(tsd);
			tsd_data_init(tsd);
		} else {
			assert_tsd_data_cleanup_done(tsd);
		}
	} else if (tsd->state == tsd_state_purgatory) {
		tsd->state = tsd_state_reincarnated;
		tsd_set(tsd);
		tsd_data_init_nocleanup(tsd);
	} else {
		assert(tsd->state == tsd_state_reincarnated);
	}

	return tsd;
}
