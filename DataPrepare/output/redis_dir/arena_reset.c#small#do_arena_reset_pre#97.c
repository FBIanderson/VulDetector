static void
do_arena_reset_pre(unsigned arena_ind, void ***ptrs, unsigned *nptrs) {
#define NLARGE	32
	unsigned nsmall, nlarge, i;
	size_t sz;
	int flags;
	tsdn_t *tsdn;

	flags = MALLOCX_ARENA(arena_ind) | MALLOCX_TCACHE_NONE;

	nsmall = get_nsmall();
	nlarge = get_nlarge() > NLARGE ? NLARGE : get_nlarge();
	*nptrs = nsmall + nlarge;
	*ptrs = (void **)malloc(*nptrs * sizeof(void *));
	assert_ptr_not_null(*ptrs, "Unexpected malloc() failure");

	/* Allocate objects with a wide range of sizes. */
	for (i = 0; i < nsmall; i++) {
		sz = get_small_size(i);
		(*ptrs)[i] = mallocx(sz, flags);
		assert_ptr_not_null((*ptrs)[i],
		    "Unexpected mallocx(%zu, %#x) failure", sz, flags);
	}
	for (i = 0; i < nlarge; i++) {
		sz = get_large_size(i);
		(*ptrs)[nsmall + i] = mallocx(sz, flags);
		assert_ptr_not_null((*ptrs)[i],
		    "Unexpected mallocx(%zu, %#x) failure", sz, flags);
	}

	tsdn = tsdn_fetch();

	/* Verify allocations. */
	for (i = 0; i < *nptrs; i++) {
		assert_zu_gt(ivsalloc(tsdn, (*ptrs)[i]), 0,
		    "Allocation should have queryable size");
	}
}
