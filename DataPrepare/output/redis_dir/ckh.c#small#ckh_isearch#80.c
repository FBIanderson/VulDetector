static size_t
ckh_isearch(ckh_t *ckh, const void *key) {
	size_t hashes[2], bucket, cell;

	assert(ckh != NULL);

	ckh->hash(key, hashes);

	/* Search primary bucket. */
	bucket = hashes[0] & ((ZU(1) << ckh->lg_curbuckets) - 1);
	cell = ckh_bucket_search(ckh, bucket, key);
	if (cell != SIZE_T_MAX) {
		return cell;
	}

	/* Search secondary bucket. */
	bucket = hashes[1] & ((ZU(1) << ckh->lg_curbuckets) - 1);
	cell = ckh_bucket_search(ckh, bucket, key);
	return cell;
}
