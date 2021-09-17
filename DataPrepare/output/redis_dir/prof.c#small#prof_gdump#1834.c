void
prof_gdump(tsdn_t *tsdn) {
	tsd_t *tsd;
	prof_tdata_t *tdata;

	cassert(config_prof);

	if (!prof_booted || tsdn_null(tsdn) || !prof_active_get_unlocked()) {
		return;
	}
	tsd = tsdn_tsd(tsdn);
	if (tsd_reentrancy_level_get(tsd) > 0) {
		return;
	}

	tdata = prof_tdata_get(tsd, false);
	if (tdata == NULL) {
		return;
	}
	if (tdata->enq) {
		tdata->enq_gdump = true;
		return;
	}

	if (opt_prof_prefix[0] != '\0') {
		char filename[DUMP_FILENAME_BUFSIZE];
		malloc_mutex_lock(tsdn, &prof_dump_seq_mtx);
		prof_dump_filename(filename, 'u', prof_dump_useq);
		prof_dump_useq++;
		malloc_mutex_unlock(tsdn, &prof_dump_seq_mtx);
		prof_dump(tsd, false, filename, false);
	}
}
