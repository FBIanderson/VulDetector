JEMALLOC_ATTR(constructor)
void
zone_register(void) {
	/*
	 * If something else replaced the system default zone allocator, don't
	 * register jemalloc's.
	 */
	default_zone = zone_default_get();
	if (!default_zone->zone_name || strcmp(default_zone->zone_name,
	    "DefaultMallocZone") != 0) {
		return;
	}

	/*
	 * The default purgeable zone is created lazily by OSX's libc.  It uses
	 * the default zone when it is created for "small" allocations
	 * (< 15 KiB), but assumes the default zone is a scalable_zone.  This
	 * obviously fails when the default zone is the jemalloc zone, so
	 * malloc_default_purgeable_zone() is called beforehand so that the
	 * default purgeable zone is created when the default zone is still
	 * a scalable_zone.  As purgeable zones only exist on >= 10.6, we need
	 * to check for the existence of malloc_default_purgeable_zone() at
	 * run time.
	 */
	purgeable_zone = (malloc_default_purgeable_zone == NULL) ? NULL :
	    malloc_default_purgeable_zone();

	/* Register the custom zone.  At this point it won't be the default. */
	zone_init();
	malloc_zone_register(&jemalloc_zone);

	/* Promote the custom zone to be default. */
	zone_promote();
}
