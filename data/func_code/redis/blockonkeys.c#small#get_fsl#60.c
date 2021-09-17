int get_fsl(RedisModuleCtx *ctx, RedisModuleString *keyname, int mode, int create, fsl_t **fsl, int reply_on_failure) {
    RedisModuleKey *key = RedisModule_OpenKey(ctx, keyname, mode);

    int type = RedisModule_KeyType(key);
    if (type != REDISMODULE_KEYTYPE_EMPTY && RedisModule_ModuleTypeGetType(key) != fsltype) {
        RedisModule_CloseKey(key);
        if (reply_on_failure)
            RedisModule_ReplyWithError(ctx, REDISMODULE_ERRORMSG_WRONGTYPE);
        return 0;
    }

    /* Create an empty value object if the key is currently empty. */
    if (type == REDISMODULE_KEYTYPE_EMPTY) {
        if (!create) {
            /* Key is empty but we cannot create */
            RedisModule_CloseKey(key);
            *fsl = NULL;
            return 1;
        }
        *fsl = fsl_type_create();
        RedisModule_ModuleTypeSetValue(key, fsltype, *fsl);
    } else {
        *fsl = RedisModule_ModuleTypeGetValue(key);
    }

    RedisModule_CloseKey(key);
    return 1;
}
