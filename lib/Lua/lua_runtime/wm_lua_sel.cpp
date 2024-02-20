//
//  wm_lua_sel.cpp
//  Lua
//
//  Created by youjian on 2024/2/19.
//
#ifdef __cplusplus
extern "C" {
#endif

#include "wm_lua_sel.hpp"
#include <string.h>
#import <objc/runtime.h>
#import <objc/message.h>

/* 返回给定选择器指定的方法的名称
 入参说明
 第一个参数：SEL 属性
 
 返回值: const char* 方法名称
 */

int wm_sel_getName(lua_State *L) {
    
    SEL sel = static_cast<SEL>(lua_touserdata(L, 1));
    if (sel == nullptr) {
        lua_pop(L,1);
        lua_pushnil(L);
        return 1;
    }
    lua_pop(L,1);
    
    const char* name = sel_getName(sel);
    if (name == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushstring(L, name);
    
    return 1;
}

/* 在Objective-C Runtime系统中注册一个方法，将方法名映射到一个选择器，并返回这个选择器
 入参说明
 第一个参数： const char *属性名称
 
 返回值: SEL 方法
 */

int wm_sel_registerName(lua_State *L) {

    const char* selName = lua_tostring(L,2);
    lua_pop(L,2);
    if(selName == nullptr || strlen(selName) == 0) {
        lua_pushnil(L);
        return 1;
    }
    char* name  = (char*)calloc(strlen(selName) + 1, sizeof(char*));
    strcpy(name, selName);
    
    
    lua_pop(L,2);
    
    SEL sel = sel_registerName(name);
    if (name != nullptr) free(name);
    if (sel == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushlightuserdata(L, sel);
    
    return 1;
}


/* 在Objective-C Runtime系统中注册一个方法
 入参说明
 第一个参数： const char *方法名
 
 返回值: SEL 方法
 */

int wm_sel_getUid(lua_State *L) {
    
    const char* selName = lua_tostring(L,2);
    lua_pop(L,2);
    if(selName == nullptr || strlen(selName) == 0) {
        lua_pushnil(L);
        return 1;
    }
    char* name  = (char*)calloc(strlen(selName) + 1, sizeof(char*));
    strcpy(name, selName);
    
    
    lua_pop(L,2);
    
    SEL sel = sel_getUid(name);
    if (name != nullptr) free(name);
    if (sel == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushlightuserdata(L, sel);
    
    return 1;
}

/* 比较两个选择器
 入参说明
 第一个参数： SEL 方法
 第二个参数： SEL 方法
 
 返回值: BOOL 是否相等
 */

int wm_sel_isEqual(lua_State *L) {

    SEL sel1 = static_cast<SEL>(lua_touserdata(L, 1));
    if (sel1 == nullptr) {
        lua_pop(L,2);
        lua_pushboolean(L, 0);
        return 1;
    }
    
    SEL sel2 = static_cast<SEL>(lua_touserdata(L, 2));
    if (sel2 == nullptr) {
        lua_pop(L,2);
        lua_pushboolean(L, 0);
        return 1;
    }
    lua_pop(L,2);
    
    BOOL isEqual = sel_isEqual(sel1, sel2);
    lua_pushboolean(L, isEqual?1:0);
    
    return 1;
}

void wm_registerSelFunctions(lua_State *L) {
    lua_register(L, "sel_getName", wm_sel_getName);
    lua_register(L, "sel_registerName", wm_sel_registerName);
    lua_register(L, "sel_getUid", wm_sel_getUid);
    lua_register(L, "sel_isEqual", wm_sel_isEqual);
}

#ifdef __cplusplus
}
#endif
