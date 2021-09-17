static void
assert_tsd_data_cleanup_done(tsd_t *tsd) {
	assert(!tsd_nominal(tsd));
	assert(*tsd_arenap_get_unsafe(tsd) == NULL);
	assert(*tsd_iarenap_get_unsafe(tsd) == NULL);
	assert(*tsd_arenas_tdata_bypassp_get_unsafe(tsd) == true);
	assert(*tsd_arenas_tdatap_get_unsafe(tsd) == NULL);
	assert(*tsd_tcache_enabledp_get_unsafe(tsd) == false);
	assert(*tsd_prof_tdatap_get_unsafe(tsd) == NULL);
}
