void
extent_dss_boot(void) {
	cassert(have_dss);

	dss_base = extent_dss_sbrk(0);
	atomic_store_b(&dss_extending, false, ATOMIC_RELAXED);
	atomic_store_b(&dss_exhausted, dss_base == (void *)-1, ATOMIC_RELAXED);
	atomic_store_p(&dss_max, dss_base, ATOMIC_RELAXED);
}
