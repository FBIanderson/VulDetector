static int
prof_gctx_comp(const prof_gctx_t *a, const prof_gctx_t *b) {
	unsigned a_len = a->bt.len;
	unsigned b_len = b->bt.len;
	unsigned comp_len = (a_len < b_len) ? a_len : b_len;
	int ret = memcmp(a->bt.vec, b->bt.vec, comp_len * sizeof(void *));
	if (ret == 0) {
		ret = (a_len > b_len) - (a_len < b_len);
	}
	return ret;
}
