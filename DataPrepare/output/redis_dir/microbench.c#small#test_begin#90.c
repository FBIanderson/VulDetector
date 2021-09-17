TEST_BEGIN(test_free_vs_dallocx) {
	compare_funcs(10*1000*1000, 100*1000*1000, "free", malloc_free,
	    "dallocx", malloc_dallocx);
}
