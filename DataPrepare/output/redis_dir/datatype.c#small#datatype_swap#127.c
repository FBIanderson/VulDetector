static int datatype_swap(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 3) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    RedisModuleKey *a = RedisModule_OpenKey(ctx, argv[1], REDISMODULE_WRITE);
    RedisModuleKey *b = RedisModule_OpenKey(ctx, argv[2], REDISMODULE_WRITE);
    void *val = RedisModule_ModuleTypeGetValue(a);

    int error = (RedisModule_ModuleTypeReplaceValue(b, datatype, val, &val) == REDISMODULE_ERR ||
                 RedisModule_ModuleTypeReplaceValue(a, datatype, val, NULL) == REDISMODULE_ERR);
    if (!error)
        RedisModule_ReplyWithSimpleString(ctx, "OK");
    else
        RedisModule_ReplyWithError(ctx, "ERR failed");

    RedisModule_CloseKey(a);
    RedisModule_CloseKey(b);

    return REDISMODULE_OK;
}
