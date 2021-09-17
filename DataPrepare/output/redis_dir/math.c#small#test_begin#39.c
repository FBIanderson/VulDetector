TEST_BEGIN(test_ln_gamma_factorial) {
	unsigned x;

	/* exp(ln_gamma(x)) == (x-1)! for integer x. */
	for (x = 1; x <= 21; x++) {
		assert_true(double_eq_rel(exp(ln_gamma(x)),
		    (double)factorial(x-1), MAX_REL_ERR, MAX_ABS_ERR),
		    "Incorrect factorial result for x=%u", x);
	}
}
