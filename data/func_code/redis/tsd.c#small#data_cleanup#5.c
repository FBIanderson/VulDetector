void
data_cleanup(int *data) {
	if (data_cleanup_count == 0) {
		assert_x_eq(*data, MALLOC_TSD_TEST_DATA_INIT,
		    "Argument passed into cleanup function should match tsd "
		    "value");
	}
	++data_cleanup_count;

	/*
	 * Allocate during cleanup for two rounds, in order to assure that
	 * jemalloc's internal tsd reinitialization happens.
	 */
	bool reincarnate = false;
	switch (*data) {
	case MALLOC_TSD_TEST_DATA_INIT:
		*data = 1;
		reincarnate = true;
		break;
	case 1:
		*data = 2;
		reincarnate = true;
		break;
	case 2:
		return;
	default:
		not_reached();
	}

	if (reincarnate) {
		void *p = mallocx(1, 0);
		assert_ptr_not_null(p, "Unexpeced mallocx() failure");
		dallocx(p, 0);
	}
}
