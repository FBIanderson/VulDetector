TEST_BEGIN(test_ln_gamma_misc) {
	unsigned i;

	for (i = 1; i < sizeof(ln_gamma_misc_expected)/sizeof(double); i++) {
		double x = (double)i * 0.25;
		assert_true(double_eq_rel(ln_gamma(x),
		    ln_gamma_misc_expected[i], MAX_REL_ERR, MAX_ABS_ERR),
		    "Incorrect ln_gamma result for i=%u", i);
	}
}
