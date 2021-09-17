static void *
thd_start(void *arg) {
	int d = (int)(uintptr_t)arg;
	void *p;

	tsd_t *tsd = tsd_fetch();
	assert_x_eq(tsd_test_data_get(tsd), MALLOC_TSD_TEST_DATA_INIT,
	    "Initial tsd get should return initialization value");

	p = malloc(1);
	assert_ptr_not_null(p, "Unexpected malloc() failure");

	tsd_test_data_set(tsd, d);
	assert_x_eq(tsd_test_data_get(tsd), d,
	    "After tsd set, tsd get should return value that was set");

	d = 0;
	assert_x_eq(tsd_test_data_get(tsd), (int)(uintptr_t)arg,
	    "Resetting local data should have no effect on tsd");

	tsd_test_callback_set(tsd, &data_cleanup);

	free(p);
	return NULL;
}
