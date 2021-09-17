static void
base_extent_init(size_t *extent_sn_next, extent_t *extent, void *addr,
    size_t size) {
	size_t sn;

	sn = *extent_sn_next;
	(*extent_sn_next)++;

	extent_binit(extent, addr, size, sn);
}
