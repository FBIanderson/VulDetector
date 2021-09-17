static test_status_t
p_test_impl(bool do_malloc_init, bool do_reentrant, test_t *t, va_list ap) {
	test_status_t ret;

	if (do_malloc_init) {
		/*
		 * Make sure initialization occurs prior to running tests.
		 * Tests are special because they may use internal facilities
		 * prior to triggering initialization as a side effect of
		 * calling into the public API.
		 */
		if (nallocx(1, 0) == 0) {
			malloc_printf("Initialization error");
			return test_status_fail;
		}
	}

	ret = test_status_pass;
	for (; t != NULL; t = va_arg(ap, test_t *)) {
		/* Non-reentrant run. */
		reentrancy = non_reentrant;
		hooks_arena_new_hook = hooks_libc_hook = NULL;
		t();
		if (test_status > ret) {
			ret = test_status;
		}
		/* Reentrant run. */
		if (do_reentrant) {
			reentrancy = libc_reentrant;
			hooks_arena_new_hook = NULL;
			hooks_libc_hook = &libc_reentrancy_hook;
			t();
			if (test_status > ret) {
				ret = test_status;
			}

			reentrancy = arena_new_reentrant;
			hooks_libc_hook = NULL;
			hooks_arena_new_hook = &arena_new_reentrancy_hook;
			t();
			if (test_status > ret) {
				ret = test_status;
			}
		}
	}

	malloc_printf("--- %s: %u/%u, %s: %u/%u, %s: %u/%u ---\n",
	    test_status_string(test_status_pass),
	    test_counts[test_status_pass], test_count,
	    test_status_string(test_status_skip),
	    test_counts[test_status_skip], test_count,
	    test_status_string(test_status_fail),
	    test_counts[test_status_fail], test_count);

	return ret;
}
