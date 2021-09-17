static void
prof_fdump(void) {
	tsd_t *tsd;
	char filename[DUMP_FILENAME_BUFSIZE];

	cassert(config_prof);
	assert(opt_prof_final);
	assert(opt_prof_prefix[0] != '\0');

	if (!prof_booted) {
		return;
	}
	tsd = tsd_fetch();
	assert(tsd_reentrancy_level_get(tsd) == 0);

	malloc_mutex_lock(tsd_tsdn(tsd), &prof_dump_seq_mtx);
	prof_dump_filename(filename, 'f', VSEQ_INVALID);
	malloc_mutex_unlock(tsd_tsdn(tsd), &prof_dump_seq_mtx);
	prof_dump(tsd, false, filename, opt_prof_leak);
}
