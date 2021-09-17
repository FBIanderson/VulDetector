static void
extent_hooks_assure_initialized(arena_t *arena,
    extent_hooks_t **r_extent_hooks) {
	if (*r_extent_hooks == EXTENT_HOOKS_INITIALIZER) {
		*r_extent_hooks = extent_hooks_get(arena);
	}
}
