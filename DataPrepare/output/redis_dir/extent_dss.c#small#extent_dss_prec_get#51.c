dss_prec_t
extent_dss_prec_get(void) {
	dss_prec_t ret;

	if (!have_dss) {
		return dss_prec_disabled;
	}
	ret = (dss_prec_t)atomic_load_u(&dss_prec_default, ATOMIC_ACQUIRE);
	return ret;
}
