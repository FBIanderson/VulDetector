uint64_t
nstime_divide(const nstime_t *time, const nstime_t *divisor) {
	assert(divisor->ns != 0);

	return time->ns / divisor->ns;
}
