static void
stats_general_print(emitter_t *emitter) {
	const char *cpv;
	bool bv, bv2;
	unsigned uv;
	uint32_t u32v;
	uint64_t u64v;
	ssize_t ssv, ssv2;
	size_t sv, bsz, usz, ssz, sssz, cpsz;

	bsz = sizeof(bool);
	usz = sizeof(unsigned);
	ssz = sizeof(size_t);
	sssz = sizeof(ssize_t);
	cpsz = sizeof(const char *);

	CTL_GET("version", &cpv, const char *);
	emitter_kv(emitter, "version", "Version", emitter_type_string, &cpv);

	/* config. */
	emitter_dict_begin(emitter, "config", "Build-time option settings");
#define CONFIG_WRITE_BOOL(name)						\
	do {								\
		CTL_GET("config."#name, &bv, bool);			\
		emitter_kv(emitter, #name, "config."#name,		\
		    emitter_type_bool, &bv);				\
	} while (0)

	CONFIG_WRITE_BOOL(cache_oblivious);
	CONFIG_WRITE_BOOL(debug);
	CONFIG_WRITE_BOOL(fill);
	CONFIG_WRITE_BOOL(lazy_lock);
	emitter_kv(emitter, "malloc_conf", "config.malloc_conf",
	    emitter_type_string, &config_malloc_conf);

	CONFIG_WRITE_BOOL(prof);
	CONFIG_WRITE_BOOL(prof_libgcc);
	CONFIG_WRITE_BOOL(prof_libunwind);
	CONFIG_WRITE_BOOL(stats);
	CONFIG_WRITE_BOOL(utrace);
	CONFIG_WRITE_BOOL(xmalloc);
#undef CONFIG_WRITE_BOOL
	emitter_dict_end(emitter); /* Close "config" dict. */

	/* opt. */
#define OPT_WRITE(name, var, size, emitter_type)			\
	if (je_mallctl("opt."name, (void *)&var, &size, NULL, 0) ==	\
	    0) {							\
		emitter_kv(emitter, name, "opt."name, emitter_type,	\
		    &var);						\
	}

#define OPT_WRITE_MUTABLE(name, var1, var2, size, emitter_type,		\
    altname)								\
	if (je_mallctl("opt."name, (void *)&var1, &size, NULL, 0) ==	\
	    0 && je_mallctl(altname, (void *)&var2, &size, NULL, 0)	\
	    == 0) {							\
		emitter_kv_note(emitter, name, "opt."name,		\
		    emitter_type, &var1, altname, emitter_type,		\
		    &var2);						\
	}

#define OPT_WRITE_BOOL(name) OPT_WRITE(name, bv, bsz, emitter_type_bool)
#define OPT_WRITE_BOOL_MUTABLE(name, altname)				\
	OPT_WRITE_MUTABLE(name, bv, bv2, bsz, emitter_type_bool, altname)

#define OPT_WRITE_UNSIGNED(name)					\
	OPT_WRITE(name, uv, usz, emitter_type_unsigned)

#define OPT_WRITE_SSIZE_T(name)						\
	OPT_WRITE(name, ssv, sssz, emitter_type_ssize)
#define OPT_WRITE_SSIZE_T_MUTABLE(name, altname)			\
	OPT_WRITE_MUTABLE(name, ssv, ssv2, sssz, emitter_type_ssize,	\
	    altname)

#define OPT_WRITE_CHAR_P(name)						\
	OPT_WRITE(name, cpv, cpsz, emitter_type_string)

	emitter_dict_begin(emitter, "opt", "Run-time option settings");

	OPT_WRITE_BOOL("abort")
	OPT_WRITE_BOOL("abort_conf")
	OPT_WRITE_BOOL("retain")
	OPT_WRITE_CHAR_P("dss")
	OPT_WRITE_UNSIGNED("narenas")
	OPT_WRITE_CHAR_P("percpu_arena")
	OPT_WRITE_CHAR_P("metadata_thp")
	OPT_WRITE_BOOL_MUTABLE("background_thread", "background_thread")
	OPT_WRITE_SSIZE_T_MUTABLE("dirty_decay_ms", "arenas.dirty_decay_ms")
	OPT_WRITE_SSIZE_T_MUTABLE("muzzy_decay_ms", "arenas.muzzy_decay_ms")
	OPT_WRITE_UNSIGNED("lg_extent_max_active_fit")
	OPT_WRITE_CHAR_P("junk")
	OPT_WRITE_BOOL("zero")
	OPT_WRITE_BOOL("utrace")
	OPT_WRITE_BOOL("xmalloc")
	OPT_WRITE_BOOL("tcache")
	OPT_WRITE_SSIZE_T("lg_tcache_max")
	OPT_WRITE_CHAR_P("thp")
	OPT_WRITE_BOOL("prof")
	OPT_WRITE_CHAR_P("prof_prefix")
	OPT_WRITE_BOOL_MUTABLE("prof_active", "prof.active")
	OPT_WRITE_BOOL_MUTABLE("prof_thread_active_init",
	    "prof.thread_active_init")
	OPT_WRITE_SSIZE_T_MUTABLE("lg_prof_sample", "prof.lg_sample")
	OPT_WRITE_BOOL("prof_accum")
	OPT_WRITE_SSIZE_T("lg_prof_interval")
	OPT_WRITE_BOOL("prof_gdump")
	OPT_WRITE_BOOL("prof_final")
	OPT_WRITE_BOOL("prof_leak")
	OPT_WRITE_BOOL("stats_print")
	OPT_WRITE_CHAR_P("stats_print_opts")

	emitter_dict_end(emitter);

#undef OPT_WRITE
#undef OPT_WRITE_MUTABLE
#undef OPT_WRITE_BOOL
#undef OPT_WRITE_BOOL_MUTABLE
#undef OPT_WRITE_UNSIGNED
#undef OPT_WRITE_SSIZE_T
#undef OPT_WRITE_SSIZE_T_MUTABLE
#undef OPT_WRITE_CHAR_P

	/* prof. */
	if (config_prof) {
		emitter_dict_begin(emitter, "prof", "Profiling settings");

		CTL_GET("prof.thread_active_init", &bv, bool);
		emitter_kv(emitter, "thread_active_init",
		    "prof.thread_active_init", emitter_type_bool, &bv);

		CTL_GET("prof.active", &bv, bool);
		emitter_kv(emitter, "active", "prof.active", emitter_type_bool,
		    &bv);

		CTL_GET("prof.gdump", &bv, bool);
		emitter_kv(emitter, "gdump", "prof.gdump", emitter_type_bool,
		    &bv);

		CTL_GET("prof.interval", &u64v, uint64_t);
		emitter_kv(emitter, "interval", "prof.interval",
		    emitter_type_uint64, &u64v);

		CTL_GET("prof.lg_sample", &ssv, ssize_t);
		emitter_kv(emitter, "lg_sample", "prof.lg_sample",
		    emitter_type_ssize, &ssv);

		emitter_dict_end(emitter); /* Close "prof". */
	}

	/* arenas. */
	/*
	 * The json output sticks arena info into an "arenas" dict; the table
	 * output puts them at the top-level.
	 */
	emitter_json_dict_begin(emitter, "arenas");

	CTL_GET("arenas.narenas", &uv, unsigned);
	emitter_kv(emitter, "narenas", "Arenas", emitter_type_unsigned, &uv);

	/*
	 * Decay settings are emitted only in json mode; in table mode, they're
	 * emitted as notes with the opt output, above.
	 */
	CTL_GET("arenas.dirty_decay_ms", &ssv, ssize_t);
	emitter_json_kv(emitter, "dirty_decay_ms", emitter_type_ssize, &ssv);

	CTL_GET("arenas.muzzy_decay_ms", &ssv, ssize_t);
	emitter_json_kv(emitter, "muzzy_decay_ms", emitter_type_ssize, &ssv);

	CTL_GET("arenas.quantum", &sv, size_t);
	emitter_kv(emitter, "quantum", "Quantum size", emitter_type_size, &sv);

	CTL_GET("arenas.page", &sv, size_t);
	emitter_kv(emitter, "page", "Page size", emitter_type_size, &sv);

	if (je_mallctl("arenas.tcache_max", (void *)&sv, &ssz, NULL, 0) == 0) {
		emitter_kv(emitter, "tcache_max",
		    "Maximum thread-cached size class", emitter_type_size, &sv);
	}

	unsigned nbins;
	CTL_GET("arenas.nbins", &nbins, unsigned);
	emitter_kv(emitter, "nbins", "Number of bin size classes",
	    emitter_type_unsigned, &nbins);

	unsigned nhbins;
	CTL_GET("arenas.nhbins", &nhbins, unsigned);
	emitter_kv(emitter, "nhbins", "Number of thread-cache bin size classes",
	    emitter_type_unsigned, &nhbins);

	/*
	 * We do enough mallctls in a loop that we actually want to omit them
	 * (not just omit the printing).
	 */
	if (emitter->output == emitter_output_json) {
		emitter_json_arr_begin(emitter, "bin");
		for (unsigned i = 0; i < nbins; i++) {
			emitter_json_arr_obj_begin(emitter);

			CTL_M2_GET("arenas.bin.0.size", i, &sv, size_t);
			emitter_json_kv(emitter, "size", emitter_type_size,
			    &sv);

			CTL_M2_GET("arenas.bin.0.nregs", i, &u32v, uint32_t);
			emitter_json_kv(emitter, "nregs", emitter_type_uint32,
			    &u32v);

			CTL_M2_GET("arenas.bin.0.slab_size", i, &sv, size_t);
			emitter_json_kv(emitter, "slab_size", emitter_type_size,
			    &sv);

			emitter_json_arr_obj_end(emitter);
		}
		emitter_json_arr_end(emitter); /* Close "bin". */
	}

	unsigned nlextents;
	CTL_GET("arenas.nlextents", &nlextents, unsigned);
	emitter_kv(emitter, "nlextents", "Number of large size classes",
	    emitter_type_unsigned, &nlextents);

	if (emitter->output == emitter_output_json) {
		emitter_json_arr_begin(emitter, "lextent");
		for (unsigned i = 0; i < nlextents; i++) {
			emitter_json_arr_obj_begin(emitter);

			CTL_M2_GET("arenas.lextent.0.size", i, &sv, size_t);
			emitter_json_kv(emitter, "size", emitter_type_size,
			    &sv);

			emitter_json_arr_obj_end(emitter);
		}
		emitter_json_arr_end(emitter); /* Close "lextent". */
	}

	emitter_json_dict_end(emitter); /* Close "arenas" */
}
