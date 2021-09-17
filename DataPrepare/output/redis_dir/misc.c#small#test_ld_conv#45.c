int test_ld_conv(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    UNUSED(argv);
    UNUSED(argc);
    long double ld = 0.00000000000000001L;
    const char *ldstr = "0.00000000000000001";
    RedisModuleString *s1 = RedisModule_CreateStringFromLongDouble(ctx, ld, 1);
    RedisModuleString *s2 =
        RedisModule_CreateString(ctx, ldstr, strlen(ldstr));
    if (RedisModule_StringCompare(s1, s2) != 0) {
        char err[4096];
        snprintf(err, 4096,
            "Failed to convert long double to string ('%s' != '%s')",
            RedisModule_StringPtrLen(s1, NULL),
            RedisModule_StringPtrLen(s2, NULL));
        RedisModule_ReplyWithError(ctx, err);
        goto final;
    }
    long double ld2 = 0;
    if (RedisModule_StringToLongDouble(s2, &ld2) == REDISMODULE_ERR) {
        RedisModule_ReplyWithError(ctx,
            "Failed to convert string to long double");
        goto final;
    }
    if (ld2 != ld) {
        char err[4096];
        snprintf(err, 4096,
            "Failed to convert string to long double (%.40Lf != %.40Lf)",
            ld2,
            ld);
        RedisModule_ReplyWithError(ctx, err);
        goto final;
    }

    /* Make sure we can't convert a string that has \0 in it */
    char buf[4] = "123";
    buf[1] = '\0';
    RedisModuleString *s3 = RedisModule_CreateString(ctx, buf, 3);
    long double ld3;
    if (RedisModule_StringToLongDouble(s3, &ld3) == REDISMODULE_OK) {
        RedisModule_ReplyWithError(ctx, "Invalid string successfully converted to long double");
        RedisModule_FreeString(ctx, s3);
        goto final;
    }
    RedisModule_FreeString(ctx, s3);

    RedisModule_ReplyWithLongDouble(ctx, ld2);
final:
    RedisModule_FreeString(ctx, s1);
    RedisModule_FreeString(ctx, s2);
    return REDISMODULE_OK;
}
