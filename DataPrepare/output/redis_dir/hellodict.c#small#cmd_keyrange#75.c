int cmd_KEYRANGE(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 4) return RedisModule_WrongArity(ctx);

    /* Parse the count argument. */
    long long count;
    if (RedisModule_StringToLongLong(argv[3],&count) != REDISMODULE_OK) {
        return RedisModule_ReplyWithError(ctx,"ERR invalid count");
    }

    /* Seek the iterator. */
    RedisModuleDictIter *iter = RedisModule_DictIteratorStart(
        Keyspace, ">=", argv[1]);

    /* Reply with the matching items. */
    char *key;
    size_t keylen;
    long long replylen = 0; /* Keep track of the amitted array len. */
    RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
    while((key = RedisModule_DictNextC(iter,&keylen,NULL)) != NULL) {
        if (replylen >= count) break;
        if (RedisModule_DictCompare(iter,"<=",argv[2]) == REDISMODULE_ERR)
            break;
        RedisModule_ReplyWithStringBuffer(ctx,key,keylen);
        replylen++;
    }
    RedisModule_ReplySetArrayLength(ctx,replylen);

    /* Cleanup. */
    RedisModule_DictIteratorStop(iter);
    return REDISMODULE_OK;
}
