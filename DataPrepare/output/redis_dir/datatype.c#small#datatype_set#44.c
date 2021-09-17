static int datatype_set(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 4) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    long long intval;

    if (RedisModule_StringToLongLong(argv[2], &intval) != REDISMODULE_OK) {
        RedisModule_ReplyWithError(ctx, "Invalid integr value");
        return REDISMODULE_OK;
    }

    RedisModuleKey *key = RedisModule_OpenKey(ctx, argv[1], REDISMODULE_WRITE);
    DataType *dt = RedisModule_Calloc(sizeof(DataType), 1);
    dt->intval = intval;
    dt->strval = argv[3];
    RedisModule_RetainString(ctx, dt->strval);

    RedisModule_ModuleTypeSetValue(key, datatype, dt);
    RedisModule_CloseKey(key);
    RedisModule_ReplyWithSimpleString(ctx, "OK");

    return REDISMODULE_OK;
}
