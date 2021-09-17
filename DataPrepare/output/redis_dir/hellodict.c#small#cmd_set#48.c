int cmd_SET(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 3) return RedisModule_WrongArity(ctx);
    RedisModule_DictSet(Keyspace,argv[1],argv[2]);
    /* We need to keep a reference to the value stored at the key, otherwise
     * it would be freed when this callback returns. */
    RedisModule_RetainString(NULL,argv[2]);
    return RedisModule_ReplyWithSimpleString(ctx, "OK");
}
