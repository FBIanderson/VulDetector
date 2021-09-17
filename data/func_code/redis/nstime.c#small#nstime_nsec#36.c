uint64_t
nstime_nsec(const nstime_t *time) {
	return time->ns % BILLION;
}
