void
stats_print(void (*write_cb)(void *, const char *), void *cbopaque,
    const char *opts) {
	int err;
	uint64_t epoch;
	size_t u64sz;
#define OPTION(o, v, d, s) bool v = d;
	STATS_PRINT_OPTIONS
#undef OPTION

	/*
	 * Refresh stats, in case mallctl() was called by the application.
	 *
	 * Check for OOM here, since refreshing the ctl cache can trigger
	 * allocation.  In practice, none of the subsequent mallctl()-related
	 * calls in this function will cause OOM if this one succeeds.
	 * */
	epoch = 1;
	u64sz = sizeof(uint64_t);
	err = je_mallctl("epoch", (void *)&epoch, &u64sz, (void *)&epoch,
	    sizeof(uint64_t));
	if (err != 0) {
		if (err == EAGAIN) {
			malloc_write("<jemalloc>: Memory allocation failure in "
			    "mallctl(\"epoch\", ...)\n");
			return;
		}
		malloc_write("<jemalloc>: Failure in mallctl(\"epoch\", "
		    "...)\n");
		abort();
	}

	if (opts != NULL) {
		for (unsigned i = 0; opts[i] != '\0'; i++) {
			switch (opts[i]) {
#define OPTION(o, v, d, s) case o: v = s; break;
				STATS_PRINT_OPTIONS
#undef OPTION
			default:;
			}
		}
	}

	emitter_t emitter;
	emitter_init(&emitter,
	    json ? emitter_output_json : emitter_output_table, write_cb,
	    cbopaque);
	emitter_begin(&emitter);
	emitter_table_printf(&emitter, "___ Begin jemalloc statistics ___\n");
	emitter_json_dict_begin(&emitter, "jemalloc");

	if (general) {
		stats_general_print(&emitter);
	}
	if (config_stats) {
		stats_print_helper(&emitter, merged, destroyed, unmerged,
		    bins, large, mutex);
	}

	emitter_json_dict_end(&emitter); /* Closes the "jemalloc" dict. */
	emitter_table_printf(&emitter, "--- End jemalloc statistics ---\n");
	emitter_end(&emitter);
}
