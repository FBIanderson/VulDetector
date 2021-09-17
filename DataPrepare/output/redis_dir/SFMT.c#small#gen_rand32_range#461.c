uint32_t gen_rand32_range(sfmt_t *ctx, uint32_t limit) {
    uint32_t ret, above;

    above = 0xffffffffU - (0xffffffffU % limit);
    while (1) {
	ret = gen_rand32(ctx);
	if (ret < above) {
	    ret %= limit;
	    break;
	}
    }
    return ret;
}
