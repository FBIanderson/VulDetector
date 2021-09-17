TEST_BEGIN(test_pt_gamma_shape) {
	unsigned i, j;
	unsigned e = 0;

	for (i = 0; i < sizeof(pt_gamma_shape)/sizeof(double); i++) {
		double shape = pt_gamma_shape[i];
		double ln_gamma_shape = ln_gamma(shape);
		for (j = 1; j < 100; j += 7) {
			double p = (double)j * 0.01;
			assert_true(double_eq_rel(pt_gamma(p, shape, 1.0,
			    ln_gamma_shape), pt_gamma_expected[e], MAX_REL_ERR,
			    MAX_ABS_ERR),
			    "Incorrect pt_gamma result for i=%u, j=%u", i, j);
			e++;
		}
	}
}
