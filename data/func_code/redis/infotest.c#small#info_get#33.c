int info_get(RedisModuleCtx *ctx, RedisModuleString **argv, int argc, char field_type)
{
    if (argc != 3 && argc != 4) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }
    int err = REDISMODULE_OK;
    const char *section, *field;
    section = RedisModule_StringPtrLen(argv[1], NULL);
    field = RedisModule_StringPtrLen(argv[2], NULL);
    RedisModuleServerInfoData *info = RedisModule_GetServerInfo(ctx, section);
    if (field_type=='i') {
        long long ll = RedisModule_ServerInfoGetFieldSigned(info, field, &err);
        if (err==REDISMODULE_OK)
            RedisModule_ReplyWithLongLong(ctx, ll);
    } else if (field_type=='u') {
        unsigned long long ll = (unsigned long long)RedisModule_ServerInfoGetFieldUnsigned(info, field, &err);
        if (err==REDISMODULE_OK)
            RedisModule_ReplyWithLongLong(ctx, ll);
    } else if (field_type=='d') {
        double d = RedisModule_ServerInfoGetFieldDouble(info, field, &err);
        if (err==REDISMODULE_OK)
            RedisModule_ReplyWithDouble(ctx, d);
    } else if (field_type=='c') {
        const char *str = RedisModule_ServerInfoGetFieldC(info, field);
        if (str)
            RedisModule_ReplyWithCString(ctx, str);
    } else {
        RedisModuleString *str = RedisModule_ServerInfoGetField(ctx, info, field);
        if (str) {
            RedisModule_ReplyWithString(ctx, str);
            RedisModule_FreeString(ctx, str);
        } else
            err=REDISMODULE_ERR;
    }
    if (err!=REDISMODULE_OK)
        RedisModule_ReplyWithError(ctx, "not found");
    RedisModule_FreeServerInfo(ctx, info);
    return REDISMODULE_OK;
}
