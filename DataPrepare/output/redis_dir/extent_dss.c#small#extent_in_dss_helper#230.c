static bool
extent_in_dss_helper(void *addr, void *max) {
	return ((uintptr_t)addr >= (uintptr_t)dss_base && (uintptr_t)addr <
	    (uintptr_t)max);
}
