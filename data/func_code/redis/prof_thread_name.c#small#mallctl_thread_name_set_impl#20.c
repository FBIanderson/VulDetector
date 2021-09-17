static void
mallctl_thread_name_set_impl(const char *thread_name, const char *func,
    int line) {
	assert_d_eq(mallctl("thread.prof.name", NULL, NULL,
	    (void *)&thread_name, sizeof(thread_name)), 0,
	    "%s():%d: Unexpected mallctl failure reading thread.prof.name",
	    func, line);
	mallctl_thread_name_get_impl(thread_name, func, line);
}
