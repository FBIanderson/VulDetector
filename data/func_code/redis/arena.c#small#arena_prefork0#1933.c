void
arena_prefork0(tsdn_t *tsdn, arena_t *arena) {
	malloc_mutex_prefork(tsdn, &arena->decay_dirty.mtx);
	malloc_mutex_prefork(tsdn, &arena->decay_muzzy.mtx);
}
