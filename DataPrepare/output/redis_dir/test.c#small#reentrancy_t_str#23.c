static const char *
reentrancy_t_str(reentrancy_t r) {
	switch (r) {
	case non_reentrant:
		return "non-reentrant";
	case libc_reentrant:
		return "libc-reentrant";
	case arena_new_reentrant:
		return "arena_new-reentrant";
	default:
		unreachable();
	}
}
