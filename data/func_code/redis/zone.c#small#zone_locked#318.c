static boolean_t
zone_locked(malloc_zone_t *zone) {
	/* Pretend no lock is being held */
	return false;
}
