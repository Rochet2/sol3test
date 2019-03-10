#ifndef LUA_SOL_H
#define LUA_SOL_H

// I think I'm paranoid
// Read top of http://sol2.readthedocs.io/en/latest/safety.html
#ifndef SOL_CHECK_ARGUMENTS
#define SOL_CHECK_ARGUMENTS true
#endif

#include "forward.hpp"

#include "wrap64.h"
int64_t sol_lua_get(sol::types<int64_t>, lua_State* L, int index, sol::stack::record& tracking);
template <typename Handler> bool sol_lua_check(sol::types<int64_t>, lua_State* L, int index, Handler&& handler, sol::stack::record& tracking);
int sol_lua_push(lua_State* L, const int64_t& c);
uint64_t sol_lua_get(sol::types<uint64_t>, lua_State* L, int index, sol::stack::record& tracking);
template <typename Handler> bool sol_lua_check(sol::types<uint64_t>, lua_State* L, int index, Handler&& handler, sol::stack::record& tracking);
int sol_lua_push(lua_State* L, const uint64_t& c);

#include "sol.hpp"

#endif
