TEST_BEGIN(test_retained) {
	test_skip_if(!config_stats);

	arena_ind = do_arena_create(NULL);
	sz = nallocx(HUGEPAGE, 0);
	esz = sz + sz_large_pad;

	atomic_store_u(&epoch, 0, ATOMIC_RELAXED);

	unsigned nthreads = ncpus * 2;
	VARIABLE_ARRAY(thd_t, threads, nthreads);
	for (unsigned i = 0; i < nthreads; i++) {
		thd_create(&threads[i], thd_start, NULL);
	}

	for (unsigned e = 1; e < NEPOCHS; e++) {
		atomic_store_u(&nfinished, 0, ATOMIC_RELEASE);
		atomic_store_u(&epoch, e, ATOMIC_RELEASE);

		/* Wait for threads to finish allocating. */
		spin_t spinner = SPIN_INITIALIZER;
		while (atomic_load_u(&nfinished, ATOMIC_ACQUIRE) < nthreads) {
			spin_adaptive(&spinner);
		}

		/*
		 * Assert that retained is no more than the sum of size classes
		 * that should have been used to satisfy the worker threads'
		 * requests, discounting per growth fragmentation.
		 */
		do_refresh();

		size_t allocated = esz * nthreads * PER_THD_NALLOCS;
		size_t active = do_get_active(arena_ind);
		assert_zu_le(allocated, active, "Unexpected active memory");
		size_t mapped = do_get_mapped(arena_ind);
		assert_zu_le(active, mapped, "Unexpected mapped memory");

		arena_t *arena = arena_get(tsdn_fetch(), arena_ind, false);
		size_t usable = 0;
		size_t fragmented = 0;
		for (pszind_t pind = sz_psz2ind(HUGEPAGE); pind <
		    arena->extent_grow_next; pind++) {
			size_t psz = sz_pind2sz(pind);
			size_t psz_fragmented = psz % esz;
			size_t psz_usable = psz - psz_fragmented;
			/*
			 * Only consider size classes that wouldn't be skipped.
			 */
			if (psz_usable > 0) {
				assert_zu_lt(usable, allocated,
				    "Excessive retained memory "
				    "(%#zx[+%#zx] > %#zx)", usable, psz_usable,
				    allocated);
				fragmented += psz_fragmented;
				usable += psz_usable;
			}
		}

		/*
		 * Clean up arena.  Destroying and recreating the arena
		 * is simpler that specifying extent hooks that deallocate
		 * (rather than retaining) during reset.
		 */
		do_arena_destroy(arena_ind);
		assert_u_eq(do_arena_create(NULL), arena_ind,
		    "Unexpected arena index");
	}

	for (unsigned i = 0; i < nthreads; i++) {
		thd_join(threads[i], NULL);
	}

	do_arena_destroy(arena_ind);
}
