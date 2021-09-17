void
large_dalloc(tsdn_t *tsdn, extent_t *extent) {
	arena_t *arena = extent_arena_get(extent);
	large_dalloc_prep_impl(tsdn, arena, extent, false);
	large_dalloc_finish_impl(tsdn, arena, extent);
	arena_decay_tick(tsdn, arena);
}
