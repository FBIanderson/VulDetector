bool
extent_dss_mergeable(void *addr_a, void *addr_b) {
	void *max;

	cassert(have_dss);

	if ((uintptr_t)addr_a < (uintptr_t)dss_base && (uintptr_t)addr_b <
	    (uintptr_t)dss_base) {
		return true;
	}

	max = atomic_load_p(&dss_max, ATOMIC_ACQUIRE);
	return (extent_in_dss_helper(addr_a, max) ==
	    extent_in_dss_helper(addr_b, max));
}
