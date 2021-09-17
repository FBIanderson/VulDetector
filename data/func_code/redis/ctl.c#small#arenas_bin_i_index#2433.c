static const ctl_named_node_t *
arenas_bin_i_index(tsdn_t *tsdn, const size_t *mib, size_t miblen, size_t i) {
	if (i > NBINS) {
		return NULL;
	}
	return super_arenas_bin_i_node;
}
