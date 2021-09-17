bool
extent_dss_prec_set(dss_prec_t dss_prec) {
	if (!have_dss) {
		return (dss_prec != dss_prec_disabled);
	}
	atomic_store_u(&dss_prec_default, (unsigned)dss_prec, ATOMIC_RELEASE);
	return false;
}
