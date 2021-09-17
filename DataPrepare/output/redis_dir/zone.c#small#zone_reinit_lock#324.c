static void
zone_reinit_lock(malloc_zone_t *zone) {
	/* As of OSX 10.12, this function is only used when force_unlock would
	 * be used if the zone version were < 9. So just use force_unlock. */
	zone_force_unlock(zone);
}
