void
arena_prefork3(tsdn_t *tsdn, arena_t *arena) {
	extents_prefork(tsdn, &arena->extents_dirty);
	extents_prefork(tsdn, &arena->extents_muzzy);
	extents_prefork(tsdn, &arena->extents_retained);
}
