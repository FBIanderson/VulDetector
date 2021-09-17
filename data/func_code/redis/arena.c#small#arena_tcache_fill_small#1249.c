void
arena_tcache_fill_small(tsdn_t *tsdn, arena_t *arena, tcache_t *tcache,
    cache_bin_t *tbin, szind_t binind, uint64_t prof_accumbytes) {
	unsigned i, nfill;
	bin_t *bin;

	assert(tbin->ncached == 0);

	if (config_prof && arena_prof_accum(tsdn, arena, prof_accumbytes)) {
		prof_idump(tsdn);
	}
	bin = &arena->bins[binind];
	malloc_mutex_lock(tsdn, &bin->lock);
	for (i = 0, nfill = (tcache_bin_info[binind].ncached_max >>
	    tcache->lg_fill_div[binind]); i < nfill; i++) {
		extent_t *slab;
		void *ptr;
		if ((slab = bin->slabcur) != NULL && extent_nfree_get(slab) >
		    0) {
			ptr = arena_slab_reg_alloc(slab, &bin_infos[binind]);
		} else {
			ptr = arena_bin_malloc_hard(tsdn, arena, bin, binind);
		}
		if (ptr == NULL) {
			/*
			 * OOM.  tbin->avail isn't yet filled down to its first
			 * element, so the successful allocations (if any) must
			 * be moved just before tbin->avail before bailing out.
			 */
			if (i > 0) {
				memmove(tbin->avail - i, tbin->avail - nfill,
				    i * sizeof(void *));
			}
			break;
		}
		if (config_fill && unlikely(opt_junk_alloc)) {
			arena_alloc_junk_small(ptr, &bin_infos[binind], true);
		}
		/* Insert such that low regions get used first. */
		*(tbin->avail - nfill + i) = ptr;
	}
	if (config_stats) {
		bin->stats.nmalloc += i;
		bin->stats.nrequests += tbin->tstats.nrequests;
		bin->stats.curregs += i;
		bin->stats.nfills++;
		tbin->tstats.nrequests = 0;
	}
	malloc_mutex_unlock(tsdn, &bin->lock);
	tbin->ncached = i;
	arena_decay_tick(tsdn, arena);
}
