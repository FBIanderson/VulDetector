int fsl_bpop2(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 3)
        return RedisModule_WrongArity(ctx);

    long long timeout;
    if (RedisModule_StringToLongLong(argv[2],&timeout) != REDISMODULE_OK || timeout < 0)
        return RedisModule_ReplyWithError(ctx,"ERR invalid timeout");

    fsl_t *fsl;
    if (!get_fsl(ctx, argv[1], REDISMODULE_READ, 0, &fsl, 1))
        return REDISMODULE_OK;

    if (!fsl || fsl->length < 2) {
        /* Key is empty or has <2 elements, we must block */
        RedisModule_BlockClientOnKeys(ctx, bpop2_reply_callback, bpop2_timeout_callback,
                                      NULL, timeout, &argv[1], 1, NULL);
    } else {
        RedisModule_ReplyWithArray(ctx, 2);
        RedisModule_ReplyWithLongLong(ctx, fsl->list[--fsl->length]);
        RedisModule_ReplyWithLongLong(ctx, fsl->list[--fsl->length]);
    }

    return REDISMODULE_OK;
}
