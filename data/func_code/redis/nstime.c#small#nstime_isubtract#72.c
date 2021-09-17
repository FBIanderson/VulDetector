void
nstime_isubtract(nstime_t *time, uint64_t subtrahend) {
	assert(time->ns >= subtrahend);

	time->ns -= subtrahend;
}
