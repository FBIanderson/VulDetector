bool
arena_dss_prec_set(arena_t *arena, dss_prec_t dss_prec) {
	if (!have_dss) {
		return (dss_prec != dss_prec_disabled);
	}
	atomic_store_u(&arena->dss_prec, (unsigned)dss_prec, ATOMIC_RELEASE);
	return false;
}
