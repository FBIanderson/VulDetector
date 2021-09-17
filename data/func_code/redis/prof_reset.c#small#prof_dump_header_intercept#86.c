static bool
prof_dump_header_intercept(tsdn_t *tsdn, bool propagate_err,
    const prof_cnt_t *cnt_all) {
	prof_dump_header_intercepted = true;
	memcpy(&cnt_all_copy, cnt_all, sizeof(prof_cnt_t));

	return false;
}
