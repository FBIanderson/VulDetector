int anetBlock(char *err, int fd) {
    return anetSetBlock(err,fd,0);
}
