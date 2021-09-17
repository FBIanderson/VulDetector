void scan_key_callback(RedisModuleKey *key, RedisModuleString* field, RedisModuleString* value, void *privdata) {
    REDISMODULE_NOT_USED(key);
    scan_key_pd* pd = privdata;
    RedisModule_ReplyWithArray(pd->ctx, 2);
    RedisModule_ReplyWithString(pd->ctx, field);
    if (value)
        RedisModule_ReplyWithString(pd->ctx, value);
    else
        RedisModule_ReplyWithNull(pd->ctx);
    pd->nreplies++;
}
