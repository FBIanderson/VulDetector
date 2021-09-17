int HelloBlock_Reply(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    RedisModuleString *keyname = RedisModule_GetBlockedClientReadyKey(ctx);
    RedisModuleKey *key = RedisModule_OpenKey(ctx,keyname,REDISMODULE_READ);
    int type = RedisModule_KeyType(key);
    if (type != REDISMODULE_KEYTYPE_MODULE ||
        RedisModule_ModuleTypeGetType(key) != HelloType)
    {
        RedisModule_CloseKey(key);
        return REDISMODULE_ERR;
    }

    /* In case the key is able to serve our blocked client, let's directly
     * use our original command implementation to make this example simpler. */
    RedisModule_CloseKey(key);
    return HelloTypeRange_RedisCommand(ctx,argv,argc-1);
}
