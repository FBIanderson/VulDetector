void
malloc_tsd_boot1(void) {
	tsd_boot1();
	tsd_t *tsd = tsd_fetch();
	/* malloc_slow has been set properly.  Update tsd_slow. */
	tsd_slow_update(tsd);
	*tsd_arenas_tdata_bypassp_get(tsd) = false;
}
