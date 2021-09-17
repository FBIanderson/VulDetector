int fork_kill(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    UNUSED(argv);
    UNUSED(argc);
    if (RedisModule_KillForkChild(child_pid) != REDISMODULE_OK)
        RedisModule_ReplyWithError(ctx, "KillForkChild failed");
    else
        RedisModule_ReplyWithLongLong(ctx, 1);
    child_pid = -1;
    return REDISMODULE_OK;
}
