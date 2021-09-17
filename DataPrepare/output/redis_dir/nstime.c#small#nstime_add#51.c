void
nstime_add(nstime_t *time, const nstime_t *addend) {
	assert(UINT64_MAX - time->ns >= addend->ns);

	time->ns += addend->ns;
}
