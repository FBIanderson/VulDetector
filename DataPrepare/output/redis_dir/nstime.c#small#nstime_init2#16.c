void
nstime_init2(nstime_t *time, uint64_t sec, uint64_t nsec) {
	time->ns = sec * BILLION + nsec;
}
