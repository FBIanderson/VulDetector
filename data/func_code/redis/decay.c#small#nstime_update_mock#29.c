static bool
nstime_update_mock(nstime_t *time) {
	nupdates_mock++;
	if (monotonic_mock) {
		nstime_copy(time, &time_mock);
	}
	return !monotonic_mock;
}
