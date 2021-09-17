TEST_BEGIN(test_rb_random) {
#define NNODES 25
#define NBAGS 250
#define SEED 42
	sfmt_t *sfmt;
	uint64_t bag[NNODES];
	tree_t tree;
	node_t nodes[NNODES];
	unsigned i, j, k, black_height, imbalances;

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
			/* Initialize tree and nodes. */
			tree_new(&tree);
			for (k = 0; k < j; k++) {
				nodes[k].magic = NODE_MAGIC;
				nodes[k].key = bag[k];
			}

			/* Insert nodes. */
			for (k = 0; k < j; k++) {
				tree_insert(&tree, &nodes[k]);

				rbtn_black_height(node_t, link, &tree,
				    black_height);
				imbalances = tree_recurse(tree.rbt_root,
				    black_height, 0);
				assert_u_eq(imbalances, 0,
				    "Tree is unbalanced");

				assert_u_eq(tree_iterate(&tree), k+1,
				    "Unexpected node iteration count");
				assert_u_eq(tree_iterate_reverse(&tree), k+1,
				    "Unexpected node iteration count");

				assert_false(tree_empty(&tree),
				    "Tree should not be empty");
				assert_ptr_not_null(tree_first(&tree),
				    "Tree should not be empty");
				assert_ptr_not_null(tree_last(&tree),
				    "Tree should not be empty");

				tree_next(&tree, &nodes[k]);
				tree_prev(&tree, &nodes[k]);
			}

			/* Remove nodes. */
			switch (i % 5) {
			case 0:
				for (k = 0; k < j; k++) {
					node_remove(&tree, &nodes[k], j - k);
				}
				break;
			case 1:
				for (k = j; k > 0; k--) {
					node_remove(&tree, &nodes[k-1], k);
				}
				break;
			case 2: {
				node_t *start;
				unsigned nnodes = j;

				start = NULL;
				do {
					start = tree_iter(&tree, start,
					    remove_iterate_cb, (void *)&nnodes);
					nnodes--;
				} while (start != NULL);
				assert_u_eq(nnodes, 0,
				    "Removal terminated early");
				break;
			} case 3: {
				node_t *start;
				unsigned nnodes = j;

				start = NULL;
				do {
					start = tree_reverse_iter(&tree, start,
					    remove_reverse_iterate_cb,
					    (void *)&nnodes);
					nnodes--;
				} while (start != NULL);
				assert_u_eq(nnodes, 0,
				    "Removal terminated early");
				break;
			} case 4: {
				unsigned nnodes = j;
				tree_destroy(&tree, destroy_cb, &nnodes);
				assert_u_eq(nnodes, 0,
				    "Destruction terminated early");
				break;
			} default:
				not_reached();
			}
		}
	}
	fini_gen_rand(sfmt);
#undef NNODES
#undef NBAGS
#undef SEED
}
