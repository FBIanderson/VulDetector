static void *
extent_dss_sbrk(intptr_t increment) {
#ifdef JEMALLOC_DSS
	return sbrk(increment);
#else
	not_implemented();
	return NULL;
#endif
}
