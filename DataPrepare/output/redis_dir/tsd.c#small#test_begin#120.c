TEST_BEGIN(test_tsd_reincarnation) {
	thd_t thd;
	thd_create(&thd, thd_start_reincarnated, NULL);
	thd_join(thd, NULL);
}
