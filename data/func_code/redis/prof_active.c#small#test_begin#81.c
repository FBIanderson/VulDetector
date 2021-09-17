TEST_BEGIN(test_prof_active) {
	test_skip_if(!config_prof);

	mallctl_prof_active_get(true);
	mallctl_thread_prof_active_get(false);

	mallctl_prof_active_set(true, true);
	mallctl_thread_prof_active_set(false, false);
	/* prof.active, !thread.prof.active. */
	prof_sampling_probe(false);

	mallctl_prof_active_set(true, false);
	mallctl_thread_prof_active_set(false, false);
	/* !prof.active, !thread.prof.active. */
	prof_sampling_probe(false);

	mallctl_prof_active_set(false, false);
	mallctl_thread_prof_active_set(false, true);
	/* !prof.active, thread.prof.active. */
	prof_sampling_probe(false);

	mallctl_prof_active_set(false, true);
	mallctl_thread_prof_active_set(true, true);
	/* prof.active, thread.prof.active. */
	prof_sampling_probe(true);

	/* Restore settings. */
	mallctl_prof_active_set(true, true);
	mallctl_thread_prof_active_set(true, false);
}
