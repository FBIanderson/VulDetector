int cmdEventCount(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 2){
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    EventElement *event = RedisModule_DictGet(event_log, argv[1], NULL);
    RedisModule_ReplyWithLongLong(ctx, event? event->count: 0);
    return REDISMODULE_OK;
}
