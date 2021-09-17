uint64_t gen_rand64_range(sfmt_t *ctx, uint64_t limit) {
    uint64_t ret, above;

    above = KQU(0xffffffffffffffff) - (KQU(0xffffffffffffffff) % limit);
    while (1) {
	ret = gen_rand64(ctx);
	if (ret < above) {
	    ret %= limit;
	    break;
	}
    }
    return ret;
}
