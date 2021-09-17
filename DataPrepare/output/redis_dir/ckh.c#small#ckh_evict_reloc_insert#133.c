static bool
ckh_evict_reloc_insert(ckh_t *ckh, size_t argbucket, void const **argkey,
    void const **argdata) {
	const void *key, *data, *tkey, *tdata;
	ckhc_t *cell;
	size_t hashes[2], bucket, tbucket;
	unsigned i;

	bucket = argbucket;
	key = *argkey;
	data = *argdata;
	while (true) {
		/*
		 * Choose a random item within the bucket to evict.  This is
		 * critical to correct function, because without (eventually)
		 * evicting all items within a bucket during iteration, it
		 * would be possible to get stuck in an infinite loop if there
		 * were an item for which both hashes indicated the same
		 * bucket.
		 */
		i = (unsigned)prng_lg_range_u64(&ckh->prng_state,
		    LG_CKH_BUCKET_CELLS);
		cell = &ckh->tab[(bucket << LG_CKH_BUCKET_CELLS) + i];
		assert(cell->key != NULL);

		/* Swap cell->{key,data} and {key,data} (evict). */
		tkey = cell->key; tdata = cell->data;
		cell->key = key; cell->data = data;
		key = tkey; data = tdata;

#ifdef CKH_COUNT
		ckh->nrelocs++;
#endif

		/* Find the alternate bucket for the evicted item. */
		ckh->hash(key, hashes);
		tbucket = hashes[1] & ((ZU(1) << ckh->lg_curbuckets) - 1);
		if (tbucket == bucket) {
			tbucket = hashes[0] & ((ZU(1) << ckh->lg_curbuckets)
			    - 1);
			/*
			 * It may be that (tbucket == bucket) still, if the
			 * item's hashes both indicate this bucket.  However,
			 * we are guaranteed to eventually escape this bucket
			 * during iteration, assuming pseudo-random item
			 * selection (true randomness would make infinite
			 * looping a remote possibility).  The reason we can
			 * never get trapped forever is that there are two
			 * cases:
			 *
			 * 1) This bucket == argbucket, so we will quickly
			 *    detect an eviction cycle and terminate.
			 * 2) An item was evicted to this bucket from another,
			 *    which means that at least one item in this bucket
			 *    has hashes that indicate distinct buckets.
			 */
		}
		/* Check for a cycle. */
		if (tbucket == argbucket) {
			*argkey = key;
			*argdata = data;
			return true;
		}

		bucket = tbucket;
		if (!ckh_try_bucket_insert(ckh, bucket, key, data)) {
			return false;
		}
	}
}
