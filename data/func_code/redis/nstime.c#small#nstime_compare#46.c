int
nstime_compare(const nstime_t *a, const nstime_t *b) {
	return (a->ns > b->ns) - (a->ns < b->ns);
}
