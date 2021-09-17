TEST_BEGIN(test_stats_print_json) {
	const char *opts[] = {
		"J",
		"Jg",
		"Jm",
		"Jd",
		"Jmd",
		"Jgd",
		"Jgm",
		"Jgmd",
		"Ja",
		"Jb",
		"Jl",
		"Jx",
		"Jbl",
		"Jal",
		"Jab",
		"Jabl",
		"Jax",
		"Jbx",
		"Jlx",
		"Jablx",
		"Jgmdablx",
	};
	unsigned arena_ind, i;

	for (i = 0; i < 3; i++) {
		unsigned j;

		switch (i) {
		case 0:
			break;
		case 1: {
			size_t sz = sizeof(arena_ind);
			assert_d_eq(mallctl("arenas.create", (void *)&arena_ind,
			    &sz, NULL, 0), 0, "Unexpected mallctl failure");
			break;
		} case 2: {
			size_t mib[3];
			size_t miblen = sizeof(mib)/sizeof(size_t);
			assert_d_eq(mallctlnametomib("arena.0.destroy",
			    mib, &miblen), 0,
			    "Unexpected mallctlnametomib failure");
			mib[1] = arena_ind;
			assert_d_eq(mallctlbymib(mib, miblen, NULL, NULL, NULL,
			    0), 0, "Unexpected mallctlbymib failure");
			break;
		} default:
			not_reached();
		}

		for (j = 0; j < sizeof(opts)/sizeof(const char *); j++) {
			parser_t parser;

			parser_init(&parser, true);
			malloc_stats_print(write_cb, (void *)&parser, opts[j]);
			assert_false(parser_parse(&parser),
			    "Unexpected parse error, opts=\"%s\"", opts[j]);
			parser_fini(&parser);
		}
	}
}
