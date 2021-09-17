static void
mutex_stats_read_global(const char *name, emitter_col_t *col_name,
    emitter_col_t col_uint64_t[mutex_prof_num_uint64_t_counters],
    emitter_col_t col_uint32_t[mutex_prof_num_uint32_t_counters]) {
	char cmd[MUTEX_CTL_STR_MAX_LENGTH];

	col_name->str_val = name;

	emitter_col_t *dst;
#define EMITTER_TYPE_uint32_t emitter_type_uint32
#define EMITTER_TYPE_uint64_t emitter_type_uint64
#define OP(counter, counter_type, human)				\
	dst = &col_##counter_type[mutex_counter_##counter];		\
	dst->type = EMITTER_TYPE_##counter_type;			\
	gen_mutex_ctl_str(cmd, MUTEX_CTL_STR_MAX_LENGTH,		\
	    "mutexes", name, #counter);					\
	CTL_GET(cmd, (counter_type *)&dst->bool_val, counter_type);
	MUTEX_PROF_COUNTERS
#undef OP
#undef EMITTER_TYPE_uint32_t
#undef EMITTER_TYPE_uint64_t
}
