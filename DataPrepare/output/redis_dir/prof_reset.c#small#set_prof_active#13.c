static void
set_prof_active(bool active) {
	assert_d_eq(mallctl("prof.active", NULL, NULL, (void *)&active,
	    sizeof(active)), 0, "Unexpected mallctl failure");
}
