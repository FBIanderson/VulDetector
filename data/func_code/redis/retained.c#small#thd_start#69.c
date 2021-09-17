static void *
thd_start(void *arg) {
	for (unsigned next_epoch = 1; next_epoch < NEPOCHS; next_epoch++) {
		/* Busy-wait for next epoch. */
		unsigned cur_epoch;
		spin_t spinner = SPIN_INITIALIZER;
		while ((cur_epoch = atomic_load_u(&epoch, ATOMIC_ACQUIRE)) !=
		    next_epoch) {
			spin_adaptive(&spinner);
		}
		assert_u_eq(cur_epoch, next_epoch, "Unexpected epoch");

		/*
		 * Allocate.  The main thread will reset the arena, so there's
		 * no need to deallocate.
		 */
		for (unsigned i = 0; i < PER_THD_NALLOCS; i++) {
			void *p = mallocx(sz, MALLOCX_ARENA(arena_ind) |
			    MALLOCX_TCACHE_NONE
			    );
			assert_ptr_not_null(p,
			    "Unexpected mallocx() failure\n");
		}

		/* Let the main thread know we've finished this iteration. */
		atomic_fetch_add_u(&nfinished, 1, ATOMIC_RELEASE);
	}

	return NULL;
}
