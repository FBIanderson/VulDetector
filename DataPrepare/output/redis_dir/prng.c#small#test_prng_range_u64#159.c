static void
test_prng_range_u64(void) {
	uint64_t range;
#define MAX_RANGE	10000000
#define RANGE_STEP	97
#define NREPS		10

	for (range = 2; range < MAX_RANGE; range += RANGE_STEP) {
		uint64_t s;
		unsigned rep;

		s = range;
		for (rep = 0; rep < NREPS; rep++) {
			uint64_t r = prng_range_u64(&s, range);

			assert_u64_lt(r, range, "Out of range");
		}
	}
}
