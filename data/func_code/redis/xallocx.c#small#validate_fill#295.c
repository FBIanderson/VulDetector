static bool
validate_fill(const void *p, uint8_t c, size_t offset, size_t len) {
	const uint8_t *pc = (const uint8_t *)p;
	bool err;
	size_t i;

	for (i = offset, err = false; i < offset+len; i++) {
		if (pc[i] != c) {
			err = true;
		}
	}

	if (err) {
		print_filled_extents(p, c, offset + len);
	}

	return err;
}
