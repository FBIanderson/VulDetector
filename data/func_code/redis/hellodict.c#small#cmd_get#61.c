int cmd_GET(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 2) return RedisModule_WrongArity(ctx);
    RedisModuleString *val = RedisModule_DictGet(Keyspace,argv[1],NULL);
    if (val == NULL) {
        return RedisModule_ReplyWithNull(ctx);
    } else {
        return RedisModule_ReplyWithString(ctx, val);
    }
}
