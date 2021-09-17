void
tsd_slow_update(tsd_t *tsd) {
	if (tsd_nominal(tsd)) {
		if (malloc_slow || !tsd_tcache_enabled_get(tsd) ||
		    tsd_reentrancy_level_get(tsd) > 0) {
			tsd->state = tsd_state_nominal_slow;
		} else {
			tsd->state = tsd_state_nominal;
		}
	}
}
