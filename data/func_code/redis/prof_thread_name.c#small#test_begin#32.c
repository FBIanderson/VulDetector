TEST_BEGIN(test_prof_thread_name_validation) {
	const char *thread_name;

	test_skip_if(!config_prof);

	mallctl_thread_name_get("");
	mallctl_thread_name_set("hi there");

	/* NULL input shouldn't be allowed. */
	thread_name = NULL;
	assert_d_eq(mallctl("thread.prof.name", NULL, NULL,
	    (void *)&thread_name, sizeof(thread_name)), EFAULT,
	    "Unexpected mallctl result writing \"%s\" to thread.prof.name",
	    thread_name);

	/* '\n' shouldn't be allowed. */
	thread_name = "hi\nthere";
	assert_d_eq(mallctl("thread.prof.name", NULL, NULL,
	    (void *)&thread_name, sizeof(thread_name)), EFAULT,
	    "Unexpected mallctl result writing \"%s\" to thread.prof.name",
	    thread_name);

	/* Simultaneous read/write shouldn't be allowed. */
	{
		const char *thread_name_old;
		size_t sz;

		sz = sizeof(thread_name_old);
		assert_d_eq(mallctl("thread.prof.name",
		    (void *)&thread_name_old, &sz, (void *)&thread_name,
		    sizeof(thread_name)), EPERM,
		    "Unexpected mallctl result writing \"%s\" to "
		    "thread.prof.name", thread_name);
	}

	mallctl_thread_name_set("");
}
