void
prof_idump(tsdn_t *tsdn) {
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
		tdata->enq_idump = true;
		return;
	}

	if (opt_prof_prefix[0] != '\0') {
		char filename[PATH_MAX + 1];
		malloc_mutex_lock(tsd_tsdn(tsd), &prof_dump_seq_mtx);
		prof_dump_filename(filename, 'i', prof_dump_iseq);
		prof_dump_iseq++;
		malloc_mutex_unlock(tsd_tsdn(tsd), &prof_dump_seq_mtx);
		prof_dump(tsd, false, filename, false);
	}
}
