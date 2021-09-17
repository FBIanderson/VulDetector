TEST_BEGIN(test_mtx_basic) {
	mtx_t mtx;

	assert_false(mtx_init(&mtx), "Unexpected mtx_init() failure");
	mtx_lock(&mtx);
	mtx_unlock(&mtx);
	mtx_fini(&mtx);
}
