TEST_BEGIN(test_smoothstep_integral) {
	uint64_t sum, min, max;
	unsigned i;

	/*
	 * The integral of smoothstep in the [0..1] range equals 1/2.  Verify
	 * that the fixed point representation's integral is no more than
	 * rounding error distant from 1/2.  Regarding rounding, each table
	 * element is rounded down to the nearest fixed point value, so the
	 * integral may be off by as much as SMOOTHSTEP_NSTEPS ulps.
	 */
	sum = 0;
	for (i = 0; i < SMOOTHSTEP_NSTEPS; i++) {
		sum += smoothstep_tab[i];
	}

	max = (KQU(1) << (SMOOTHSTEP_BFP-1)) * (SMOOTHSTEP_NSTEPS+1);
	min = max - SMOOTHSTEP_NSTEPS;

	assert_u64_ge(sum, min,
	    "Integral too small, even accounting for truncation");
	assert_u64_le(sum, max, "Integral exceeds 1/2");
	if (false) {
		malloc_printf("%"FMTu64" ulps under 1/2 (limit %d)\n",
		    max - sum, SMOOTHSTEP_NSTEPS);
	}
}
