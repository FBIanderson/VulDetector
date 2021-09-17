static unsigned
get_nlarge(void) {
	return get_nsizes_impl("arenas.nlextents");
}
