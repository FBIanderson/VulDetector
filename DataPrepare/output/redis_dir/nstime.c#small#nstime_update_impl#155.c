static bool
nstime_update_impl(nstime_t *time) {
	nstime_t old_time;

	nstime_copy(&old_time, time);
	nstime_get(time);

	/* Handle non-monotonic clocks. */
	if (unlikely(nstime_compare(&old_time, time) > 0)) {
		nstime_copy(time, &old_time);
		return true;
	}

	return false;
}
