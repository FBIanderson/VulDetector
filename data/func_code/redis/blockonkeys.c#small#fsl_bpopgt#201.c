int fsl_bpopgt(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 4)
        return RedisModule_WrongArity(ctx);

    long long gt;
    if (RedisModule_StringToLongLong(argv[2],&gt) != REDISMODULE_OK)
        return RedisModule_ReplyWithError(ctx,"ERR invalid integer");

    long long timeout;
    if (RedisModule_StringToLongLong(argv[3],&timeout) != REDISMODULE_OK || timeout < 0)
        return RedisModule_ReplyWithError(ctx,"ERR invalid timeout");

    fsl_t *fsl;
    if (!get_fsl(ctx, argv[1], REDISMODULE_READ, 0, &fsl, 1))
        return REDISMODULE_OK;

    if (!fsl || fsl->list[fsl->length-1] <= gt) {
        /* We use malloc so the tests in blockedonkeys.tcl can check for memory leaks */
        long long *pgt = RedisModule_Alloc(sizeof(long long));
        *pgt = gt;
        /* Key is empty or has <2 elements, we must block */
        RedisModule_BlockClientOnKeys(ctx, bpopgt_reply_callback, bpopgt_timeout_callback,
                                      bpopgt_free_privdata, timeout, &argv[1], 1, pgt);
    } else {
        RedisModule_ReplyWithLongLong(ctx, fsl->list[--fsl->length]);
    }

    return REDISMODULE_OK;
}
