static void
expect_no_logging(const char *names) {
	log_var_t log_l1 = LOG_VAR_INIT("l1");
	log_var_t log_l2 = LOG_VAR_INIT("l2");
	log_var_t log_l2_a = LOG_VAR_INIT("l2.a");

	strcpy(log_var_names, names);

	int count = 0;

	for (int i = 0; i < 10; i++) {
		log_do_begin(log_l1)
			count++;
		log_do_end(log_l1)

		log_do_begin(log_l2)
			count++;
		log_do_end(log_l2)

		log_do_begin(log_l2_a)
			count++;
		log_do_end(log_l2_a)
	}
	assert_d_eq(count, 0, "Disabled logging not ignored!");
}
