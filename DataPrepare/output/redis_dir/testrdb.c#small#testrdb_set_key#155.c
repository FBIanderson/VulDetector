int testrdb_set_key(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 3){
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    RedisModuleKey *key = RedisModule_OpenKey(ctx, argv[1], REDISMODULE_WRITE);
    RedisModuleString *str = RedisModule_ModuleTypeGetValue(key);
    if (str)
        RedisModule_FreeString(ctx, str);
    RedisModule_ModuleTypeSetValue(key, testrdb_type, argv[2]);
    RedisModule_RetainString(ctx, argv[2]);
    RedisModule_CloseKey(key);
    RedisModule_ReplyWithLongLong(ctx, 1);
    return REDISMODULE_OK;
}
