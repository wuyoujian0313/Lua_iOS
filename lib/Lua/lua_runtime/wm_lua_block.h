//
//  wm_lua_block.h
//  Lua
//
//  Created by youjian on 2024/2/20.
//

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"





void wm_registerBlockFunctions(lua_State *L);


#ifdef __cplusplus
}
#endif
