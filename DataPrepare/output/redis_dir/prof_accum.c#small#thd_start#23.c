static void *
thd_start(void *varg) {
	unsigned thd_ind = *(unsigned *)varg;
	size_t bt_count_prev, bt_count;
	unsigned i_prev, i;

	i_prev = 0;
	bt_count_prev = 0;
	for (i = 0; i < NALLOCS_PER_THREAD; i++) {
		void *p = alloc_from_permuted_backtrace(thd_ind, i);
		dallocx(p, 0);
		if (i % DUMP_INTERVAL == 0) {
			assert_d_eq(mallctl("prof.dump", NULL, NULL, NULL, 0),
			    0, "Unexpected error while dumping heap profile");
		}

		if (i % BT_COUNT_CHECK_INTERVAL == 0 ||
		    i+1 == NALLOCS_PER_THREAD) {
			bt_count = prof_bt_count();
			assert_zu_le(bt_count_prev+(i-i_prev), bt_count,
			    "Expected larger backtrace count increase");
			i_prev = i;
			bt_count_prev = bt_count;
		}
	}

	return NULL;
}
