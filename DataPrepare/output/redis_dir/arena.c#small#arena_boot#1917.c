void
arena_boot(void) {
	arena_dirty_decay_ms_default_set(opt_dirty_decay_ms);
	arena_muzzy_decay_ms_default_set(opt_muzzy_decay_ms);
#define REGIND_bin_yes(index, reg_size) 				\
	div_init(&arena_binind_div_info[(index)], (reg_size));
#define REGIND_bin_no(index, reg_size)
#define SC(index, lg_grp, lg_delta, ndelta, psz, bin, pgs,		\
    lg_delta_lookup)							\
	REGIND_bin_##bin(index, (1U<<lg_grp) + (ndelta << lg_delta))
	SIZE_CLASSES
#undef REGIND_bin_yes
#undef REGIND_bin_no
#undef SC
}
