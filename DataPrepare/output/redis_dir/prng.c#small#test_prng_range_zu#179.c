static void
test_prng_range_zu(bool atomic) {
	size_t range;
#define MAX_RANGE	10000000
#define RANGE_STEP	97
#define NREPS		10

	for (range = 2; range < MAX_RANGE; range += RANGE_STEP) {
		atomic_zu_t s;
		unsigned rep;

		atomic_store_zu(&s, range, ATOMIC_RELAXED);
		for (rep = 0; rep < NREPS; rep++) {
			size_t r = prng_range_zu(&s, range, atomic);

			assert_zu_lt(r, range, "Out of range");
		}
	}
}
