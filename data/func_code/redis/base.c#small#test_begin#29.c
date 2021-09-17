TEST_BEGIN(test_base_hooks_default) {
	base_t *base;
	size_t allocated0, allocated1, resident, mapped, n_thp;

	tsdn_t *tsdn = tsd_tsdn(tsd_fetch());
	base = base_new(tsdn, 0, (extent_hooks_t *)&extent_hooks_default);

	if (config_stats) {
		base_stats_get(tsdn, base, &allocated0, &resident, &mapped,
		    &n_thp);
		assert_zu_ge(allocated0, sizeof(base_t),
		    "Base header should count as allocated");
		if (opt_metadata_thp == metadata_thp_always) {
			assert_zu_gt(n_thp, 0,
			    "Base should have 1 THP at least.");
		}
	}

	assert_ptr_not_null(base_alloc(tsdn, base, 42, 1),
	    "Unexpected base_alloc() failure");

	if (config_stats) {
		base_stats_get(tsdn, base, &allocated1, &resident, &mapped,
		    &n_thp);
		assert_zu_ge(allocated1 - allocated0, 42,
		    "At least 42 bytes were allocated by base_alloc()");
	}

	base_delete(tsdn, base);
}
