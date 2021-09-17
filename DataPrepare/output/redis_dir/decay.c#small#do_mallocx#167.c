static void *
do_mallocx(size_t size, int flags) {
	void *p = mallocx(size, flags);
	assert_ptr_not_null(p, "Unexpected mallocx() failure");
	return p;
}
