void
bitmap_info_init(bitmap_info_t *binfo, size_t nbits) {
	assert(nbits > 0);
	assert(nbits <= (ZU(1) << LG_BITMAP_MAXBITS));

	binfo->ngroups = BITMAP_BITS2GROUPS(nbits);
	binfo->nbits = nbits;
}
