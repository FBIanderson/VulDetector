static void
mallocx_free(void) {
	void *p = mallocx(1, 0);
	if (p == NULL) {
		test_fail("Unexpected mallocx() failure");
		return;
	}
	free(p);
}
