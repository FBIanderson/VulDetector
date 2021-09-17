uint64_t
nstime_msec(const nstime_t *time) {
	return time->ns / MILLION;
}
