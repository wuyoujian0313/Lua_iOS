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
#include "wm_lua_object.h"
#include "wm_lua_method.h"
#include "wm_lua_property.h"
#include "wm_lua_protocol.h"
#include "wm_lua_sel.h"
#include "wm_lua_block.h"





void wm_registerCFunctions(lua_State* L) {
    wm_registerClassFunctions(L);
    wm_registerObjectFunctions(L);
    wm_registerMethodFunctions(L);
    wm_registerPropertyFunctions(L);
    wm_registerProtocolFunctions(L);
    wm_registerSelFunctions(L);
    wm_registerBlockFunctions(L);
}

#ifdef __cplusplus
}
#endif
