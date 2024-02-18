//
//  wm_lua_object.cpp
//  Lua
//
//  Created by youjian on 2024/1/18.
//
#ifdef __cplusplus
extern "C" {
#endif

#include "wm_lua_object.hpp"
#include <string.h>
#import <objc/runtime.h>
#import <objc/message.h>



/* 修改类实例的实例变量的值
 入参说明
 第一个参数：对象
 第二个参数：属性名
 第三个参数：修改后的值
 
 返回值：Ivar
 */

int wm_object_setInstanceVariable(lua_State *L) {
    id caller = static_cast<id>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,3);
        lua_pushboolean(L, 0);
        return 1;
    }
    
    const char* property = lua_tostring(L,2);
    if(property == nullptr || strlen(property) == 0) {
        lua_pop(L,3);
        lua_pushnil(L);
        return 1;
    }
    char* name  = (char*)calloc(strlen(property) + 1, sizeof(char*));
    strcpy(name, property);
    
    void* value = static_cast<void*>(lua_touserdata(L, 3));
    if (value == nullptr) {
        lua_pop(L,3);
        if (name != nullptr) free(name);
        lua_pushboolean(L, 0);
        return 1;
    }
    
    
    Ivar var = object_setInstanceVariable(caller,name,value);
    if (var == nullptr) {
        lua_pop(L,3);
        lua_pushboolean(L, 0);
        return 1;
    }
    
    lua_pushlightuserdata(L, var);
    
    return 1;
}

/* 修改类实例的实例变量的值
 入参说明
 第一个参数：对象
 第二个参数：属性名
 第三个参数：返回获取的对象
 
 返回值：Ivar
 */

int wm_object_getInstanceVariable(lua_State *L) {
    
    id caller = static_cast<id>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,3);
        lua_pushboolean(L, 0);
        return 1;
    }
    
    const char* property = lua_tostring(L,2);
    if(property == nullptr || strlen(property) == 0) {
        lua_pop(L,3);
        lua_pushnil(L);
        return 1;
    }
    char* name  = (char*)calloc(strlen(property) + 1, sizeof(char*));
    strcpy(name, property);
    
    void** value = static_cast<void**>(lua_touserdata(L, 3));
    if (value == nullptr) {
        lua_pop(L,3);
        if (name != nullptr) free(name);
        lua_pushboolean(L, 0);
        return 1;
    }
    
    
    Ivar var = object_getInstanceVariable(caller,name,value);
    if (var == nullptr) {
        lua_pop(L,3);
        lua_pushboolean(L, 0);
        return 1;
    }
    
    lua_pushlightuserdata(L, var);
    
    return 1;
}


void wm_registerObjectFunctions(lua_State *L) {
    lua_register(L, "object_setInstanceVariable", wm_object_setInstanceVariable);
    lua_register(L, "object_getInstanceVariable", wm_object_getInstanceVariable);
}





#ifdef __cplusplus
}
#endif
