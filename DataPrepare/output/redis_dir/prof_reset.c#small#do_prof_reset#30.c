static void
do_prof_reset(size_t lg_prof_sample) {
	assert_d_eq(mallctl("prof.reset", NULL, NULL,
	    (void *)&lg_prof_sample, sizeof(size_t)), 0,
	    "Unexpected mallctl failure while resetting profile data");
	assert_zu_eq(lg_prof_sample, get_lg_prof_sample(),
	    "Expected profile sample rate change");
}
