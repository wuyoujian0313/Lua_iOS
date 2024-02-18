//
//  wm_lua_object.hpp
//  Lua
//
//  Created by youjian on 2024/1/18.
//

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"





void wm_registerObjectFunctions(lua_State *L);


#ifdef __cplusplus
}
#endif
