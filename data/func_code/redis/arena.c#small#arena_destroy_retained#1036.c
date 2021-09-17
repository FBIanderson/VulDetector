static void
arena_destroy_retained(tsdn_t *tsdn, arena_t *arena) {
	/*
	 * Iterate over the retained extents and destroy them.  This gives the
	 * extent allocator underlying the extent hooks an opportunity to unmap
	 * all retained memory without having to keep its own metadata
	 * structures.  In practice, virtual memory for dss-allocated extents is
	 * leaked here, so best practice is to avoid dss for arenas to be
	 * destroyed, or provide custom extent hooks that track retained
	 * dss-based extents for later reuse.
	 */
	extent_hooks_t *extent_hooks = extent_hooks_get(arena);
	extent_t *extent;
	while ((extent = extents_evict(tsdn, arena, &extent_hooks,
	    &arena->extents_retained, 0)) != NULL) {
		extent_destroy_wrapper(tsdn, arena, &extent_hooks, extent);
	}
}
