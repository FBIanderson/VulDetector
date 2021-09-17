void aeStop(aeEventLoop *eventLoop) {
    eventLoop->stop = 1;
}
