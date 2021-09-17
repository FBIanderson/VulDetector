int HelloRandArray_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 2) return RedisModule_WrongArity(ctx);
    long long count;
    if (RedisModule_StringToLongLong(argv[1],&count) != REDISMODULE_OK ||
        count < 0)
        return RedisModule_ReplyWithError(ctx,"ERR invalid count");

    /* To reply with an array, we call RedisModule_ReplyWithArray() followed
     * by other "count" calls to other reply functions in order to generate
     * the elements of the array. */
    RedisModule_ReplyWithArray(ctx,count);
    while(count--) RedisModule_ReplyWithLongLong(ctx,rand());
    return REDISMODULE_OK;
}
