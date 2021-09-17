static int datatype_get(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 2) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    RedisModuleKey *key = RedisModule_OpenKey(ctx, argv[1], REDISMODULE_READ);
    DataType *dt = RedisModule_ModuleTypeGetValue(key);
    RedisModule_CloseKey(key);

    RedisModule_ReplyWithArray(ctx, 2);
    RedisModule_ReplyWithLongLong(ctx, dt->intval);
    RedisModule_ReplyWithString(ctx, dt->strval);
    return REDISMODULE_OK;
}
