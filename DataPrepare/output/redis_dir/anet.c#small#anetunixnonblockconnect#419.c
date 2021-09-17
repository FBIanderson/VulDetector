int anetUnixNonBlockConnect(char *err, const char *path)
{
    return anetUnixGenericConnect(err,path,ANET_CONNECT_NONBLOCK);
}
