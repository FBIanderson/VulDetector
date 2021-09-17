TEST_BEGIN(test_witness) {
	witness_t a, b;
	witness_tsdn_t witness_tsdn = { WITNESS_TSD_INITIALIZER };

	test_skip_if(!config_debug);

	witness_assert_lockless(&witness_tsdn);
	witness_assert_depth(&witness_tsdn, 0);
	witness_assert_depth_to_rank(&witness_tsdn, (witness_rank_t)1U, 0);

	witness_init(&a, "a", 1, NULL, NULL);
	witness_assert_not_owner(&witness_tsdn, &a);
	witness_lock(&witness_tsdn, &a);
	witness_assert_owner(&witness_tsdn, &a);
	witness_assert_depth(&witness_tsdn, 1);
	witness_assert_depth_to_rank(&witness_tsdn, (witness_rank_t)1U, 1);
	witness_assert_depth_to_rank(&witness_tsdn, (witness_rank_t)2U, 0);

	witness_init(&b, "b", 2, NULL, NULL);
	witness_assert_not_owner(&witness_tsdn, &b);
	witness_lock(&witness_tsdn, &b);
	witness_assert_owner(&witness_tsdn, &b);
	witness_assert_depth(&witness_tsdn, 2);
	witness_assert_depth_to_rank(&witness_tsdn, (witness_rank_t)1U, 2);
	witness_assert_depth_to_rank(&witness_tsdn, (witness_rank_t)2U, 1);
	witness_assert_depth_to_rank(&witness_tsdn, (witness_rank_t)3U, 0);

	witness_unlock(&witness_tsdn, &a);
	witness_assert_depth(&witness_tsdn, 1);
	witness_assert_depth_to_rank(&witness_tsdn, (witness_rank_t)1U, 1);
	witness_assert_depth_to_rank(&witness_tsdn, (witness_rank_t)2U, 1);
	witness_assert_depth_to_rank(&witness_tsdn, (witness_rank_t)3U, 0);
	witness_unlock(&witness_tsdn, &b);

	witness_assert_lockless(&witness_tsdn);
	witness_assert_depth(&witness_tsdn, 0);
	witness_assert_depth_to_rank(&witness_tsdn, (witness_rank_t)1U, 0);
}
