static void
mallctl_thread_prof_active_set_impl(bool thread_prof_active_old_expected,
    bool thread_prof_active_new, const char *func, int line) {
	mallctl_bool_set("thread.prof.active", thread_prof_active_old_expected,
	    thread_prof_active_new, func, line);
}
