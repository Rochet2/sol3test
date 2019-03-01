#ifndef LUA_STACKINTERFACE_H
#define LUA_STACKINTERFACE_H

#include "wrap64.h"
#include "sol.h"

inline int64_t sol_lua_get(sol::types<int64_t>, lua_State* L, int index, sol::stack::record& tracking) {
    tracking.use(1);
    void* vp = lua_touserdata(L, index);
    wrap64<int64_t>* pscp = static_cast<wrap64<int64_t>*>(vp);
    return pscp->raw;
}

template <typename Handler>
inline bool sol_lua_check(sol::types<int64_t>, lua_State* L, int index, Handler&& handler, sol::stack::record& tracking) {
    tracking.use(1);
    if (luaL_testudata(L, index, "int64") == nullptr) {
        handler(L, index, sol::type::userdata, sol::type_of(L, index), "expected int64");
        return false;
    }
    return true;
}

inline int sol_lua_push(lua_State* L, const int64_t& c) {
    lua_checkstack(L, 1);
    void* ud = lua_newuserdata(L, sizeof(wrap64<int64_t>));
    wrap64<int64_t>* tud = static_cast<wrap64<int64_t>*>(ud);
    *tud = wrap64<int64_t>(c);
    luaL_newmetatable(L, "int64");
    lua_setmetatable(L, -2);
    return 1;
}

inline uint64_t sol_lua_get(sol::types<uint64_t>, lua_State* L, int index, sol::stack::record& tracking) {
    tracking.use(1);
    void* vp = lua_touserdata(L, index);
    wrap64<uint64_t>* pscp = static_cast<wrap64<uint64_t>*>(vp);
    return pscp->raw;
}

template <typename Handler>
inline bool sol_lua_check(sol::types<uint64_t>, lua_State* L, int index, Handler&& handler, sol::stack::record& tracking) {
    tracking.use(1);
    if (luaL_testudata(L, index, "uint64") == nullptr) {
        handler(L, index, sol::type::userdata, sol::type_of(L, index), "expected uint64");
        return false;
    }
    return true;
}

inline int sol_lua_push(lua_State* L, const uint64_t& c) {
    lua_checkstack(L, 1);
    void* ud = lua_newuserdata(L, sizeof(wrap64<uint64_t>));
    wrap64<uint64_t>* tud = static_cast<wrap64<uint64_t>*>(ud);
    *tud = wrap64<uint64_t>(c);
    luaL_newmetatable(L, "uint64");
    lua_setmetatable(L, -2);
    return 1;
}

#endif
