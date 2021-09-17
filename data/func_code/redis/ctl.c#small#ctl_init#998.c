static bool
ctl_init(tsd_t *tsd) {
	bool ret;
	tsdn_t *tsdn = tsd_tsdn(tsd);

	malloc_mutex_lock(tsdn, &ctl_mtx);
	if (!ctl_initialized) {
		ctl_arena_t *ctl_sarena, *ctl_darena;
		unsigned i;

		/*
		 * Allocate demand-zeroed space for pointers to the full
		 * range of supported arena indices.
		 */
		if (ctl_arenas == NULL) {
			ctl_arenas = (ctl_arenas_t *)base_alloc(tsdn,
			    b0get(), sizeof(ctl_arenas_t), QUANTUM);
			if (ctl_arenas == NULL) {
				ret = true;
				goto label_return;
			}
		}

		if (config_stats && ctl_stats == NULL) {
			ctl_stats = (ctl_stats_t *)base_alloc(tsdn, b0get(),
			    sizeof(ctl_stats_t), QUANTUM);
			if (ctl_stats == NULL) {
				ret = true;
				goto label_return;
			}
		}

		/*
		 * Allocate space for the current full range of arenas
		 * here rather than doing it lazily elsewhere, in order
		 * to limit when OOM-caused errors can occur.
		 */
		if ((ctl_sarena = arenas_i_impl(tsd, MALLCTL_ARENAS_ALL, false,
		    true)) == NULL) {
			ret = true;
			goto label_return;
		}
		ctl_sarena->initialized = true;

		if ((ctl_darena = arenas_i_impl(tsd, MALLCTL_ARENAS_DESTROYED,
		    false, true)) == NULL) {
			ret = true;
			goto label_return;
		}
		ctl_arena_clear(ctl_darena);
		/*
		 * Don't toggle ctl_darena to initialized until an arena is
		 * actually destroyed, so that arena.<i>.initialized can be used
		 * to query whether the stats are relevant.
		 */

		ctl_arenas->narenas = narenas_total_get();
		for (i = 0; i < ctl_arenas->narenas; i++) {
			if (arenas_i_impl(tsd, i, false, true) == NULL) {
				ret = true;
				goto label_return;
			}
		}

		ql_new(&ctl_arenas->destroyed);
		ctl_refresh(tsdn);

		ctl_initialized = true;
	}

	ret = false;
label_return:
	malloc_mutex_unlock(tsdn, &ctl_mtx);
	return ret;
}
