static void
large_dalloc_finish_impl(tsdn_t *tsdn, arena_t *arena, extent_t *extent) {
	extent_hooks_t *extent_hooks = EXTENT_HOOKS_INITIALIZER;
	arena_extents_dirty_dalloc(tsdn, arena, &extent_hooks, extent);
}
