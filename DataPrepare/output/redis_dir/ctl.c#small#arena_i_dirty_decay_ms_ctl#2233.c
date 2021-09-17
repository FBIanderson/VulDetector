static int
arena_i_dirty_decay_ms_ctl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	return arena_i_decay_ms_ctl_impl(tsd, mib, miblen, oldp, oldlenp, newp,
	    newlen, true);
}
