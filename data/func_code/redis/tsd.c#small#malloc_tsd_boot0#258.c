tsd_t *
malloc_tsd_boot0(void) {
	tsd_t *tsd;

	ncleanups = 0;
	if (tsd_boot0()) {
		return NULL;
	}
	tsd = tsd_fetch();
	*tsd_arenas_tdata_bypassp_get(tsd) = true;
	return tsd;
}
