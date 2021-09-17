static uint64_t
factorial(unsigned x) {
	uint64_t ret = 1;
	unsigned i;

	for (i = 2; i <= x; i++) {
		ret *= (uint64_t)i;
	}

	return ret;
}
