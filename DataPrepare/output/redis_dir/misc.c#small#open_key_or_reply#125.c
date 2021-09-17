RedisModuleKey *open_key_or_reply(RedisModuleCtx *ctx, RedisModuleString *keyname, int mode) {
    RedisModuleKey *key = RedisModule_OpenKey(ctx, keyname, mode);
    if (!key) {
        RedisModule_ReplyWithError(ctx, "key not found");
        return NULL;
    }
    return key;
}
