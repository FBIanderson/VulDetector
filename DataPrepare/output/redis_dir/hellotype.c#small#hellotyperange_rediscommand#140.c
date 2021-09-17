int HelloTypeRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */

    if (argc != 4) return RedisModule_WrongArity(ctx);
    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    int type = RedisModule_KeyType(key);
    if (type != REDISMODULE_KEYTYPE_EMPTY &&
        RedisModule_ModuleTypeGetType(key) != HelloType)
    {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    long long first, count;
    if (RedisModule_StringToLongLong(argv[2],&first) != REDISMODULE_OK ||
        RedisModule_StringToLongLong(argv[3],&count) != REDISMODULE_OK ||
        first < 0 || count < 0)
    {
        return RedisModule_ReplyWithError(ctx,
            "ERR invalid first or count parameters");
    }

    struct HelloTypeObject *hto = RedisModule_ModuleTypeGetValue(key);
    struct HelloTypeNode *node = hto ? hto->head : NULL;
    RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
    long long arraylen = 0;
    while(node && count--) {
        RedisModule_ReplyWithLongLong(ctx,node->value);
        arraylen++;
        node = node->next;
    }
    RedisModule_ReplySetArrayLength(ctx,arraylen);
    return REDISMODULE_OK;
}
