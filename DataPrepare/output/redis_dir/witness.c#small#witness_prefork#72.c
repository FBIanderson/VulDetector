void
witness_prefork(witness_tsd_t *witness_tsd) {
	if (!config_debug) {
		return;
	}
	witness_tsd->forking = true;
}
