TEST_BEGIN(test_new_delete) {
	tsd_t *tsd;
	ckh_t ckh;

	tsd = tsd_fetch();

	assert_false(ckh_new(tsd, &ckh, 2, ckh_string_hash,
	    ckh_string_keycomp), "Unexpected ckh_new() error");
	ckh_delete(tsd, &ckh);

	assert_false(ckh_new(tsd, &ckh, 3, ckh_pointer_hash,
	    ckh_pointer_keycomp), "Unexpected ckh_new() error");
	ckh_delete(tsd, &ckh);
}
