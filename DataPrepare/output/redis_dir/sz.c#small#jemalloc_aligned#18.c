JEMALLOC_ALIGNED(CACHELINE)
const size_t sz_index2size_tab[NSIZES] = {
#define SC(index, lg_grp, lg_delta, ndelta, psz, bin, pgs, lg_delta_lookup) \
	((ZU(1)<<lg_grp) + (ZU(ndelta)<<lg_delta)),
	SIZE_CLASSES
#undef SC
};
