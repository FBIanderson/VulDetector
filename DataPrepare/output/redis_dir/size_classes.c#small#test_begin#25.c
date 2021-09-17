TEST_BEGIN(test_size_classes) {
	size_t size_class, max_size_class;
	szind_t index, max_index;

	max_size_class = get_max_size_class();
	max_index = sz_size2index(max_size_class);

	for (index = 0, size_class = sz_index2size(index); index < max_index ||
	    size_class < max_size_class; index++, size_class =
	    sz_index2size(index)) {
		assert_true(index < max_index,
		    "Loop conditionals should be equivalent; index=%u, "
		    "size_class=%zu (%#zx)", index, size_class, size_class);
		assert_true(size_class < max_size_class,
		    "Loop conditionals should be equivalent; index=%u, "
		    "size_class=%zu (%#zx)", index, size_class, size_class);

		assert_u_eq(index, sz_size2index(size_class),
		    "sz_size2index() does not reverse sz_index2size(): index=%u"
		    " --> size_class=%zu --> index=%u --> size_class=%zu",
		    index, size_class, sz_size2index(size_class),
		    sz_index2size(sz_size2index(size_class)));
		assert_zu_eq(size_class,
		    sz_index2size(sz_size2index(size_class)),
		    "sz_index2size() does not reverse sz_size2index(): index=%u"
		    " --> size_class=%zu --> index=%u --> size_class=%zu",
		    index, size_class, sz_size2index(size_class),
		    sz_index2size(sz_size2index(size_class)));

		assert_u_eq(index+1, sz_size2index(size_class+1),
		    "Next size_class does not round up properly");

		assert_zu_eq(size_class, (index > 0) ?
		    sz_s2u(sz_index2size(index-1)+1) : sz_s2u(1),
		    "sz_s2u() does not round up to size class");
		assert_zu_eq(size_class, sz_s2u(size_class-1),
		    "sz_s2u() does not round up to size class");
		assert_zu_eq(size_class, sz_s2u(size_class),
		    "sz_s2u() does not compute same size class");
		assert_zu_eq(sz_s2u(size_class+1), sz_index2size(index+1),
		    "sz_s2u() does not round up to next size class");
	}

	assert_u_eq(index, sz_size2index(sz_index2size(index)),
	    "sz_size2index() does not reverse sz_index2size()");
	assert_zu_eq(max_size_class, sz_index2size(
	    sz_size2index(max_size_class)),
	    "sz_index2size() does not reverse sz_size2index()");

	assert_zu_eq(size_class, sz_s2u(sz_index2size(index-1)+1),
	    "sz_s2u() does not round up to size class");
	assert_zu_eq(size_class, sz_s2u(size_class-1),
	    "sz_s2u() does not round up to size class");
	assert_zu_eq(size_class, sz_s2u(size_class),
	    "sz_s2u() does not compute same size class");
}
