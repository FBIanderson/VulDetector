static bool
nstime_monotonic_impl(void) {
	return NSTIME_MONOTONIC;
#undef NSTIME_MONOTONIC
}
