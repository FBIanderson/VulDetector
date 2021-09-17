static void
forwarding_cb(void *buf_descriptor_v, const char *str) {
	buf_descriptor_t *buf_descriptor = (buf_descriptor_t *)buf_descriptor_v;

	if (print_raw) {
		malloc_printf("%s", str);
	}
	if (print_escaped) {
		const char *it = str;
		while (*it != '\0') {
			if (!buf_descriptor->mid_quote) {
				malloc_printf("\"");
				buf_descriptor->mid_quote = true;
			}
			switch (*it) {
			case '\\':
				malloc_printf("\\");
				break;
			case '\"':
				malloc_printf("\\\"");
				break;
			case '\t':
				malloc_printf("\\t");
				break;
			case '\n':
				malloc_printf("\\n\"\n");
				buf_descriptor->mid_quote = false;
				break;
			default:
				malloc_printf("%c", *it);
			}
			it++;
		}
	}

	size_t written = malloc_snprintf(buf_descriptor->buf,
	    buf_descriptor->len, "%s", str);
	assert_zu_eq(written, strlen(str), "Buffer overflow!");
	buf_descriptor->buf += written;
	buf_descriptor->len -= written;
	assert_zu_gt(buf_descriptor->len, 0, "Buffer out of space!");
}
