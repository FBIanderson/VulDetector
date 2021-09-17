int bpop2_reply_callback(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    RedisModuleString *keyname = RedisModule_GetBlockedClientReadyKey(ctx);

    fsl_t *fsl;
    if (!get_fsl(ctx, keyname, REDISMODULE_READ, 0, &fsl, 0))
        return REDISMODULE_ERR;

    if (!fsl || fsl->length < 2)
        return REDISMODULE_ERR;

    RedisModule_ReplyWithArray(ctx, 2);
    RedisModule_ReplyWithLongLong(ctx, fsl->list[--fsl->length]);
    RedisModule_ReplyWithLongLong(ctx, fsl->list[--fsl->length]);
    return REDISMODULE_OK;
}
