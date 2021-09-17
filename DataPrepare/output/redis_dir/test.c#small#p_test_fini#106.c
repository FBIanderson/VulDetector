void
p_test_fini(void) {
	test_counts[test_status]++;
	malloc_printf("%s (%s): %s\n", test_name, reentrancy_t_str(reentrancy),
	    test_status_string(test_status));
}
