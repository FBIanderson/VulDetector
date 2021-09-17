void mp_decode_to_lua_type(lua_State *L, mp_cur *c) {
    mp_cur_need(c,1);

    /* If we return more than 18 elements, we must resize the stack to
     * fit all our return values.  But, there is no way to
     * determine how many objects a msgpack will unpack to up front, so
     * we request a +1 larger stack on each iteration (noop if stack is
     * big enough, and when stack does require resize it doubles in size) */
    luaL_checkstack(L, 1,
        "too many return values at once; "
        "use unpack_one or unpack_limit instead.");

    switch(c->p[0]) {
    case 0xcc:  /* uint 8 */
        mp_cur_need(c,2);
        lua_pushunsigned(L,c->p[1]);
        mp_cur_consume(c,2);
        break;
    case 0xd0:  /* int 8 */
        mp_cur_need(c,2);
        lua_pushinteger(L,(signed char)c->p[1]);
        mp_cur_consume(c,2);
        break;
    case 0xcd:  /* uint 16 */
        mp_cur_need(c,3);
        lua_pushunsigned(L,
            (c->p[1] << 8) |
             c->p[2]);
        mp_cur_consume(c,3);
        break;
    case 0xd1:  /* int 16 */
        mp_cur_need(c,3);
        lua_pushinteger(L,(int16_t)
            (c->p[1] << 8) |
             c->p[2]);
        mp_cur_consume(c,3);
        break;
    case 0xce:  /* uint 32 */
        mp_cur_need(c,5);
        lua_pushunsigned(L,
            ((uint32_t)c->p[1] << 24) |
            ((uint32_t)c->p[2] << 16) |
            ((uint32_t)c->p[3] << 8) |
             (uint32_t)c->p[4]);
        mp_cur_consume(c,5);
        break;
    case 0xd2:  /* int 32 */
        mp_cur_need(c,5);
        lua_pushinteger(L,
            ((int32_t)c->p[1] << 24) |
            ((int32_t)c->p[2] << 16) |
            ((int32_t)c->p[3] << 8) |
             (int32_t)c->p[4]);
        mp_cur_consume(c,5);
        break;
    case 0xcf:  /* uint 64 */
        mp_cur_need(c,9);
        lua_pushunsigned(L,
            ((uint64_t)c->p[1] << 56) |
            ((uint64_t)c->p[2] << 48) |
            ((uint64_t)c->p[3] << 40) |
            ((uint64_t)c->p[4] << 32) |
            ((uint64_t)c->p[5] << 24) |
            ((uint64_t)c->p[6] << 16) |
            ((uint64_t)c->p[7] << 8) |
             (uint64_t)c->p[8]);
        mp_cur_consume(c,9);
        break;
    case 0xd3:  /* int 64 */
        mp_cur_need(c,9);
#if LUA_VERSION_NUM < 503
        lua_pushnumber(L,
#else
        lua_pushinteger(L,
#endif
            ((int64_t)c->p[1] << 56) |
            ((int64_t)c->p[2] << 48) |
            ((int64_t)c->p[3] << 40) |
            ((int64_t)c->p[4] << 32) |
            ((int64_t)c->p[5] << 24) |
            ((int64_t)c->p[6] << 16) |
            ((int64_t)c->p[7] << 8) |
             (int64_t)c->p[8]);
        mp_cur_consume(c,9);
        break;
    case 0xc0:  /* nil */
        lua_pushnil(L);
        mp_cur_consume(c,1);
        break;
    case 0xc3:  /* true */
        lua_pushboolean(L,1);
        mp_cur_consume(c,1);
        break;
    case 0xc2:  /* false */
        lua_pushboolean(L,0);
        mp_cur_consume(c,1);
        break;
    case 0xca:  /* float */
        mp_cur_need(c,5);
        assert(sizeof(float) == 4);
        {
            float f;
            memcpy(&f,c->p+1,4);
            memrevifle(&f,4);
            lua_pushnumber(L,f);
            mp_cur_consume(c,5);
        }
        break;
    case 0xcb:  /* double */
        mp_cur_need(c,9);
        assert(sizeof(double) == 8);
        {
            double d;
            memcpy(&d,c->p+1,8);
            memrevifle(&d,8);
            lua_pushnumber(L,d);
            mp_cur_consume(c,9);
        }
        break;
    case 0xd9:  /* raw 8 */
        mp_cur_need(c,2);
        {
            size_t l = c->p[1];
            mp_cur_need(c,2+l);
            lua_pushlstring(L,(char*)c->p+2,l);
            mp_cur_consume(c,2+l);
        }
        break;
    case 0xda:  /* raw 16 */
        mp_cur_need(c,3);
        {
            size_t l = (c->p[1] << 8) | c->p[2];
            mp_cur_need(c,3+l);
            lua_pushlstring(L,(char*)c->p+3,l);
            mp_cur_consume(c,3+l);
        }
        break;
    case 0xdb:  /* raw 32 */
        mp_cur_need(c,5);
        {
            size_t l = ((size_t)c->p[1] << 24) |
                       ((size_t)c->p[2] << 16) |
                       ((size_t)c->p[3] << 8) |
                       (size_t)c->p[4];
            mp_cur_consume(c,5);
            mp_cur_need(c,l);
            lua_pushlstring(L,(char*)c->p,l);
            mp_cur_consume(c,l);
        }
        break;
    case 0xdc:  /* array 16 */
        mp_cur_need(c,3);
        {
            size_t l = (c->p[1] << 8) | c->p[2];
            mp_cur_consume(c,3);
            mp_decode_to_lua_array(L,c,l);
        }
        break;
    case 0xdd:  /* array 32 */
        mp_cur_need(c,5);
        {
            size_t l = ((size_t)c->p[1] << 24) |
                       ((size_t)c->p[2] << 16) |
                       ((size_t)c->p[3] << 8) |
                       (size_t)c->p[4];
            mp_cur_consume(c,5);
            mp_decode_to_lua_array(L,c,l);
        }
        break;
    case 0xde:  /* map 16 */
        mp_cur_need(c,3);
        {
            size_t l = (c->p[1] << 8) | c->p[2];
            mp_cur_consume(c,3);
            mp_decode_to_lua_hash(L,c,l);
        }
        break;
    case 0xdf:  /* map 32 */
        mp_cur_need(c,5);
        {
            size_t l = ((size_t)c->p[1] << 24) |
                       ((size_t)c->p[2] << 16) |
                       ((size_t)c->p[3] << 8) |
                       (size_t)c->p[4];
            mp_cur_consume(c,5);
            mp_decode_to_lua_hash(L,c,l);
        }
        break;
    default:    /* types that can't be idenitified by first byte value. */
        if ((c->p[0] & 0x80) == 0) {   /* positive fixnum */
            lua_pushunsigned(L,c->p[0]);
            mp_cur_consume(c,1);
        } else if ((c->p[0] & 0xe0) == 0xe0) {  /* negative fixnum */
            lua_pushinteger(L,(signed char)c->p[0]);
            mp_cur_consume(c,1);
        } else if ((c->p[0] & 0xe0) == 0xa0) {  /* fix raw */
            size_t l = c->p[0] & 0x1f;
            mp_cur_need(c,1+l);
            lua_pushlstring(L,(char*)c->p+1,l);
            mp_cur_consume(c,1+l);
        } else if ((c->p[0] & 0xf0) == 0x90) {  /* fix map */
            size_t l = c->p[0] & 0xf;
            mp_cur_consume(c,1);
            mp_decode_to_lua_array(L,c,l);
        } else if ((c->p[0] & 0xf0) == 0x80) {  /* fix map */
            size_t l = c->p[0] & 0xf;
            mp_cur_consume(c,1);
            mp_decode_to_lua_hash(L,c,l);
        } else {
            c->err = MP_CUR_ERROR_BADFMT;
        }
    }
}
