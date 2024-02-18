//
//  wm_lua_class.hpp
//  Lua
//
//  Created by youjian on 2024/1/16.
//

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"




void wm_registerClassFunctions(lua_State *L);





#ifdef __cplusplus
}
#endif
