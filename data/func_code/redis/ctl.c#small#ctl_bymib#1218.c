int
ctl_bymib(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	const ctl_named_node_t *node;
	size_t i;

	if (!ctl_initialized && ctl_init(tsd)) {
		ret = EAGAIN;
		goto label_return;
	}

	/* Iterate down the tree. */
	node = super_root_node;
	for (i = 0; i < miblen; i++) {
		assert(node);
		assert(node->nchildren > 0);
		if (ctl_named_node(node->children) != NULL) {
			/* Children are named. */
			if (node->nchildren <= mib[i]) {
				ret = ENOENT;
				goto label_return;
			}
			node = ctl_named_children(node, mib[i]);
		} else {
			const ctl_indexed_node_t *inode;

			/* Indexed element. */
			inode = ctl_indexed_node(node->children);
			node = inode->index(tsd_tsdn(tsd), mib, miblen, mib[i]);
			if (node == NULL) {
				ret = ENOENT;
				goto label_return;
			}
		}
	}

	/* Call the ctl function. */
	if (node && node->ctl) {
		ret = node->ctl(tsd, mib, miblen, oldp, oldlenp, newp, newlen);
	} else {
		/* Partial MIB. */
		ret = ENOENT;
	}

label_return:
	return(ret);
}
