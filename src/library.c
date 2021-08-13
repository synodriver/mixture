//#include "lua.h"
#include <math.h>
#include "Windows.h"
#include "lauxlib.h"


#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#elif
#define DLLEXPORT
#endif /* _WIN32 */

static int add2(lua_State *L)
{
    double op1 = luaL_checknumber(L, 1);
    double op2 = luaL_checknumber(L, 2);
    lua_pushnumber(L, op1 + op2);
    return 1;
}

static int sub2(lua_State *L)
{
    double op1 = luaL_checknumber(L, 1);
    double op2 = luaL_checknumber(L, 2);
    lua_pushnumber(L, op1 - op2);
    return 1;
}

static int l_sin(lua_State *L)
{
    double d = lua_tonumber(L, 1); /* get argument */
    lua_pushnumber(L, sin(d)); /* push result */
    return 1; /* number of results */
}

static int message(lua_State *L)
{
    char *word = luaL_checkstring(L, 1);
    char *title = luaL_checkstring(L, 2);
    double type = luaL_checknumber(L, 3);
    int ret = MessageBoxA(0, word, title, (int) type);
    lua_pushnumber(L, ret);
    return 1;
}

static luaL_Reg lua_funcs[] = {
        {"add",     &add2},
        {"sub",     &sub2},
        {"sin",     &l_sin},
        {"message", &message},
        {NULL, NULL}
};

DLLEXPORT
int luaopen_test(lua_State *L)
{
    luaL_newlib(L, lua_funcs);
    return 1;
}