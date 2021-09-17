static void
ctl_arena_refresh(tsdn_t *tsdn, arena_t *arena, ctl_arena_t *ctl_sdarena,
    unsigned i, bool destroyed) {
	ctl_arena_t *ctl_arena = arenas_i(i);

	ctl_arena_clear(ctl_arena);
	ctl_arena_stats_amerge(tsdn, ctl_arena, arena);
	/* Merge into sum stats as well. */
	ctl_arena_stats_sdmerge(ctl_sdarena, ctl_arena, destroyed);
}
