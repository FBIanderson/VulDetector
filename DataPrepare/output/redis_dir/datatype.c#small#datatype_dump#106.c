static int datatype_dump(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 2) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    RedisModuleKey *key = RedisModule_OpenKey(ctx, argv[1], REDISMODULE_READ);
    DataType *dt = RedisModule_ModuleTypeGetValue(key);
    RedisModule_CloseKey(key);

    RedisModuleString *reply = RedisModule_SaveDataTypeToString(ctx, dt, datatype);
    if (!reply) {
        RedisModule_ReplyWithError(ctx, "Failed to save");
        return REDISMODULE_OK;
    }

    RedisModule_ReplyWithString(ctx, reply);
    RedisModule_FreeString(ctx, reply);
    return REDISMODULE_OK;
}
