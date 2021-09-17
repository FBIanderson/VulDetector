static const ctl_named_node_t *
stats_arenas_i_lextents_j_index(tsdn_t *tsdn, const size_t *mib, size_t miblen,
    size_t j) {
	if (j > NSIZES - NBINS) {
		return NULL;
	}
	return super_stats_arenas_i_lextents_j_node;
}
