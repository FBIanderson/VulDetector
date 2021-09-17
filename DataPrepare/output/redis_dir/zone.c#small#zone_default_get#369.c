static malloc_zone_t *
zone_default_get(void) {
	malloc_zone_t **zones = NULL;
	unsigned int num_zones = 0;

	/*
	 * On OSX 10.12, malloc_default_zone returns a special zone that is not
	 * present in the list of registered zones. That zone uses a "lite zone"
	 * if one is present (apparently enabled when malloc stack logging is
	 * enabled), or the first registered zone otherwise. In practice this
	 * means unless malloc stack logging is enabled, the first registered
	 * zone is the default.  So get the list of zones to get the first one,
	 * instead of relying on malloc_default_zone.
	 */
	if (KERN_SUCCESS != malloc_get_all_zones(0, NULL,
	    (vm_address_t**)&zones, &num_zones)) {
		/*
		 * Reset the value in case the failure happened after it was
		 * set.
		 */
		num_zones = 0;
	}

	if (num_zones) {
		return zones[0];
	}

	return malloc_default_zone();
}
