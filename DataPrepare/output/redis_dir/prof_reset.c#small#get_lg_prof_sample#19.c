static size_t
get_lg_prof_sample(void) {
	size_t lg_prof_sample;
	size_t sz = sizeof(size_t);

	assert_d_eq(mallctl("prof.lg_sample", (void *)&lg_prof_sample, &sz,
	    NULL, 0), 0,
	    "Unexpected mallctl failure while reading profiling sample rate");
	return lg_prof_sample;
}
