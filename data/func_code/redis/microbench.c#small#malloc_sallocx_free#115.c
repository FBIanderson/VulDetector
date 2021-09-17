static void
malloc_sallocx_free(void) {
	void *p;

	p = malloc(1);
	if (p == NULL) {
		test_fail("Unexpected malloc() failure");
		return;
	}
	if (sallocx(p, 0) < 1) {
		test_fail("Unexpected sallocx() failure");
	}
	free(p);
}
