//
//  wm_lua_cwrapper.hpp
//  Lua
//
//  Created by youjian on 2024/1/16.
//

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

struct lua_State;

extern void wm_registerCFunctions(lua_State* L);











#ifdef __cplusplus
}
#endif
