static void test_free_null(void) {
    void *redisCtx = NULL;
    void *reply = NULL;

    test("Don't fail when redisFree is passed a NULL value: ");
    redisFree(redisCtx);
    test_cond(redisCtx == NULL);

    test("Don't fail when freeReplyObject is passed a NULL value: ");
    freeReplyObject(reply);
    test_cond(reply == NULL);
}
