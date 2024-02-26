//
//  wm_lua_protocol.h
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

void wm_registerProtocolFunctions(lua_State *L);


#ifdef __cplusplus
}
#endif
