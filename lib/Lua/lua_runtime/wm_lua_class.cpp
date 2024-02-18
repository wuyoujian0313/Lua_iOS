//
//  wm_lua_class.cpp
//  Lua
//
//  Created by youjian on 2024/1/16.
//

#ifdef __cplusplus
extern "C" {
#endif

#include "wm_lua_class.h"
#include <string.h>
#import <objc/runtime.h>
#import <objc/message.h>




/* 获取类的类名
 入参说明
 第一个参数，Class对象
 返回值：Class对象的类名
 */

int wm_class_getName(lua_State *L) {
    Class caller = static_cast<Class>(lua_touserdata(L, 1));
    lua_pop(L, 1);
    if (caller == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    const char* className = class_getName(caller);
    if(className == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushstring(L, className);
    
    return 1;
}


/* 获取类的父类
 入参说明
 第一个参数，Class对象
 返回值：Class对象的父类Class对象
 */

int wm_class_getSuperclass(lua_State *L) {
    Class caller = static_cast<Class>(lua_touserdata(L, 1));
    lua_pop(L, 1);
    if (caller == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    Class superCls = class_getSuperclass(caller);
    if(superCls == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlightuserdata(L, superCls);
    
    return 1;
}



/* 判断给定的Class是否是一个元类
 入参说明
 第一个参数，Class对象
 返回值：BOOL
 */

int wm_class_isMetaClass(lua_State *L) {
    Class caller = static_cast<Class>(lua_touserdata(L, 1));
    lua_pop(L, 1);
    if (caller == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    BOOL isBool = class_isMetaClass(caller);
    lua_pushboolean(L, isBool?1:0);
    
    return 1;
}




/* 获取实例大小
 入参说明
 第一个参数，Class对象
 返回值：size_t
 */


int wm_class_getInstanceSize(lua_State *L) {
    Class caller = static_cast<Class>(lua_touserdata(L, 1));
    lua_pop(L, 1);
    if (caller == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    size_t size = class_getInstanceSize(caller);
    lua_pushinteger(L, size);
    
    return 1;
}


/* 获取类中指定名称实例成员变量的信息
 入参说明
 第一个参数，Class对象
 第二个参数，属性名
 返回值：Ivar
 */

int wm_class_getInstanceVariable(lua_State *L) {
    Class caller = static_cast<Class>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    const char* property = lua_tostring(L,2);
    lua_pop(L,2);
    if(property == nullptr || strlen(property) == 0) {
        lua_pushnil(L);
        return 1;
    }
    char* name  = (char*)calloc(strlen(property) + 1, sizeof(char*));
    strcpy(name, property);
    
    Ivar ivar = class_getInstanceVariable(caller, name);
    if(name != nullptr) free(name);
    
    if (ivar == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushlightuserdata(L, ivar);
    

    return 1;
}

/* 获取类成员变量的信息
 入参说明
 第一个参数，Class对象
 第二个参数，属性名
 返回值：Ivar
 */

int wm_class_getClassVariable(lua_State *L) {
    Class caller = static_cast<Class>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    const char* property = lua_tostring(L,2);
    lua_pop(L,2);
    if(property == nullptr || strlen(property) == 0) {
        lua_pushnil(L);
        return 1;
    }
    char* name  = (char*)calloc(strlen(property) + 1, sizeof(char*));
    strcpy(name, property);
    
    Ivar ivar = class_getClassVariable(caller, name);
    if(name != nullptr) free(name);
    
    if (ivar == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushlightuserdata(L, ivar);
    

    return 1;
}

/* 获取指定的属性
 入参说明
 第一个参数，Class对象
 第二个参数，属性名
 返回值：objc_property_t
 */

int wm_class_getProperty(lua_State *L) {
    
    Class caller = static_cast<Class>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    const char* property = lua_tostring(L,2);
    lua_pop(L,2);
    if(property == nullptr || strlen(property) == 0) {
        lua_pushnil(L);
        return 1;
    }
    char* name  = (char*)calloc(strlen(property) + 1, sizeof(char*));
    strcpy(name, property);
    
    objc_property_t p = class_getProperty(caller, name);
    if(name != nullptr) free(name);
    
    if (p == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushlightuserdata(L, p);
    
    
    return 1;
}

/* 获取实例方法
 入参说明
 第一个参数，Class对象
 第二个参数，方法SeL
 返回值：Method
 */

int wm_class_getInstanceMethod(lua_State *L) {
    
    Class caller = static_cast<Class>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    
    SEL methoSEL = static_cast<SEL>(lua_touserdata(L, 2));
    lua_pop(L,2);
    
    Method method = class_getInstanceMethod(caller, methoSEL);
    if (method == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushlightuserdata(L, method);
    return 1;
}

/* 获取类方法
 入参说明
 第一个参数，Class对象
 第二个参数，方法SeL
 返回值：Method
 */

int wm_class_getClassMethod(lua_State *L) {
    
    Class caller = static_cast<Class>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    
    SEL methoSEL = static_cast<SEL>(lua_touserdata(L, 2));
    lua_pop(L,2);
    
    Method method = class_getClassMethod(caller, methoSEL);
    if (method == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushlightuserdata(L, method);
    return 1;
}

/* 类实例是否响应指定的selector
 入参说明
 第一个参数，Class对象
 第二个参数，方法SeL
 返回值：BOOL
 */

int wm_class_respondsToSelector(lua_State *L) {
    
    Class caller = static_cast<Class>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,2);
        lua_pushboolean(L, 0);
        return 1;
    }
    
    SEL methoSEL = static_cast<SEL>(lua_touserdata(L, 2));
    lua_pop(L,2);
    if (methoSEL == nullptr) {
        lua_pushboolean(L, 0);
        return 1;
    }
    
    BOOL isExist = class_respondsToSelector(caller, methoSEL);

    lua_pushboolean(L, isExist?1:0);
    return 1;
}


/* 返回类是否实现指定的协议
 入参说明
 第一个参数，Class对象
 第二个参数，协议Protocol的指针
 返回值：BOOL
 */

int wm_class_conformsToProtocol(lua_State *L) {
    
    Class caller = static_cast<Class>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,2);
        lua_pushboolean(L, 0);
        return 1;
    }
    
    Protocol *protocol = static_cast<Protocol*>(lua_touserdata(L, 2));
    lua_pop(L,2);
    if (protocol == nullptr) {
        lua_pushboolean(L, 0);
        return 1;
    }
    
    BOOL isExist = class_conformsToProtocol(caller, protocol);

    lua_pushboolean(L, isExist?1:0);
    return 1;
}


void wm_registerClassFunctions(lua_State *L) {
    lua_register(L, "class_getName", wm_class_getName);
    lua_register(L, "class_getSuperclass", wm_class_getSuperclass);
    lua_register(L, "class_isMetaClass", wm_class_isMetaClass);
    lua_register(L, "class_getInstanceSize", wm_class_getInstanceSize);
    lua_register(L, "class_getInstanceVariable", wm_class_getInstanceVariable);
    lua_register(L, "class_getClassVariable", wm_class_getClassVariable);
    
    lua_register(L, "class_getProperty", wm_class_getProperty);
    lua_register(L, "class_getInstanceMethod", wm_class_getInstanceMethod);
    lua_register(L, "class_getClassMethod", wm_class_getClassMethod);
    lua_register(L, "class_respondsToSelector", wm_class_respondsToSelector);
    lua_register(L, "class_conformsToProtocol", wm_class_conformsToProtocol);
    
}



#ifdef __cplusplus
}
#endif
