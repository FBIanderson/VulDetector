static bool
extent_merge_default_impl(void *addr_a, void *addr_b) {
	if (!maps_coalesce) {
		return true;
	}
	if (have_dss && !extent_dss_mergeable(addr_a, addr_b)) {
		return true;
	}

	return false;
}
