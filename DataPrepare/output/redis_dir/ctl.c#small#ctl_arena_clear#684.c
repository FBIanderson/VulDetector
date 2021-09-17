static void
ctl_arena_clear(ctl_arena_t *ctl_arena) {
	ctl_arena->nthreads = 0;
	ctl_arena->dss = dss_prec_names[dss_prec_limit];
	ctl_arena->dirty_decay_ms = -1;
	ctl_arena->muzzy_decay_ms = -1;
	ctl_arena->pactive = 0;
	ctl_arena->pdirty = 0;
	ctl_arena->pmuzzy = 0;
	if (config_stats) {
		memset(&ctl_arena->astats->astats, 0, sizeof(arena_stats_t));
		ctl_arena->astats->allocated_small = 0;
		ctl_arena->astats->nmalloc_small = 0;
		ctl_arena->astats->ndalloc_small = 0;
		ctl_arena->astats->nrequests_small = 0;
		memset(ctl_arena->astats->bstats, 0, NBINS *
		    sizeof(bin_stats_t));
		memset(ctl_arena->astats->lstats, 0, (NSIZES - NBINS) *
		    sizeof(arena_stats_large_t));
	}
}
