int TestIt(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    RedisModule_AutoMemory(ctx);
    RedisModuleCallReply *reply;

    /* Make sure the DB is empty before to proceed. */
    T("dbsize","");
    if (!TestAssertIntegerReply(ctx,reply,0)) goto fail;

    T("ping","");
    if (!TestAssertStringReply(ctx,reply,"PONG",4)) goto fail;

    T("test.call","");
    if (!TestAssertStringReply(ctx,reply,"OK",2)) goto fail;

    T("test.ctxflags","");
    if (!TestAssertStringReply(ctx,reply,"OK",2)) goto fail;

    T("test.string.append","");
    if (!TestAssertStringReply(ctx,reply,"foobar",6)) goto fail;

    T("test.unlink","");
    if (!TestAssertStringReply(ctx,reply,"OK",2)) goto fail;

    T("test.string.append.am","");
    if (!TestAssertStringReply(ctx,reply,"foobar",6)) goto fail;

    T("test.string.printf", "cc", "foo", "bar");
    if (!TestAssertStringReply(ctx,reply,"Got 3 args. argv[1]: foo, argv[2]: bar",38)) goto fail;

    T("test.notify", "");
    if (!TestAssertStringReply(ctx,reply,"OK",2)) goto fail;

    RedisModule_ReplyWithSimpleString(ctx,"ALL TESTS PASSED");
    return REDISMODULE_OK;

fail:
    RedisModule_ReplyWithSimpleString(ctx,
        "SOME TEST NOT PASSED! Check server logs");
    return REDISMODULE_OK;
}
