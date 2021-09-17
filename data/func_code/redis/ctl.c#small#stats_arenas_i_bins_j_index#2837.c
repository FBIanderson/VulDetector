static const ctl_named_node_t *
stats_arenas_i_bins_j_index(tsdn_t *tsdn, const size_t *mib, size_t miblen,
    size_t j) {
	if (j > NBINS) {
		return NULL;
	}
	return super_stats_arenas_i_bins_j_node;
}
