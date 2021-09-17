static void
malloc_sdallocx(void) {
	void *p = malloc(1);
	if (p == NULL) {
		test_fail("Unexpected malloc() failure");
		return;
	}
	sdallocx(p, 1, 0);
}
