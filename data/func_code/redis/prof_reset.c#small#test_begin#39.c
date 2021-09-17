TEST_BEGIN(test_prof_reset_basic) {
	size_t lg_prof_sample_orig, lg_prof_sample, lg_prof_sample_next;
	size_t sz;
	unsigned i;

	test_skip_if(!config_prof);

	sz = sizeof(size_t);
	assert_d_eq(mallctl("opt.lg_prof_sample", (void *)&lg_prof_sample_orig,
	    &sz, NULL, 0), 0,
	    "Unexpected mallctl failure while reading profiling sample rate");
	assert_zu_eq(lg_prof_sample_orig, 0,
	    "Unexpected profiling sample rate");
	lg_prof_sample = get_lg_prof_sample();
	assert_zu_eq(lg_prof_sample_orig, lg_prof_sample,
	    "Unexpected disagreement between \"opt.lg_prof_sample\" and "
	    "\"prof.lg_sample\"");

	/* Test simple resets. */
	for (i = 0; i < 2; i++) {
		assert_d_eq(mallctl("prof.reset", NULL, NULL, NULL, 0), 0,
		    "Unexpected mallctl failure while resetting profile data");
		lg_prof_sample = get_lg_prof_sample();
		assert_zu_eq(lg_prof_sample_orig, lg_prof_sample,
		    "Unexpected profile sample rate change");
	}

	/* Test resets with prof.lg_sample changes. */
	lg_prof_sample_next = 1;
	for (i = 0; i < 2; i++) {
		do_prof_reset(lg_prof_sample_next);
		lg_prof_sample = get_lg_prof_sample();
		assert_zu_eq(lg_prof_sample, lg_prof_sample_next,
		    "Expected profile sample rate change");
		lg_prof_sample_next = lg_prof_sample_orig;
	}

	/* Make sure the test code restored prof.lg_sample. */
	lg_prof_sample = get_lg_prof_sample();
	assert_zu_eq(lg_prof_sample_orig, lg_prof_sample,
	    "Unexpected disagreement between \"opt.lg_prof_sample\" and "
	    "\"prof.lg_sample\"");
}
