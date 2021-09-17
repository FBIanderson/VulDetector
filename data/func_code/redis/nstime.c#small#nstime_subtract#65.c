void
nstime_subtract(nstime_t *time, const nstime_t *subtrahend) {
	assert(nstime_compare(time, subtrahend) >= 0);

	time->ns -= subtrahend->ns;
}
