void
tcache_arena_reassociate(tsdn_t *tsdn, tcache_t *tcache, arena_t *arena) {
	tcache_arena_dissociate(tsdn, tcache);
	tcache_arena_associate(tsdn, tcache, arena);
}
