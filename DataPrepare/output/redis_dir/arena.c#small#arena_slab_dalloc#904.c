static void
arena_slab_dalloc(tsdn_t *tsdn, arena_t *arena, extent_t *slab) {
	arena_nactive_sub(arena, extent_size_get(slab) >> LG_PAGE);

	extent_hooks_t *extent_hooks = EXTENT_HOOKS_INITIALIZER;
	arena_extents_dirty_dalloc(tsdn, arena, &extent_hooks, slab);
}
