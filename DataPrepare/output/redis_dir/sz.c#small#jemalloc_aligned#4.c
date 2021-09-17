JEMALLOC_ALIGNED(CACHELINE)
const size_t sz_pind2sz_tab[NPSIZES+1] = {
#define PSZ_yes(lg_grp, ndelta, lg_delta)				\
	(((ZU(1)<<lg_grp) + (ZU(ndelta)<<lg_delta))),
#define PSZ_no(lg_grp, ndelta, lg_delta)
#define SC(index, lg_grp, lg_delta, ndelta, psz, bin, pgs, lg_delta_lookup) \
	PSZ_##psz(lg_grp, ndelta, lg_delta)
	SIZE_CLASSES
#undef PSZ_yes
#undef PSZ_no
#undef SC
	(LARGE_MAXCLASS + PAGE)
};
