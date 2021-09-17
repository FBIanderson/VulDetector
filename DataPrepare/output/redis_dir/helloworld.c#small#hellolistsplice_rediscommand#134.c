int HelloListSplice_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 4) return RedisModule_WrongArity(ctx);

    RedisModuleKey *srckey = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    RedisModuleKey *dstkey = RedisModule_OpenKey(ctx,argv[2],
        REDISMODULE_READ|REDISMODULE_WRITE);

    /* Src and dst key must be empty or lists. */
    if ((RedisModule_KeyType(srckey) != REDISMODULE_KEYTYPE_LIST &&
         RedisModule_KeyType(srckey) != REDISMODULE_KEYTYPE_EMPTY) ||
        (RedisModule_KeyType(dstkey) != REDISMODULE_KEYTYPE_LIST &&
         RedisModule_KeyType(dstkey) != REDISMODULE_KEYTYPE_EMPTY))
    {
        RedisModule_CloseKey(srckey);
        RedisModule_CloseKey(dstkey);
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    long long count;
    if ((RedisModule_StringToLongLong(argv[3],&count) != REDISMODULE_OK) ||
        (count < 0)) {
        RedisModule_CloseKey(srckey);
        RedisModule_CloseKey(dstkey);
        return RedisModule_ReplyWithError(ctx,"ERR invalid count");
    }

    while(count-- > 0) {
        RedisModuleString *ele;

        ele = RedisModule_ListPop(srckey,REDISMODULE_LIST_TAIL);
        if (ele == NULL) break;
        RedisModule_ListPush(dstkey,REDISMODULE_LIST_HEAD,ele);
        RedisModule_FreeString(ctx,ele);
    }

    size_t len = RedisModule_ValueLength(srckey);
    RedisModule_CloseKey(srckey);
    RedisModule_CloseKey(dstkey);
    RedisModule_ReplyWithLongLong(ctx,len);
    return REDISMODULE_OK;
}
