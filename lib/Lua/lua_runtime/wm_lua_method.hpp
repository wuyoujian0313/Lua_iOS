//
//  wm_lua_method.hpp
//  Lua
//
//  Created by youjian on 2024/2/19.
//
#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

void wm_registerMethodFunctions(lua_State *L);


#ifdef __cplusplus
}
#endif
