static void
ctl_arena_stats_sdmerge(ctl_arena_t *ctl_sdarena, ctl_arena_t *ctl_arena,
    bool destroyed) {
	unsigned i;

	if (!destroyed) {
		ctl_sdarena->nthreads += ctl_arena->nthreads;
		ctl_sdarena->pactive += ctl_arena->pactive;
		ctl_sdarena->pdirty += ctl_arena->pdirty;
		ctl_sdarena->pmuzzy += ctl_arena->pmuzzy;
	} else {
		assert(ctl_arena->nthreads == 0);
		assert(ctl_arena->pactive == 0);
		assert(ctl_arena->pdirty == 0);
		assert(ctl_arena->pmuzzy == 0);
	}

	if (config_stats) {
		ctl_arena_stats_t *sdstats = ctl_sdarena->astats;
		ctl_arena_stats_t *astats = ctl_arena->astats;

		if (!destroyed) {
			accum_atomic_zu(&sdstats->astats.mapped,
			    &astats->astats.mapped);
			accum_atomic_zu(&sdstats->astats.retained,
			    &astats->astats.retained);
		}

		ctl_accum_arena_stats_u64(&sdstats->astats.decay_dirty.npurge,
		    &astats->astats.decay_dirty.npurge);
		ctl_accum_arena_stats_u64(&sdstats->astats.decay_dirty.nmadvise,
		    &astats->astats.decay_dirty.nmadvise);
		ctl_accum_arena_stats_u64(&sdstats->astats.decay_dirty.purged,
		    &astats->astats.decay_dirty.purged);

		ctl_accum_arena_stats_u64(&sdstats->astats.decay_muzzy.npurge,
		    &astats->astats.decay_muzzy.npurge);
		ctl_accum_arena_stats_u64(&sdstats->astats.decay_muzzy.nmadvise,
		    &astats->astats.decay_muzzy.nmadvise);
		ctl_accum_arena_stats_u64(&sdstats->astats.decay_muzzy.purged,
		    &astats->astats.decay_muzzy.purged);

#define OP(mtx) malloc_mutex_prof_merge(				\
		    &(sdstats->astats.mutex_prof_data[			\
		        arena_prof_mutex_##mtx]),			\
		    &(astats->astats.mutex_prof_data[			\
		        arena_prof_mutex_##mtx]));
MUTEX_PROF_ARENA_MUTEXES
#undef OP
		if (!destroyed) {
			accum_atomic_zu(&sdstats->astats.base,
			    &astats->astats.base);
			accum_atomic_zu(&sdstats->astats.internal,
			    &astats->astats.internal);
			accum_atomic_zu(&sdstats->astats.resident,
			    &astats->astats.resident);
			accum_atomic_zu(&sdstats->astats.metadata_thp,
			    &astats->astats.metadata_thp);
		} else {
			assert(atomic_load_zu(
			    &astats->astats.internal, ATOMIC_RELAXED) == 0);
		}

		if (!destroyed) {
			sdstats->allocated_small += astats->allocated_small;
		} else {
			assert(astats->allocated_small == 0);
		}
		sdstats->nmalloc_small += astats->nmalloc_small;
		sdstats->ndalloc_small += astats->ndalloc_small;
		sdstats->nrequests_small += astats->nrequests_small;

		if (!destroyed) {
			accum_atomic_zu(&sdstats->astats.allocated_large,
			    &astats->astats.allocated_large);
		} else {
			assert(atomic_load_zu(&astats->astats.allocated_large,
			    ATOMIC_RELAXED) == 0);
		}
		ctl_accum_arena_stats_u64(&sdstats->astats.nmalloc_large,
		    &astats->astats.nmalloc_large);
		ctl_accum_arena_stats_u64(&sdstats->astats.ndalloc_large,
		    &astats->astats.ndalloc_large);
		ctl_accum_arena_stats_u64(&sdstats->astats.nrequests_large,
		    &astats->astats.nrequests_large);

		accum_atomic_zu(&sdstats->astats.tcache_bytes,
		    &astats->astats.tcache_bytes);

		if (ctl_arena->arena_ind == 0) {
			sdstats->astats.uptime = astats->astats.uptime;
		}

		for (i = 0; i < NBINS; i++) {
			sdstats->bstats[i].nmalloc += astats->bstats[i].nmalloc;
			sdstats->bstats[i].ndalloc += astats->bstats[i].ndalloc;
			sdstats->bstats[i].nrequests +=
			    astats->bstats[i].nrequests;
			if (!destroyed) {
				sdstats->bstats[i].curregs +=
				    astats->bstats[i].curregs;
			} else {
				assert(astats->bstats[i].curregs == 0);
			}
			sdstats->bstats[i].nfills += astats->bstats[i].nfills;
			sdstats->bstats[i].nflushes +=
			    astats->bstats[i].nflushes;
			sdstats->bstats[i].nslabs += astats->bstats[i].nslabs;
			sdstats->bstats[i].reslabs += astats->bstats[i].reslabs;
			if (!destroyed) {
				sdstats->bstats[i].curslabs +=
				    astats->bstats[i].curslabs;
			} else {
				assert(astats->bstats[i].curslabs == 0);
			}
			malloc_mutex_prof_merge(&sdstats->bstats[i].mutex_data,
			    &astats->bstats[i].mutex_data);
		}

		for (i = 0; i < NSIZES - NBINS; i++) {
			ctl_accum_arena_stats_u64(&sdstats->lstats[i].nmalloc,
			    &astats->lstats[i].nmalloc);
			ctl_accum_arena_stats_u64(&sdstats->lstats[i].ndalloc,
			    &astats->lstats[i].ndalloc);
			ctl_accum_arena_stats_u64(&sdstats->lstats[i].nrequests,
			    &astats->lstats[i].nrequests);
			if (!destroyed) {
				sdstats->lstats[i].curlextents +=
				    astats->lstats[i].curlextents;
			} else {
				assert(astats->lstats[i].curlextents == 0);
			}
		}
	}
}
