static const ctl_named_node_t *
arenas_lextent_i_index(tsdn_t *tsdn, const size_t *mib, size_t miblen,
    size_t i) {
	if (i > NSIZES - NBINS) {
		return NULL;
	}
	return super_arenas_lextent_i_node;
}
