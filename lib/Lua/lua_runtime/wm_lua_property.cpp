//
//  wm_lua_property.cpp
//  Lua
//
//  Created by youjian on 2024/2/19.
//

#ifdef __cplusplus
extern "C" {
#endif

#include "wm_lua_property.h"
#include <string.h>
#import <objc/runtime.h>
#import <objc/message.h>

/* 获取属性名
 入参说明
 第一个参数：objc_property_t 属性
 
 返回值: const char* 属性名
 */

int wm_property_getName(lua_State *L) {
    
    objc_property_t property = static_cast<objc_property_t>(lua_touserdata(L, 1));
    if (property == nullptr) {
        lua_pop(L,1);
        lua_pushnil(L);
        return 1;
    }
    lua_pop(L,1);
    
    const char* name = property_getName(property);
    if (name == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushstring(L, name);
    
    return 1;
}

/* 获取属性特性描述字符串
 入参说明
 第一个参数：objc_property_t 属性
 
 返回值: const char* 属性特性描述字符串
 */

int wm_property_getAttributes(lua_State *L) {
    
    objc_property_t property = static_cast<objc_property_t>(lua_touserdata(L, 1));
    if (property == nullptr) {
        lua_pop(L,1);
        lua_pushnil(L);
        return 1;
    }
    lua_pop(L,1);
    
    const char* name = property_getAttributes(property);
    if (name == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushstring(L, name);
    
    return 1;
}

/* 获取属性中指定的特性
 入参说明
 第一个参数：objc_property_t 属性
 第二个参数：const char* 特性名称
 
 返回值: char* 属性特性描述字符串
 */

int wm_property_copyAttributeValue(lua_State *L) {
    
    objc_property_t property = static_cast<objc_property_t>(lua_touserdata(L, 1));
    if (property == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    
    const char* attrName = lua_tostring(L,2);
    lua_pop(L,2);
    if(attrName == nullptr || strlen(attrName) == 0) {
        lua_pushnil(L);
        return 1;
    }
    char* name  = (char*)calloc(strlen(attrName) + 1, sizeof(char*));
    strcpy(name, attrName);
    
    char* propertyName = property_copyAttributeValue(property,name);
    if(name) free(name);
    if (propertyName == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushstring(L, propertyName);
    
    return 1;
}


void wm_registerPropertyFunctions(lua_State *L) {
    lua_register(L, "property_getName", wm_property_getName);
    lua_register(L, "property_getAttributes", wm_property_getAttributes);
    lua_register(L, "property_copyAttributeValue", wm_property_copyAttributeValue);
}

#ifdef __cplusplus
}
#endif
