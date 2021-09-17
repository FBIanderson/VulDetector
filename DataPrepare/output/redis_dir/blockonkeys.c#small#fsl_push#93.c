int fsl_push(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 3)
        return RedisModule_WrongArity(ctx);

    long long ele;
    if (RedisModule_StringToLongLong(argv[2],&ele) != REDISMODULE_OK)
        return RedisModule_ReplyWithError(ctx,"ERR invalid integer");

    fsl_t *fsl;
    if (!get_fsl(ctx, argv[1], REDISMODULE_WRITE, 1, &fsl, 1))
        return REDISMODULE_OK;

    if (fsl->length == LIST_SIZE)
        return RedisModule_ReplyWithError(ctx,"ERR list is full");

    if (fsl->length != 0 && fsl->list[fsl->length-1] >= ele)
        return RedisModule_ReplyWithError(ctx,"ERR new element has to be greater than the head element");

    fsl->list[fsl->length++] = ele;

    if (fsl->length >= 2)
        RedisModule_SignalKeyAsReady(ctx, argv[1]);

    return RedisModule_ReplyWithSimpleString(ctx, "OK");
}
