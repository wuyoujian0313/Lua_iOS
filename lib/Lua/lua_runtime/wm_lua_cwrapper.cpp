//
//  wm_lua_cwrapper.cpp
//  Lua
//
//  Created by youjian on 2024/1/16.
//
#ifdef __cplusplus
extern "C" {
#endif

#include "wm_lua_cwrapper.h"
#include "wm_lua_class.h"
#include "wm_lua_object.hpp"


void wm_registerCFunctions(lua_State* L) {
    wm_registerClassFunctions(L);
    wm_registerObjectFunctions(L);
}

#ifdef __cplusplus
}
#endif
