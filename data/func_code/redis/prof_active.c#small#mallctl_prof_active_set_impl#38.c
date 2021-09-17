static void
mallctl_prof_active_set_impl(bool prof_active_old_expected,
    bool prof_active_new, const char *func, int line) {
	mallctl_bool_set("prof.active", prof_active_old_expected,
	    prof_active_new, func, line);
}
