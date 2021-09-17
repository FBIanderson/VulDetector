static void
arena_i_decay(tsdn_t *tsdn, unsigned arena_ind, bool all) {
	malloc_mutex_lock(tsdn, &ctl_mtx);
	{
		unsigned narenas = ctl_arenas->narenas;

		/*
		 * Access via index narenas is deprecated, and scheduled for
		 * removal in 6.0.0.
		 */
		if (arena_ind == MALLCTL_ARENAS_ALL || arena_ind == narenas) {
			unsigned i;
			VARIABLE_ARRAY(arena_t *, tarenas, narenas);

			for (i = 0; i < narenas; i++) {
				tarenas[i] = arena_get(tsdn, i, false);
			}

			/*
			 * No further need to hold ctl_mtx, since narenas and
			 * tarenas contain everything needed below.
			 */
			malloc_mutex_unlock(tsdn, &ctl_mtx);

			for (i = 0; i < narenas; i++) {
				if (tarenas[i] != NULL) {
					arena_decay(tsdn, tarenas[i], false,
					    all);
				}
			}
		} else {
			arena_t *tarena;

			assert(arena_ind < narenas);

			tarena = arena_get(tsdn, arena_ind, false);

			/* No further need to hold ctl_mtx. */
			malloc_mutex_unlock(tsdn, &ctl_mtx);

			if (tarena != NULL) {
				arena_decay(tsdn, tarena, false, all);
			}
		}
	}
}
