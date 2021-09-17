int fork_create(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    long long code_to_exit_with;
    if (argc != 2) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }
    RedisModule_StringToLongLong(argv[1], &code_to_exit_with);
    exitted_with_code = -1;
    child_pid = RedisModule_Fork(done_handler, (void*)0xdeadbeef);
    if (child_pid < 0) {
        RedisModule_ReplyWithError(ctx, "Fork failed");
        return REDISMODULE_OK;
    } else if (child_pid > 0) {
        /* parent */
        RedisModule_ReplyWithLongLong(ctx, child_pid);
        return REDISMODULE_OK;
    }

    /* child */
    RedisModule_Log(ctx, "notice", "fork child started");
    usleep(500000);
    RedisModule_Log(ctx, "notice", "fork child exiting");
    RedisModule_ExitFromChild(code_to_exit_with);
    /* unreachable */
    return 0;
}
