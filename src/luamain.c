//
// Created by LAB on 2021/8/10.
//
#include "lua.h"  // 基础运行时
#include "lualib.h"  // 内置标准库
#include "lauxlib.h" // 高级封装

#define ERROR(...) fprintf(stderr, __VA_ARGS__)

#define OK(...) fprintf(stdout, __VA_ARGS__)

#define okprintln(...) \
do{                   \
OK( __VA_ARGS__);              \
OK("\n");             \
}while(0)

#define errprintln(...) \
do{                   \
ERROR( __VA_ARGS__);              \
ERROR("\n");             \
}while(0)

int
getfield(lua_State *L, int index, char *fieldname)
{
    int tp = lua_getglobal(L, "color");
    if (tp != LUA_TTABLE)
    {
        ERROR("color is not a table");
        return 0;
    }
    int isnum = 0, ret = 0;
    lua_getfield(L, index, fieldname); // -1是value
    ret = (int) lua_tointegerx(L, -1, &isnum);

    if (!isnum)
    {
        luaL_error(L, "color field is not int");
        lua_pop(L, -1);
        return 0;
    }
    //    fprintf(stdout, "%d\n", ret);
    lua_pop(L, -1);
    return ret;
}

int
main(int argc, char **argv)
{
    //    fprintf(stdout, "ok here %d\n", __LINE__);
    int r, g, b;
    lua_State *L = luaL_newstate();
    if (L == NULL)
    {
        ERROR("bad here %d\n", __LINE__);
        return 1;
    }
    luaL_openlibs(L);

    //    fprintf(stdout, "ok here %d\n", __LINE__);
    if (luaL_dofile(L, "config.lua") != LUA_OK)
    {
        ERROR("%s\n", lua_tostring(L, -1));
        lua_pop(L, -1);
        return 1;
    }
    //    fprintf(stdout, "ok here %d\n", __LINE__);
    // 加载文件没有返回值

    ERROR("ok here stacklen%d lasttype %s %d\n", lua_gettop(L), lua_typename(L, -1), __LINE__);

    r = getfield(L, -1, "red");
    g = getfield(L, -1, "green");
    //    fprintf(stdout, "栈高度%d\n", lua_gettop(L));
    b = getfield(L, -1, "blue");
    //    fprintf(stdout, "栈高度%d\n", lua_gettop(L));
    OK("r=%d,g=%d,b=%d\n", r, g, b);
    lua_getglobal(L, "callback");
    lua_pushinteger(L, 11);
    lua_pushinteger(L, 10);
    lua_pcall(L, 2, 1, 0);
    int ok = 0;
    int ret = (int) lua_tointegerx(L, -1, &ok);
    if (!ok)
    {
        ERROR("err: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        return 1;
    }
    //    fprintf(stdout, "HIGHT %d\n", lua_gettop(L));  // 1
    //    OK("callback %d\n", ret);
    okprintln("callback %d", ret);
    lua_pop(L, 1);
    return 0;
}



