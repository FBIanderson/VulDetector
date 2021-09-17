static redisContext *do_connect(struct config config) {
    redisContext *c = NULL;

    if (config.type == CONN_TCP) {
        c = redisConnect(config.tcp.host, config.tcp.port);
    } else if (config.type == CONN_SSL) {
        c = redisConnect(config.ssl.host, config.ssl.port);
    } else if (config.type == CONN_UNIX) {
        c = redisConnectUnix(config.unix_sock.path);
    } else if (config.type == CONN_FD) {
        /* Create a dummy connection just to get an fd to inherit */
        redisContext *dummy_ctx = redisConnectUnix(config.unix_sock.path);
        if (dummy_ctx) {
            int fd = disconnect(dummy_ctx, 1);
            printf("Connecting to inherited fd %d\n", fd);
            c = redisConnectFd(fd);
        }
    } else {
        assert(NULL);
    }

    if (c == NULL) {
        printf("Connection error: can't allocate redis context\n");
        exit(1);
    } else if (c->err) {
        printf("Connection error: %s\n", c->errstr);
        redisFree(c);
        exit(1);
    }

    if (config.type == CONN_SSL) {
        do_ssl_handshake(c, config);
    }

    return select_database(c);
}
