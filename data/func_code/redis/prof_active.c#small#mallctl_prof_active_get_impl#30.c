static void
mallctl_prof_active_get_impl(bool prof_active_old_expected, const char *func,
    int line) {
	mallctl_bool_get("prof.active", prof_active_old_expected, func, line);
}
