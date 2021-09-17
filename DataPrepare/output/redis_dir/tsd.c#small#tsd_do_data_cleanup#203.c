static void
tsd_do_data_cleanup(tsd_t *tsd) {
	prof_tdata_cleanup(tsd);
	iarena_cleanup(tsd);
	arena_cleanup(tsd);
	arenas_tdata_cleanup(tsd);
	tcache_cleanup(tsd);
	witnesses_cleanup(tsd_witness_tsdp_get_unsafe(tsd));
}
