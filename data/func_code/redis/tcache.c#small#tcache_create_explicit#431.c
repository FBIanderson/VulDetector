tcache_t *
tcache_create_explicit(tsd_t *tsd) {
	tcache_t *tcache;
	size_t size, stack_offset;

	size = sizeof(tcache_t);
	/* Naturally align the pointer stacks. */
	size = PTR_CEILING(size);
	stack_offset = size;
	size += stack_nelms * sizeof(void *);
	/* Avoid false cacheline sharing. */
	size = sz_sa2u(size, CACHELINE);

	tcache = ipallocztm(tsd_tsdn(tsd), size, CACHELINE, true, NULL, true,
	    arena_get(TSDN_NULL, 0, true));
	if (tcache == NULL) {
		return NULL;
	}

	tcache_init(tsd, tcache,
	    (void *)((uintptr_t)tcache + (uintptr_t)stack_offset));
	tcache_arena_associate(tsd_tsdn(tsd), tcache, arena_ichoose(tsd, NULL));

	return tcache;
}
