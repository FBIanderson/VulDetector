int TestUnlink(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx);
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    RedisModuleKey *k = RedisModule_OpenKey(ctx, RedisModule_CreateStringPrintf(ctx, "unlinked"), REDISMODULE_WRITE | REDISMODULE_READ);
    if (!k) return failTest(ctx, "Could not create key");

    if (REDISMODULE_ERR == RedisModule_StringSet(k, RedisModule_CreateStringPrintf(ctx, "Foobar"))) {
        return failTest(ctx, "Could not set string value");
    }

    RedisModuleCallReply *rep = RedisModule_Call(ctx, "EXISTS", "c", "unlinked");
    if (!rep || RedisModule_CallReplyInteger(rep) != 1) {
        return failTest(ctx, "Key does not exist before unlink");
    }

    if (REDISMODULE_ERR == RedisModule_UnlinkKey(k)) {
        return failTest(ctx, "Could not unlink key");
    }

    rep = RedisModule_Call(ctx, "EXISTS", "c", "unlinked");
    if (!rep || RedisModule_CallReplyInteger(rep) != 0) {
        return failTest(ctx, "Could not verify key to be unlinked");
    }
    return RedisModule_ReplyWithSimpleString(ctx, "OK");

}
