void redisFreeSdsCommand(sds cmd) {
    sdsfree(cmd);
}
