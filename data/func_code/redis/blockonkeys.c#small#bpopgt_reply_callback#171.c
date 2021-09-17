int bpopgt_reply_callback(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    RedisModuleString *keyname = RedisModule_GetBlockedClientReadyKey(ctx);
    long long *pgt = RedisModule_GetBlockedClientPrivateData(ctx);

    fsl_t *fsl;
    if (!get_fsl(ctx, keyname, REDISMODULE_READ, 0, &fsl, 0))
        return REDISMODULE_ERR;

    if (!fsl || fsl->list[fsl->length-1] <= *pgt)
        return REDISMODULE_ERR;

    RedisModule_ReplyWithLongLong(ctx, fsl->list[--fsl->length]);
    return REDISMODULE_OK;
}
