extent_hooks_t *
extent_hooks_get(arena_t *arena) {
	return base_extent_hooks_get(arena->base);
}
