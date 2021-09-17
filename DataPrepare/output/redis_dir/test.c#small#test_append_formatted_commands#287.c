static void test_append_formatted_commands(struct config config) {
    redisContext *c;
    redisReply *reply;
    char *cmd;
    int len;

    c = do_connect(config);

    test("Append format command: ");

    len = redisFormatCommand(&cmd, "SET foo bar");

    test_cond(redisAppendFormattedCommand(c, cmd, len) == REDIS_OK);

    assert(redisGetReply(c, (void*)&reply) == REDIS_OK);

    free(cmd);
    freeReplyObject(reply);

    disconnect(c, 0);
}
