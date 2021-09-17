TEST_BEGIN(test_sallocx_vs_nallocx) {
	compare_funcs(10*1000*1000, 100*1000*1000, "sallocx",
	    malloc_sallocx_free, "nallocx", malloc_nallocx_free);
}
