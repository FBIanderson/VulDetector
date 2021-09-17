TEST_BEGIN(test_decay_ticks) {
	test_skip_if(check_background_thread_enabled());

	ticker_t *decay_ticker;
	unsigned tick0, tick1, arena_ind;
	size_t sz, large0;
	void *p;

	sz = sizeof(size_t);
	assert_d_eq(mallctl("arenas.lextent.0.size", (void *)&large0, &sz, NULL,
	    0), 0, "Unexpected mallctl failure");

	/* Set up a manually managed arena for test. */
	arena_ind = do_arena_create(0, 0);

	/* Migrate to the new arena, and get the ticker. */
	unsigned old_arena_ind;
	size_t sz_arena_ind = sizeof(old_arena_ind);
	assert_d_eq(mallctl("thread.arena", (void *)&old_arena_ind,
	    &sz_arena_ind, (void *)&arena_ind, sizeof(arena_ind)), 0,
	    "Unexpected mallctl() failure");
	decay_ticker = decay_ticker_get(tsd_fetch(), arena_ind);
	assert_ptr_not_null(decay_ticker,
	    "Unexpected failure getting decay ticker");

	/*
	 * Test the standard APIs using a large size class, since we can't
	 * control tcache interactions for small size classes (except by
	 * completely disabling tcache for the entire test program).
	 */

	/* malloc(). */
	tick0 = ticker_read(decay_ticker);
	p = malloc(large0);
	assert_ptr_not_null(p, "Unexpected malloc() failure");
	tick1 = ticker_read(decay_ticker);
	assert_u32_ne(tick1, tick0, "Expected ticker to tick during malloc()");
	/* free(). */
	tick0 = ticker_read(decay_ticker);
	free(p);
	tick1 = ticker_read(decay_ticker);
	assert_u32_ne(tick1, tick0, "Expected ticker to tick during free()");

	/* calloc(). */
	tick0 = ticker_read(decay_ticker);
	p = calloc(1, large0);
	assert_ptr_not_null(p, "Unexpected calloc() failure");
	tick1 = ticker_read(decay_ticker);
	assert_u32_ne(tick1, tick0, "Expected ticker to tick during calloc()");
	free(p);

	/* posix_memalign(). */
	tick0 = ticker_read(decay_ticker);
	assert_d_eq(posix_memalign(&p, sizeof(size_t), large0), 0,
	    "Unexpected posix_memalign() failure");
	tick1 = ticker_read(decay_ticker);
	assert_u32_ne(tick1, tick0,
	    "Expected ticker to tick during posix_memalign()");
	free(p);

	/* aligned_alloc(). */
	tick0 = ticker_read(decay_ticker);
	p = aligned_alloc(sizeof(size_t), large0);
	assert_ptr_not_null(p, "Unexpected aligned_alloc() failure");
	tick1 = ticker_read(decay_ticker);
	assert_u32_ne(tick1, tick0,
	    "Expected ticker to tick during aligned_alloc()");
	free(p);

	/* realloc(). */
	/* Allocate. */
	tick0 = ticker_read(decay_ticker);
	p = realloc(NULL, large0);
	assert_ptr_not_null(p, "Unexpected realloc() failure");
	tick1 = ticker_read(decay_ticker);
	assert_u32_ne(tick1, tick0, "Expected ticker to tick during realloc()");
	/* Reallocate. */
	tick0 = ticker_read(decay_ticker);
	p = realloc(p, large0);
	assert_ptr_not_null(p, "Unexpected realloc() failure");
	tick1 = ticker_read(decay_ticker);
	assert_u32_ne(tick1, tick0, "Expected ticker to tick during realloc()");
	/* Deallocate. */
	tick0 = ticker_read(decay_ticker);
	realloc(p, 0);
	tick1 = ticker_read(decay_ticker);
	assert_u32_ne(tick1, tick0, "Expected ticker to tick during realloc()");

	/*
	 * Test the *allocx() APIs using large and small size classes, with
	 * tcache explicitly disabled.
	 */
	{
		unsigned i;
		size_t allocx_sizes[2];
		allocx_sizes[0] = large0;
		allocx_sizes[1] = 1;

		for (i = 0; i < sizeof(allocx_sizes) / sizeof(size_t); i++) {
			sz = allocx_sizes[i];

			/* mallocx(). */
			tick0 = ticker_read(decay_ticker);
			p = mallocx(sz, MALLOCX_TCACHE_NONE);
			assert_ptr_not_null(p, "Unexpected mallocx() failure");
			tick1 = ticker_read(decay_ticker);
			assert_u32_ne(tick1, tick0,
			    "Expected ticker to tick during mallocx() (sz=%zu)",
			    sz);
			/* rallocx(). */
			tick0 = ticker_read(decay_ticker);
			p = rallocx(p, sz, MALLOCX_TCACHE_NONE);
			assert_ptr_not_null(p, "Unexpected rallocx() failure");
			tick1 = ticker_read(decay_ticker);
			assert_u32_ne(tick1, tick0,
			    "Expected ticker to tick during rallocx() (sz=%zu)",
			    sz);
			/* xallocx(). */
			tick0 = ticker_read(decay_ticker);
			xallocx(p, sz, 0, MALLOCX_TCACHE_NONE);
			tick1 = ticker_read(decay_ticker);
			assert_u32_ne(tick1, tick0,
			    "Expected ticker to tick during xallocx() (sz=%zu)",
			    sz);
			/* dallocx(). */
			tick0 = ticker_read(decay_ticker);
			dallocx(p, MALLOCX_TCACHE_NONE);
			tick1 = ticker_read(decay_ticker);
			assert_u32_ne(tick1, tick0,
			    "Expected ticker to tick during dallocx() (sz=%zu)",
			    sz);
			/* sdallocx(). */
			p = mallocx(sz, MALLOCX_TCACHE_NONE);
			assert_ptr_not_null(p, "Unexpected mallocx() failure");
			tick0 = ticker_read(decay_ticker);
			sdallocx(p, sz, MALLOCX_TCACHE_NONE);
			tick1 = ticker_read(decay_ticker);
			assert_u32_ne(tick1, tick0,
			    "Expected ticker to tick during sdallocx() "
			    "(sz=%zu)", sz);
		}
	}

	/*
	 * Test tcache fill/flush interactions for large and small size classes,
	 * using an explicit tcache.
	 */
	unsigned tcache_ind, i;
	size_t tcache_sizes[2];
	tcache_sizes[0] = large0;
	tcache_sizes[1] = 1;

	size_t tcache_max, sz_tcache_max;
	sz_tcache_max = sizeof(tcache_max);
	assert_d_eq(mallctl("arenas.tcache_max", (void *)&tcache_max,
	    &sz_tcache_max, NULL, 0), 0, "Unexpected mallctl() failure");

	sz = sizeof(unsigned);
	assert_d_eq(mallctl("tcache.create", (void *)&tcache_ind, &sz,
	    NULL, 0), 0, "Unexpected mallctl failure");

	for (i = 0; i < sizeof(tcache_sizes) / sizeof(size_t); i++) {
		sz = tcache_sizes[i];

		/* tcache fill. */
		tick0 = ticker_read(decay_ticker);
		p = mallocx(sz, MALLOCX_TCACHE(tcache_ind));
		assert_ptr_not_null(p, "Unexpected mallocx() failure");
		tick1 = ticker_read(decay_ticker);
		assert_u32_ne(tick1, tick0,
		    "Expected ticker to tick during tcache fill "
		    "(sz=%zu)", sz);
		/* tcache flush. */
		dallocx(p, MALLOCX_TCACHE(tcache_ind));
		tick0 = ticker_read(decay_ticker);
		assert_d_eq(mallctl("tcache.flush", NULL, NULL,
		    (void *)&tcache_ind, sizeof(unsigned)), 0,
		    "Unexpected mallctl failure");
		tick1 = ticker_read(decay_ticker);

		/* Will only tick if it's in tcache. */
		if (sz <= tcache_max) {
			assert_u32_ne(tick1, tick0,
			    "Expected ticker to tick during tcache "
			    "flush (sz=%zu)", sz);
		} else {
			assert_u32_eq(tick1, tick0,
			    "Unexpected ticker tick during tcache "
			    "flush (sz=%zu)", sz);
		}
	}
}
