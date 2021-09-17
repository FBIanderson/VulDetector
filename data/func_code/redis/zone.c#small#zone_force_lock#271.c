static void
zone_force_lock(malloc_zone_t *zone) {
	if (isthreaded) {
		/*
		 * See the note in zone_force_unlock, below, to see why we need
		 * this.
		 */
		assert(zone_force_lock_pid == -1);
		zone_force_lock_pid = getpid();
		jemalloc_prefork();
	}
}
