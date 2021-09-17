TEST_BEGIN(test_rb_empty) {
	tree_t tree;
	node_t key;

	tree_new(&tree);

	assert_true(tree_empty(&tree), "Tree should be empty");
	assert_ptr_null(tree_first(&tree), "Unexpected node");
	assert_ptr_null(tree_last(&tree), "Unexpected node");

	key.key = 0;
	key.magic = NODE_MAGIC;
	assert_ptr_null(tree_search(&tree, &key), "Unexpected node");

	key.key = 0;
	key.magic = NODE_MAGIC;
	assert_ptr_null(tree_nsearch(&tree, &key), "Unexpected node");

	key.key = 0;
	key.magic = NODE_MAGIC;
	assert_ptr_null(tree_psearch(&tree, &key), "Unexpected node");
}
