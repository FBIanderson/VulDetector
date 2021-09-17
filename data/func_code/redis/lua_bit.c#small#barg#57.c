static UBits barg(lua_State *L, int idx)
{
  BitNum bn;
  UBits b;
#if LUA_VERSION_NUM < 502
  bn.n = lua_tonumber(L, idx);
#else
  bn.n = luaL_checknumber(L, idx);
#endif
#if defined(LUA_NUMBER_DOUBLE)
  bn.n += 6755399441055744.0;  /* 2^52+2^51 */
#ifdef SWAPPED_DOUBLE
  b = (UBits)(bn.b >> 32);
#else
  b = (UBits)bn.b;
#endif
#elif defined(LUA_NUMBER_INT) || defined(LUA_NUMBER_LONG) || \
      defined(LUA_NUMBER_LONGLONG) || defined(LUA_NUMBER_LONG_LONG) || \
      defined(LUA_NUMBER_LLONG)
  if (sizeof(UBits) == sizeof(lua_Number))
    b = bn.b;
  else
    b = (UBits)(SBits)bn.n;
#elif defined(LUA_NUMBER_FLOAT)
#error "A 'float' lua_Number type is incompatible with this library"
#else
#error "Unknown number type, check LUA_NUMBER_* in luaconf.h"
#endif
#if LUA_VERSION_NUM < 502
  if (b == 0 && !lua_isnumber(L, idx)) {
    luaL_typerror(L, idx, "number");
  }
#endif
  return b;
}
