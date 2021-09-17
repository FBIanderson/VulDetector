void
witnesses_cleanup(witness_tsd_t *witness_tsd) {
	witness_assert_lockless(witness_tsd_tsdn(witness_tsd));

	/* Do nothing. */
}
