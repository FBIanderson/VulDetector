int anetNonBlock(char *err, int fd) {
    return anetSetBlock(err,fd,1);
}
