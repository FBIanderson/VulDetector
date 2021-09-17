static bool
prof_tdata_should_destroy_unlocked(prof_tdata_t *tdata, bool even_if_attached) {
	if (tdata->attached && !even_if_attached) {
		return false;
	}
	if (ckh_count(&tdata->bt2tctx) != 0) {
		return false;
	}
	return true;
}
