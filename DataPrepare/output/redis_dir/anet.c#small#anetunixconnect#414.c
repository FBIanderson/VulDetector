int anetUnixConnect(char *err, const char *path)
{
    return anetUnixGenericConnect(err,path,ANET_CONNECT_NONE);
}
