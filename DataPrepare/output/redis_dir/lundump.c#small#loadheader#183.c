static void LoadHeader(LoadState* S)
{
 char h[LUAC_HEADERSIZE];
 char s[LUAC_HEADERSIZE];
 luaU_header(h);
 LoadBlock(S,s,LUAC_HEADERSIZE);
 IF (memcmp(h,s,LUAC_HEADERSIZE)!=0, "bad header");
}
