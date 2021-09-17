TEST_BEGIN(test_stats_summary) {
	size_t sz, allocated, active, resident, mapped;
	int expected = config_stats ? 0 : ENOENT;

	sz = sizeof(size_t);
	assert_d_eq(mallctl("stats.allocated", (void *)&allocated, &sz, NULL,
	    0), expected, "Unexpected mallctl() result");
	assert_d_eq(mallctl("stats.active", (void *)&active, &sz, NULL, 0),
	    expected, "Unexpected mallctl() result");
	assert_d_eq(mallctl("stats.resident", (void *)&resident, &sz, NULL, 0),
	    expected, "Unexpected mallctl() result");
	assert_d_eq(mallctl("stats.mapped", (void *)&mapped, &sz, NULL, 0),
	    expected, "Unexpected mallctl() result");

	if (config_stats) {
		assert_zu_le(allocated, active,
		    "allocated should be no larger than active");
		assert_zu_lt(active, resident,
		    "active should be less than resident");
		assert_zu_lt(active, mapped,
		    "active should be less than mapped");
	}
}
