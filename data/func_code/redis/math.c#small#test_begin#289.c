TEST_BEGIN(test_pt_chi2) {
	unsigned i, j;
	unsigned e = 0;

	for (i = 0; i < sizeof(pt_chi2_df)/sizeof(double); i++) {
		double df = pt_chi2_df[i];
		double ln_gamma_df = ln_gamma(df * 0.5);
		for (j = 1; j < 100; j += 7) {
			double p = (double)j * 0.01;
			assert_true(double_eq_rel(pt_chi2(p, df, ln_gamma_df),
			    pt_chi2_expected[e], MAX_REL_ERR, MAX_ABS_ERR),
			    "Incorrect pt_chi2 result for i=%u, j=%u", i, j);
			e++;
		}
	}
}
