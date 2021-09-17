TEST_BEGIN(test_pt_norm) {
	unsigned i;

	for (i = 1; i < sizeof(pt_norm_expected)/sizeof(double); i++) {
		double p = (double)i * 0.01;
		assert_true(double_eq_rel(pt_norm(p), pt_norm_expected[i],
		    MAX_REL_ERR, MAX_ABS_ERR),
		    "Incorrect pt_norm result for i=%u", i);
	}
}
