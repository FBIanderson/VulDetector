TEST_BEGIN(test_prof_reset) {
	size_t lg_prof_sample_orig;
	thd_t thds[NTHREADS];
	unsigned thd_args[NTHREADS];
	unsigned i;
	size_t bt_count, tdata_count;

	test_skip_if(!config_prof);

	bt_count = prof_bt_count();
	assert_zu_eq(bt_count, 0,
	    "Unexpected pre-existing tdata structures");
	tdata_count = prof_tdata_count();

	lg_prof_sample_orig = get_lg_prof_sample();
	do_prof_reset(5);

	set_prof_active(true);

	for (i = 0; i < NTHREADS; i++) {
		thd_args[i] = i;
		thd_create(&thds[i], thd_start, (void *)&thd_args[i]);
	}
	for (i = 0; i < NTHREADS; i++) {
		thd_join(thds[i], NULL);
	}

	assert_zu_eq(prof_bt_count(), bt_count,
	    "Unexpected bactrace count change");
	assert_zu_eq(prof_tdata_count(), tdata_count,
	    "Unexpected remaining tdata structures");

	set_prof_active(false);

	do_prof_reset(lg_prof_sample_orig);
}
