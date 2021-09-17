void PingReceiver(RedisModuleCtx *ctx, const char *sender_id, uint8_t type, const unsigned char *payload, uint32_t len) {
    RedisModule_Log(ctx,"notice","PING (type %d) RECEIVED from %.*s: '%.*s'",
        type,REDISMODULE_NODE_ID_LEN,sender_id,(int)len, payload);
    RedisModule_SendClusterMessage(ctx,NULL,MSGTYPE_PONG,(unsigned char*)"Ohi!",4);
    RedisModule_Call(ctx, "INCR", "c", "pings_received");
}
