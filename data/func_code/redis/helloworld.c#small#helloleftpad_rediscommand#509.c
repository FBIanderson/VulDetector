int HelloLeftPad_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */
    long long padlen;

    if (argc != 4) return RedisModule_WrongArity(ctx);

    if ((RedisModule_StringToLongLong(argv[2],&padlen) != REDISMODULE_OK) ||
        (padlen< 0)) {
        return RedisModule_ReplyWithError(ctx,"ERR invalid padding length");
    }
    size_t strlen, chlen;
    const char *str = RedisModule_StringPtrLen(argv[1], &strlen);
    const char *ch = RedisModule_StringPtrLen(argv[3], &chlen);

    /* If the string is already larger than the target len, just return
     * the string itself. */
    if (strlen >= (size_t)padlen)
        return RedisModule_ReplyWithString(ctx,argv[1]);

    /* Padding must be a single character in this simple implementation. */
    if (chlen != 1)
        return RedisModule_ReplyWithError(ctx,
            "ERR padding must be a single char");

    /* Here we use our pool allocator, for our throw-away allocation. */
    padlen -= strlen;
    char *buf = RedisModule_PoolAlloc(ctx,padlen+strlen);
    for (long long j = 0; j < padlen; j++) buf[j] = *ch;
    memcpy(buf+padlen,str,strlen);

    RedisModule_ReplyWithStringBuffer(ctx,buf,padlen+strlen);
    return REDISMODULE_OK;
}
