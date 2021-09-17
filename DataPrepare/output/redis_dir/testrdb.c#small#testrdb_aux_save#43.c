void testrdb_aux_save(RedisModuleIO *rdb, int when) {
    if (conf_aux_count==1) assert(when == REDISMODULE_AUX_AFTER_RDB);
    if (conf_aux_count==0) assert(0);
    if (when == REDISMODULE_AUX_BEFORE_RDB) {
        if (before_str) {
            RedisModule_SaveSigned(rdb, 1);
            RedisModule_SaveString(rdb, before_str);
        } else {
            RedisModule_SaveSigned(rdb, 0);
        }
    } else {
        if (after_str) {
            RedisModule_SaveSigned(rdb, 1);
            RedisModule_SaveString(rdb, after_str);
        } else {
            RedisModule_SaveSigned(rdb, 0);
        }
    }
}
