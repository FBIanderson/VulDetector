void
tcache_event_hard(tsd_t *tsd, tcache_t *tcache) {
	szind_t binind = tcache->next_gc_bin;

	cache_bin_t *tbin;
	if (binind < NBINS) {
		tbin = tcache_small_bin_get(tcache, binind);
	} else {
		tbin = tcache_large_bin_get(tcache, binind);
	}
	if (tbin->low_water > 0) {
		/*
		 * Flush (ceiling) 3/4 of the objects below the low water mark.
		 */
		if (binind < NBINS) {
			tcache_bin_flush_small(tsd, tcache, tbin, binind,
			    tbin->ncached - tbin->low_water + (tbin->low_water
			    >> 2));
			/*
			 * Reduce fill count by 2X.  Limit lg_fill_div such that
			 * the fill count is always at least 1.
			 */
			cache_bin_info_t *tbin_info = &tcache_bin_info[binind];
			if ((tbin_info->ncached_max >>
			     (tcache->lg_fill_div[binind] + 1)) >= 1) {
				tcache->lg_fill_div[binind]++;
			}
		} else {
			tcache_bin_flush_large(tsd, tbin, binind, tbin->ncached
			    - tbin->low_water + (tbin->low_water >> 2), tcache);
		}
	} else if (tbin->low_water < 0) {
		/*
		 * Increase fill count by 2X for small bins.  Make sure
		 * lg_fill_div stays greater than 0.
		 */
		if (binind < NBINS && tcache->lg_fill_div[binind] > 1) {
			tcache->lg_fill_div[binind]--;
		}
	}
	tbin->low_water = tbin->ncached;

	tcache->next_gc_bin++;
	if (tcache->next_gc_bin == nhbins) {
		tcache->next_gc_bin = 0;
	}
}
