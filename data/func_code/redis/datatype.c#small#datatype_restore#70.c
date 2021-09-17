static int datatype_restore(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 3) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    DataType *dt = RedisModule_LoadDataTypeFromString(argv[2], datatype);
    if (!dt) {
        RedisModule_ReplyWithError(ctx, "Invalid data");
        return REDISMODULE_OK;
    }

    RedisModuleKey *key = RedisModule_OpenKey(ctx, argv[1], REDISMODULE_WRITE);
    RedisModule_ModuleTypeSetValue(key, datatype, dt);
    RedisModule_CloseKey(key);
    RedisModule_ReplyWithSimpleString(ctx, "OK");

    return REDISMODULE_OK;
}
