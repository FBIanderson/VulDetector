void
bitmap_init(bitmap_t *bitmap, const bitmap_info_t *binfo, bool fill) {
	size_t extra;

	if (fill) {
		memset(bitmap, 0, bitmap_size(binfo));
		return;
	}

	memset(bitmap, 0xffU, bitmap_size(binfo));
	extra = (BITMAP_GROUP_NBITS - (binfo->nbits & BITMAP_GROUP_NBITS_MASK))
	    & BITMAP_GROUP_NBITS_MASK;
	if (extra != 0) {
		bitmap[binfo->ngroups - 1] >>= extra;
	}
}
