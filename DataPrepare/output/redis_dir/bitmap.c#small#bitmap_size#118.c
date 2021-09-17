size_t
bitmap_size(const bitmap_info_t *binfo) {
	return (bitmap_info_ngroups(binfo) << LG_SIZEOF_BITMAP);
}
