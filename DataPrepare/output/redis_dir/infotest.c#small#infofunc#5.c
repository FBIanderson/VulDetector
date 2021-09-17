void InfoFunc(RedisModuleInfoCtx *ctx, int for_crash_report) {
    RedisModule_InfoAddSection(ctx, "");
    RedisModule_InfoAddFieldLongLong(ctx, "global", -2);
    RedisModule_InfoAddFieldULongLong(ctx, "uglobal", (unsigned long long)-2);

    RedisModule_InfoAddSection(ctx, "Spanish");
    RedisModule_InfoAddFieldCString(ctx, "uno", "one");
    RedisModule_InfoAddFieldLongLong(ctx, "dos", 2);

    RedisModule_InfoAddSection(ctx, "Italian");
    RedisModule_InfoAddFieldLongLong(ctx, "due", 2);
    RedisModule_InfoAddFieldDouble(ctx, "tre", 3.3);

    RedisModule_InfoAddSection(ctx, "keyspace");
    RedisModule_InfoBeginDictField(ctx, "db0");
    RedisModule_InfoAddFieldLongLong(ctx, "keys", 3);
    RedisModule_InfoAddFieldLongLong(ctx, "expires", 1);
    RedisModule_InfoEndDictField(ctx);

    if (for_crash_report) {
        RedisModule_InfoAddSection(ctx, "Klingon");
        RedisModule_InfoAddFieldCString(ctx, "one", "wa’");
        RedisModule_InfoAddFieldCString(ctx, "two", "cha’");
        RedisModule_InfoAddFieldCString(ctx, "three", "wej");
    }

}
