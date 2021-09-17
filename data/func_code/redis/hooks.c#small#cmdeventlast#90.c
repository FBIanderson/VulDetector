int cmdEventLast(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 2){
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    EventElement *event = RedisModule_DictGet(event_log, argv[1], NULL);
    if (event && event->last_val_string)
        RedisModule_ReplyWithString(ctx, event->last_val_string);
    else if (event)
        RedisModule_ReplyWithLongLong(ctx, event->last_val_int);
    else
        RedisModule_ReplyWithNull(ctx);
    return REDISMODULE_OK;
}
