//
//  wm_lua_object.cpp
//  Lua
//
//  Created by youjian on 2024/1/18.
//
#ifdef __cplusplus
extern "C" {
#endif

#include "wm_lua_object.h"
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
    
    lua_pop(L,3);
    Ivar var = object_setInstanceVariable(caller,name,value);
    if (name != nullptr) free(name);
    if (var == nullptr) {
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
    
    lua_pop(L,3);
    Ivar var = object_getInstanceVariable(caller,name,value);
    if (name != nullptr) free(name);
    if (var == nullptr) {
        lua_pushboolean(L, 0);
        return 1;
    }
    
    lua_pushlightuserdata(L, var);
    
    return 1;
}

/* 返回对象中实例变量的值
 入参说明
 第一个参数：对象
 第二个参数：Ivar 对象中实例对象信息
 
 返回值：id 变量的值
 */

int wm_object_getIvar(lua_State *L) {
    
    id caller = static_cast<id>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    
    Ivar var = static_cast<Ivar>(lua_touserdata(L, 2));
    if (var == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    
    lua_pop(L,2);
    
    id value = object_getIvar(caller,var);
    if (value == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushlightuserdata(L, value);
    
    return 1;
}

/* 设置对象中实例变量的值
 入参说明
 第一个参数：对象
 第二个参数：Ivar 对象中实例对象信息
 第三个参数：id 变量的新值
 
 返回值：无返回值
 */

int wm_object_setIvar(lua_State *L) {
    
    id caller = static_cast<id>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,3);
        return 0;
    }
    
    Ivar var = static_cast<Ivar>(lua_touserdata(L, 2));
    if (var == nullptr) {
        lua_pop(L,3);
        return 0;
    }
    
    id value = static_cast<id>(lua_touserdata(L, 3));
    if (value == nullptr) {
        lua_pop(L,3);
        return 0;
    }
    
    lua_pop(L,3);
    object_setIvar(caller, var, value);
    
    return 0;
}

/* 返回给定对象的类名
 入参说明
 第一个参数：id 对象
 
 返回值: const char* 类名
 */

int wm_object_getClassName(lua_State *L) {
    
    id caller = static_cast<id>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,1);
        lua_pushnil(L);
        return 1;
    }
    lua_pop(L,1);
    
    const char * className = object_getClassName(caller);
    if (className == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushstring(L, className);
    
    return 1;
}

/* 返回对象的类
 入参说明
 第一个参数：id 对象
 
 返回值: Class 类class对象
 */

int wm_object_getClass(lua_State *L) {
    
    id caller = static_cast<id>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,1);
        lua_pushnil(L);
        return 1;
    }
    lua_pop(L,1);
    
    Class cls = object_getClass(caller);
    if (cls == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushlightuserdata(L, cls);
    
    return 1;
}

/* 设置对象的类
 入参说明
 第一个参数：id 对象
 第二个参数：Class 对象
 
 返回值: Class 类class对象
 */

int wm_object_setClass(lua_State *L) {
    
    id caller = static_cast<id>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    
    
    Class cls = static_cast<Class>(lua_touserdata(L, 2));
    if (cls == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    
    lua_pop(L,2);
    Class objClass = object_setClass(caller,cls);
    if (objClass == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlightuserdata(L, objClass);
    
    return 1;
}



/* 返回指定类的类定义
 入参说明
 第一个参数：const char* 类名
 
 返回值: Class 类class对象
 */

int wm_objc_lookUpClass(lua_State *L) {
    
    const char* name = lua_tostring(L,1);
    if(name == nullptr || strlen(name) == 0) {
        lua_pop(L,1);
        lua_pushnil(L);
        return 1;
    }
    
    lua_pop(L,1);
    char* classname  = (char*)calloc(strlen(name) + 1, sizeof(char*));
    strcpy(classname, name);
    
    if(classname == nullptr) {
        if (classname != nullptr) free(classname);
        lua_pushnil(L);
        return 1;
    }
    Class cls = objc_lookUpClass(classname);
    if (classname != nullptr) free(classname);
    
    if (cls == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlightuserdata(L, cls);
    
    return 1;
}

/* 返回指定类的类定义
 入参说明
 第一个参数：const char* 类名
 
 返回值: Class 类class对象
 */

int wm_objc_getClass(lua_State *L) {
    
    const char* name = lua_tostring(L,1);
    if(name == nullptr || strlen(name) == 0) {
        lua_pop(L,1);
        lua_pushnil(L);
        return 1;
    }
    
    lua_pop(L,1);
    char* classname  = (char*)calloc(strlen(name) + 1, sizeof(char*));
    strcpy(classname, name);
    
    if(classname == nullptr) {
        if (classname != nullptr) free(classname);
        lua_pushnil(L);
        return 1;
    }
    Class cls = objc_getClass(classname);
    if (classname != nullptr) free(classname);
    
    if (cls == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlightuserdata(L, cls);
    
    return 1;
}

/* 返回指定类的类定义
 入参说明
 第一个参数：const char* 类名
 
 返回值: Class 类class对象
 */

int wm_objc_getRequiredClass(lua_State *L) {
    
    const char* name = lua_tostring(L,1);
    if(name == nullptr || strlen(name) == 0) {
        lua_pop(L,1);
        lua_pushnil(L);
        return 1;
    }
    
    lua_pop(L,1);
    char* classname  = (char*)calloc(strlen(name) + 1, sizeof(char*));
    strcpy(classname, name);
    
    if(classname == nullptr) {
        if (classname != nullptr) free(classname);
        lua_pushnil(L);
        return 1;
    }
    Class cls = objc_getRequiredClass(classname);
    if (classname != nullptr) free(classname);
    
    if (cls == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlightuserdata(L, cls);
    
    return 1;
}

/* 返回指定类的元类
 入参说明
 第一个参数：const char* 类名
 
 返回值: Class 类class对象
 */
int wm_objc_getMetaClass(lua_State *L) {
    
    const char* name = lua_tostring(L,1);
    if(name == nullptr || strlen(name) == 0) {
        lua_pop(L,1);
        lua_pushnil(L);
        return 1;
    }
    
    lua_pop(L,1);
    char* classname  = (char*)calloc(strlen(name) + 1, sizeof(char*));
    strcpy(classname, name);
    
    if(classname == nullptr) {
        if (classname != nullptr) free(classname);
        lua_pushnil(L);
        return 1;
    }
    Class cls = objc_getMetaClass(classname);
    if (classname != nullptr) free(classname);
    
    if (cls == nullptr) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlightuserdata(L, cls);
    
    return 1;
}

/* 设置关联对象
 入参说明
 第一个参数：id 对象
 第二个参数：const void* 关联对象的Key
 第三个参数：关联的对象
 第四个参数：关联策略
 
 返回值: 无
 */

int wm_objc_setAssociatedObject(lua_State *L) {
    
    id caller = static_cast<id>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,4);
        return 0;
    }
    
    const void* key = static_cast<const void*>(lua_touserdata(L, 2));
    if (key == nullptr) {
        lua_pop(L,4);
        return 0;
    }
    
    id value = static_cast<id>(lua_touserdata(L, 3));
    if (value == nullptr) {
        lua_pop(L,4);
        return 0;
    }
    
    objc_AssociationPolicy policy = (objc_AssociationPolicy)lua_tointeger(L, 4);
    lua_pop(L,4);
    objc_setAssociatedObject(caller,key,value,policy);
    
    return 0;
}


/* 获取关联对象
 入参说明
 第一个参数：id 对象
 第二个参数：const void* 关联对象的Key
 
 返回值: id 关联对象
 */

int wm_objc_getAssociatedObject(lua_State *L) {
    
    id caller = static_cast<id>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    
    const void* key = static_cast<const void*>(lua_touserdata(L, 2));
    if (key == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    
    lua_pop(L,2);
    id  obj = objc_getAssociatedObject(caller,key);
    if (obj == nullptr) {
        lua_pop(L,2);
        lua_pushnil(L);
        return 1;
    }
    
    lua_pushlightuserdata(L, obj);
    
    return 1;
}

/* 移除所有关联对象
 入参说明
 第一个参数：id 对象
 
 返回值: 无
 */

int wm_objc_removeAssociatedObjects(lua_State *L) {
    
    id caller = static_cast<id>(lua_touserdata(L, 1));
    if (caller == nullptr) {
        lua_pop(L,1);
        return 0;
    }
    
    lua_pop(L,1);
    objc_removeAssociatedObjects(caller);
    
    return 0;
}



void wm_registerObjectFunctions(lua_State *L) {
    lua_register(L, "object_setInstanceVariable", wm_object_setInstanceVariable);
    lua_register(L, "object_getInstanceVariable", wm_object_getInstanceVariable);
    lua_register(L, "object_getIvar", wm_object_getIvar);
    lua_register(L, "object_setIvar", wm_object_setIvar);
    lua_register(L, "object_getClassName", wm_object_getClassName);
    lua_register(L, "object_getClass", wm_object_getClass);
    lua_register(L, "object_setClass", wm_object_setClass);
    
    lua_register(L, "objc_lookUpClass", wm_objc_lookUpClass);
    lua_register(L, "objc_getClass", wm_objc_getClass);
    lua_register(L, "objc_getRequiredClass", wm_objc_getRequiredClass);
    lua_register(L, "objc_getMetaClass", wm_objc_getMetaClass);
    lua_register(L, "objc_setAssociatedObject", wm_objc_setAssociatedObject);
    lua_register(L, "objc_getAssociatedObject", wm_objc_getAssociatedObject);
    lua_register(L, "objc_removeAssociatedObjects", wm_objc_removeAssociatedObjects);
}





#ifdef __cplusplus
}
#endif
