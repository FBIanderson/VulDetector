static void
zone_force_unlock(malloc_zone_t *zone) {
	/*
	 * zone_force_lock and zone_force_unlock are the entry points to the
	 * forking machinery on OS X.  The tricky thing is, the child is not
	 * allowed to unlock mutexes locked in the parent, even if owned by the
	 * forking thread (and the mutex type we use in OS X will fail an assert
	 * if we try).  In the child, we can get away with reinitializing all
	 * the mutexes, which has the effect of unlocking them.  In the parent,
	 * doing this would mean we wouldn't wake any waiters blocked on the
	 * mutexes we unlock.  So, we record the pid of the current thread in
	 * zone_force_lock, and use that to detect if we're in the parent or
	 * child here, to decide which unlock logic we need.
	 */
	if (isthreaded) {
		assert(zone_force_lock_pid != -1);
		if (getpid() == zone_force_lock_pid) {
			jemalloc_postfork_parent();
		} else {
			jemalloc_postfork_child();
		}
		zone_force_lock_pid = -1;
	}
}
