static void *
extent_dss_max_update(void *new_addr) {
	/*
	 * Get the current end of the DSS as max_cur and assure that dss_max is
	 * up to date.
	 */
	void *max_cur = extent_dss_sbrk(0);
	if (max_cur == (void *)-1) {
		return NULL;
	}
	atomic_store_p(&dss_max, max_cur, ATOMIC_RELEASE);
	/* Fixed new_addr can only be supported if it is at the edge of DSS. */
	if (new_addr != NULL && max_cur != new_addr) {
		return NULL;
	}
	return max_cur;
}
