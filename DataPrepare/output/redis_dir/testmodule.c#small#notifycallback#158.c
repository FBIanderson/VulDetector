int NotifyCallback(RedisModuleCtx *ctx, int type, const char *event,
                   RedisModuleString *key) {
  /* Increment a counter on the notifications: for each key notified we
   * increment a counter */
  RedisModule_Log(ctx, "notice", "Got event type %d, event %s, key %s", type,
                  event, RedisModule_StringPtrLen(key, NULL));

  RedisModule_Call(ctx, "HINCRBY", "csc", "notifications", key, "1");
  return REDISMODULE_OK;
}
