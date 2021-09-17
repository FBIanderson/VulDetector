static void
large_dalloc_maybe_junk_impl(void *ptr, size_t size) {
	if (config_fill && have_dss && unlikely(opt_junk_free)) {
		/*
		 * Only bother junk filling if the extent isn't about to be
		 * unmapped.
		 */
		if (opt_retain || (have_dss && extent_in_dss(ptr))) {
			large_dalloc_junk(ptr, size);
		}
	}
}
