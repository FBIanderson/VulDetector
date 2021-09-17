TEST_BEGIN(test_ph_random) {
#define NNODES 25
#define NBAGS 250
#define SEED 42
	sfmt_t *sfmt;
	uint64_t bag[NNODES];
	heap_t heap;
	node_t nodes[NNODES];
	unsigned i, j, k;

	sfmt = init_gen_rand(SEED);
	for (i = 0; i < NBAGS; i++) {
		switch (i) {
		case 0:
			/* Insert in order. */
			for (j = 0; j < NNODES; j++) {
				bag[j] = j;
			}
			break;
		case 1:
			/* Insert in reverse order. */
			for (j = 0; j < NNODES; j++) {
				bag[j] = NNODES - j - 1;
			}
			break;
		default:
			for (j = 0; j < NNODES; j++) {
				bag[j] = gen_rand64_range(sfmt, NNODES);
			}
		}

		for (j = 1; j <= NNODES; j++) {
			/* Initialize heap and nodes. */
			heap_new(&heap);
			assert_u_eq(heap_validate(&heap), 0,
			    "Incorrect node count");
			for (k = 0; k < j; k++) {
				nodes[k].magic = NODE_MAGIC;
				nodes[k].key = bag[k];
			}

			/* Insert nodes. */
			for (k = 0; k < j; k++) {
				heap_insert(&heap, &nodes[k]);
				if (i % 13 == 12) {
					assert_ptr_not_null(heap_any(&heap),
					    "Heap should not be empty");
					/* Trigger merging. */
					assert_ptr_not_null(heap_first(&heap),
					    "Heap should not be empty");
				}
				assert_u_eq(heap_validate(&heap), k + 1,
				    "Incorrect node count");
			}

			assert_false(heap_empty(&heap),
			    "Heap should not be empty");

			/* Remove nodes. */
			switch (i % 6) {
			case 0:
				for (k = 0; k < j; k++) {
					assert_u_eq(heap_validate(&heap), j - k,
					    "Incorrect node count");
					node_remove(&heap, &nodes[k]);
					assert_u_eq(heap_validate(&heap), j - k
					    - 1, "Incorrect node count");
				}
				break;
			case 1:
				for (k = j; k > 0; k--) {
					node_remove(&heap, &nodes[k-1]);
					assert_u_eq(heap_validate(&heap), k - 1,
					    "Incorrect node count");
				}
				break;
			case 2: {
				node_t *prev = NULL;
				for (k = 0; k < j; k++) {
					node_t *node = node_remove_first(&heap);
					assert_u_eq(heap_validate(&heap), j - k
					    - 1, "Incorrect node count");
					if (prev != NULL) {
						assert_d_ge(node_cmp(node,
						    prev), 0,
						    "Bad removal order");
					}
					prev = node;
				}
				break;
			} case 3: {
				node_t *prev = NULL;
				for (k = 0; k < j; k++) {
					node_t *node = heap_first(&heap);
					assert_u_eq(heap_validate(&heap), j - k,
					    "Incorrect node count");
					if (prev != NULL) {
						assert_d_ge(node_cmp(node,
						    prev), 0,
						    "Bad removal order");
					}
					node_remove(&heap, node);
					assert_u_eq(heap_validate(&heap), j - k
					    - 1, "Incorrect node count");
					prev = node;
				}
				break;
			} case 4: {
				for (k = 0; k < j; k++) {
					node_remove_any(&heap);
					assert_u_eq(heap_validate(&heap), j - k
					    - 1, "Incorrect node count");
				}
				break;
			} case 5: {
				for (k = 0; k < j; k++) {
					node_t *node = heap_any(&heap);
					assert_u_eq(heap_validate(&heap), j - k,
					    "Incorrect node count");
					node_remove(&heap, node);
					assert_u_eq(heap_validate(&heap), j - k
					    - 1, "Incorrect node count");
				}
				break;
			} default:
				not_reached();
			}

			assert_ptr_null(heap_first(&heap),
			    "Heap should be empty");
			assert_ptr_null(heap_any(&heap),
			    "Heap should be empty");
			assert_true(heap_empty(&heap), "Heap should be empty");
		}
	}
	fini_gen_rand(sfmt);
#undef NNODES
#undef SEED
}
