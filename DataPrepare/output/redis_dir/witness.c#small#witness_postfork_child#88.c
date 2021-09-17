void
witness_postfork_child(witness_tsd_t *witness_tsd) {
	if (!config_debug) {
		return;
	}
#ifndef JEMALLOC_MUTEX_INIT_CB
	witness_list_t *witnesses;

	witnesses = &witness_tsd->witnesses;
	ql_new(witnesses);
#endif
	witness_tsd->forking = false;
}
