static void
extent_dss_extending_finish(void) {
	assert(atomic_load_b(&dss_extending, ATOMIC_RELAXED));

	atomic_store_b(&dss_extending, false, ATOMIC_RELEASE);
}
