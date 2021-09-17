static void
ctl_arena_stats_amerge(tsdn_t *tsdn, ctl_arena_t *ctl_arena, arena_t *arena) {
	unsigned i;

	if (config_stats) {
		arena_stats_merge(tsdn, arena, &ctl_arena->nthreads,
		    &ctl_arena->dss, &ctl_arena->dirty_decay_ms,
		    &ctl_arena->muzzy_decay_ms, &ctl_arena->pactive,
		    &ctl_arena->pdirty, &ctl_arena->pmuzzy,
		    &ctl_arena->astats->astats, ctl_arena->astats->bstats,
		    ctl_arena->astats->lstats);

		for (i = 0; i < NBINS; i++) {
			ctl_arena->astats->allocated_small +=
			    ctl_arena->astats->bstats[i].curregs *
			    sz_index2size(i);
			ctl_arena->astats->nmalloc_small +=
			    ctl_arena->astats->bstats[i].nmalloc;
			ctl_arena->astats->ndalloc_small +=
			    ctl_arena->astats->bstats[i].ndalloc;
			ctl_arena->astats->nrequests_small +=
			    ctl_arena->astats->bstats[i].nrequests;
		}
	} else {
		arena_basic_stats_merge(tsdn, arena, &ctl_arena->nthreads,
		    &ctl_arena->dss, &ctl_arena->dirty_decay_ms,
		    &ctl_arena->muzzy_decay_ms, &ctl_arena->pactive,
		    &ctl_arena->pdirty, &ctl_arena->pmuzzy);
	}
}
