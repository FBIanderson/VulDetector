static bool
check_background_thread_enabled(void) {
	bool enabled;
	size_t sz = sizeof(bool);
	int ret = mallctl("background_thread", (void *)&enabled, &sz, NULL,0);
	if (ret == ENOENT) {
		return false;
	}
	assert_d_eq(ret, 0, "Unexpected mallctl error");
	return enabled;
}
