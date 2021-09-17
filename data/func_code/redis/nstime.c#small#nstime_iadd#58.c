void
nstime_iadd(nstime_t *time, uint64_t addend) {
	assert(UINT64_MAX - time->ns >= addend);

	time->ns += addend;
}
