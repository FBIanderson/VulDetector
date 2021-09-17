void
witness_postfork_parent(witness_tsd_t *witness_tsd) {
	if (!config_debug) {
		return;
	}
	witness_tsd->forking = false;
}
