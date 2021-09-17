TEST_BEGIN(test_basic) {
	void *ptr = mallocx(64, 0);
	sdallocx(ptr, 64, 0);
}
