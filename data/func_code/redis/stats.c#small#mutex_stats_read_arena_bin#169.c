static void
mutex_stats_read_arena_bin(unsigned arena_ind, unsigned bin_ind,
    emitter_col_t col_uint64_t[mutex_prof_num_uint64_t_counters],
    emitter_col_t col_uint32_t[mutex_prof_num_uint32_t_counters]) {
	char cmd[MUTEX_CTL_STR_MAX_LENGTH];
	emitter_col_t *dst;

#define EMITTER_TYPE_uint32_t emitter_type_uint32
#define EMITTER_TYPE_uint64_t emitter_type_uint64
#define OP(counter, counter_type, human)				\
	dst = &col_##counter_type[mutex_counter_##counter];		\
	dst->type = EMITTER_TYPE_##counter_type;			\
	gen_mutex_ctl_str(cmd, MUTEX_CTL_STR_MAX_LENGTH,		\
	    "arenas.0.bins.0","mutex", #counter);			\
	CTL_M2_M4_GET(cmd, arena_ind, bin_ind,				\
	    (counter_type *)&dst->bool_val, counter_type);
	MUTEX_PROF_COUNTERS
#undef OP
#undef EMITTER_TYPE_uint32_t
#undef EMITTER_TYPE_uint64_t
}
