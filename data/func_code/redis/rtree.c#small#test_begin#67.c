TEST_BEGIN(test_rtree_read_empty) {
	tsdn_t *tsdn;

	tsdn = tsdn_fetch();

	rtree_t *rtree = &test_rtree;
	rtree_ctx_t rtree_ctx;
	rtree_ctx_data_init(&rtree_ctx);
	assert_false(rtree_new(rtree, false), "Unexpected rtree_new() failure");
	assert_ptr_null(rtree_extent_read(tsdn, rtree, &rtree_ctx, PAGE,
	    false), "rtree_extent_read() should return NULL for empty tree");
	rtree_delete(tsdn, rtree);
}
