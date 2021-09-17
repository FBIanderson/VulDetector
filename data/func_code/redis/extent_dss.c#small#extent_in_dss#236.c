bool
extent_in_dss(void *addr) {
	cassert(have_dss);

	return extent_in_dss_helper(addr, atomic_load_p(&dss_max,
	    ATOMIC_ACQUIRE));
}
