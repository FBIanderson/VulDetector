static void aeApiFree(aeEventLoop *eventLoop) {
    zfree(eventLoop->apidata);
}
