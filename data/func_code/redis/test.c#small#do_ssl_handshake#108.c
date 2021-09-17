static void do_ssl_handshake(redisContext *c, struct config config) {
#ifdef HIREDIS_TEST_SSL
    redisSecureConnection(c, config.ssl.ca_cert, config.ssl.cert, config.ssl.key, NULL);
    if (c->err) {
        printf("SSL error: %s\n", c->errstr);
        redisFree(c);
        exit(1);
    }
#else
    (void) c;
    (void) config;
#endif
}
