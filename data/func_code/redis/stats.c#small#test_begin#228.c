TEST_BEGIN(test_stats_arenas_bins) {
	void *p;
	size_t sz, curslabs, curregs;
	uint64_t epoch, nmalloc, ndalloc, nrequests, nfills, nflushes;
	uint64_t nslabs, nreslabs;
	int expected = config_stats ? 0 : ENOENT;

	/* Make sure allocation below isn't satisfied by tcache. */
	assert_d_eq(mallctl("thread.tcache.flush", NULL, NULL, NULL, 0),
	    opt_tcache ? 0 : EFAULT, "Unexpected mallctl() result");

	unsigned arena_ind, old_arena_ind;
	sz = sizeof(unsigned);
	assert_d_eq(mallctl("arenas.create", (void *)&arena_ind, &sz, NULL, 0),
	    0, "Arena creation failure");
	sz = sizeof(arena_ind);
	assert_d_eq(mallctl("thread.arena", (void *)&old_arena_ind, &sz,
	    (void *)&arena_ind, sizeof(arena_ind)), 0,
	    "Unexpected mallctl() failure");

	p = malloc(bin_infos[0].reg_size);
	assert_ptr_not_null(p, "Unexpected malloc() failure");

	assert_d_eq(mallctl("thread.tcache.flush", NULL, NULL, NULL, 0),
	    opt_tcache ? 0 : EFAULT, "Unexpected mallctl() result");

	assert_d_eq(mallctl("epoch", NULL, NULL, (void *)&epoch, sizeof(epoch)),
	    0, "Unexpected mallctl() failure");

	char cmd[128];
	sz = sizeof(uint64_t);
	gen_mallctl_str(cmd, "nmalloc", arena_ind);
	assert_d_eq(mallctl(cmd, (void *)&nmalloc, &sz, NULL, 0), expected,
	    "Unexpected mallctl() result");
	gen_mallctl_str(cmd, "ndalloc", arena_ind);
	assert_d_eq(mallctl(cmd, (void *)&ndalloc, &sz, NULL, 0), expected,
	    "Unexpected mallctl() result");
	gen_mallctl_str(cmd, "nrequests", arena_ind);
	assert_d_eq(mallctl(cmd, (void *)&nrequests, &sz, NULL, 0), expected,
	    "Unexpected mallctl() result");
	sz = sizeof(size_t);
	gen_mallctl_str(cmd, "curregs", arena_ind);
	assert_d_eq(mallctl(cmd, (void *)&curregs, &sz, NULL, 0), expected,
	    "Unexpected mallctl() result");

	sz = sizeof(uint64_t);
	gen_mallctl_str(cmd, "nfills", arena_ind);
	assert_d_eq(mallctl(cmd, (void *)&nfills, &sz, NULL, 0), expected,
	    "Unexpected mallctl() result");
	gen_mallctl_str(cmd, "nflushes", arena_ind);
	assert_d_eq(mallctl(cmd, (void *)&nflushes, &sz, NULL, 0), expected,
	    "Unexpected mallctl() result");

	gen_mallctl_str(cmd, "nslabs", arena_ind);
	assert_d_eq(mallctl(cmd, (void *)&nslabs, &sz, NULL, 0), expected,
	    "Unexpected mallctl() result");
	gen_mallctl_str(cmd, "nreslabs", arena_ind);
	assert_d_eq(mallctl(cmd, (void *)&nreslabs, &sz, NULL, 0), expected,
	    "Unexpected mallctl() result");
	sz = sizeof(size_t);
	gen_mallctl_str(cmd, "curslabs", arena_ind);
	assert_d_eq(mallctl(cmd, (void *)&curslabs, &sz, NULL, 0), expected,
	    "Unexpected mallctl() result");

	if (config_stats) {
		assert_u64_gt(nmalloc, 0,
		    "nmalloc should be greater than zero");
		assert_u64_ge(nmalloc, ndalloc,
		    "nmalloc should be at least as large as ndalloc");
		assert_u64_gt(nrequests, 0,
		    "nrequests should be greater than zero");
		assert_zu_gt(curregs, 0,
		    "allocated should be greater than zero");
		if (opt_tcache) {
			assert_u64_gt(nfills, 0,
			    "At least one fill should have occurred");
			assert_u64_gt(nflushes, 0,
			    "At least one flush should have occurred");
		}
		assert_u64_gt(nslabs, 0,
		    "At least one slab should have been allocated");
		assert_zu_gt(curslabs, 0,
		    "At least one slab should be currently allocated");
	}

	dallocx(p, 0);
}
