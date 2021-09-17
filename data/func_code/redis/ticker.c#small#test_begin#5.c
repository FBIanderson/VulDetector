TEST_BEGIN(test_ticker_tick) {
#define NREPS 2
#define NTICKS 3
	ticker_t ticker;
	int32_t i, j;

	ticker_init(&ticker, NTICKS);
	for (i = 0; i < NREPS; i++) {
		for (j = 0; j < NTICKS; j++) {
			assert_u_eq(ticker_read(&ticker), NTICKS - j,
			    "Unexpected ticker value (i=%d, j=%d)", i, j);
			assert_false(ticker_tick(&ticker),
			    "Unexpected ticker fire (i=%d, j=%d)", i, j);
		}
		assert_u32_eq(ticker_read(&ticker), 0,
		    "Expected ticker depletion");
		assert_true(ticker_tick(&ticker),
		    "Expected ticker fire (i=%d)", i);
		assert_u32_eq(ticker_read(&ticker), NTICKS,
		    "Expected ticker reset");
	}
#undef NTICKS
}
