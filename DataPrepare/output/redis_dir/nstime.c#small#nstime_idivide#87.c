void
nstime_idivide(nstime_t *time, uint64_t divisor) {
	assert(divisor != 0);

	time->ns /= divisor;
}
