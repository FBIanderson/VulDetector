static void
mallctl_thread_prof_active_get_impl(bool thread_prof_active_old_expected,
    const char *func, int line) {
	mallctl_bool_get("thread.prof.active", thread_prof_active_old_expected,
	    func, line);
}
