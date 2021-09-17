uint64_t
nstime_sec(const nstime_t *time) {
	return time->ns / BILLION;
}
