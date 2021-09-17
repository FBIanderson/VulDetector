int
ctl_byname(tsd_t *tsd, const char *name, void *oldp, size_t *oldlenp,
    void *newp, size_t newlen) {
	int ret;
	size_t depth;
	ctl_node_t const *nodes[CTL_MAX_DEPTH];
	size_t mib[CTL_MAX_DEPTH];
	const ctl_named_node_t *node;

	if (!ctl_initialized && ctl_init(tsd)) {
		ret = EAGAIN;
		goto label_return;
	}

	depth = CTL_MAX_DEPTH;
	ret = ctl_lookup(tsd_tsdn(tsd), name, nodes, mib, &depth);
	if (ret != 0) {
		goto label_return;
	}

	node = ctl_named_node(nodes[depth-1]);
	if (node != NULL && node->ctl) {
		ret = node->ctl(tsd, mib, depth, oldp, oldlenp, newp, newlen);
	} else {
		/* The name refers to a partial path through the ctl tree. */
		ret = ENOENT;
	}

label_return:
	return(ret);
}
