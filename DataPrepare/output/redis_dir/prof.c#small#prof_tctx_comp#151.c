static int
prof_tctx_comp(const prof_tctx_t *a, const prof_tctx_t *b) {
	uint64_t a_thr_uid = a->thr_uid;
	uint64_t b_thr_uid = b->thr_uid;
	int ret = (a_thr_uid > b_thr_uid) - (a_thr_uid < b_thr_uid);
	if (ret == 0) {
		uint64_t a_thr_discrim = a->thr_discrim;
		uint64_t b_thr_discrim = b->thr_discrim;
		ret = (a_thr_discrim > b_thr_discrim) - (a_thr_discrim <
		    b_thr_discrim);
		if (ret == 0) {
			uint64_t a_tctx_uid = a->tctx_uid;
			uint64_t b_tctx_uid = b->tctx_uid;
			ret = (a_tctx_uid > b_tctx_uid) - (a_tctx_uid <
			    b_tctx_uid);
		}
	}
	return ret;
}
