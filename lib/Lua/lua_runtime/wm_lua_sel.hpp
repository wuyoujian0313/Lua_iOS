//
//  wm_lua_sel.hpp
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





void wm_registerSelFunctions(lua_State *L);


#ifdef __cplusplus
}
#endif
