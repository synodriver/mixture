//
// Created by LAB on 2021/8/16.
//
#include "stackdump.h"

static void
printindentate(FILE *f, int indentate)
{
    for (int i = 0; i < indentate; i++)
    {
        fprintf(f, " ");
    }
}

void
dumpany(lua_State *L, FILE *f, int index, int indentate)
{
    lua_pushvalue(L, index);
    switch (lua_type(L, -1))
    {
        case LUA_TTABLE:
            dumptable(L, f, -1, indentate);
            break;
        case LUA_TBOOLEAN:
            dumpboolean(L, f, -1, indentate);
            break;
        case LUA_TFUNCTION:
            dumpfunction(L, f, -1, indentate);
            break;
        case LUA_TNIL:
            dumpnil(L, f, -1, indentate);
            break;
        case LUA_TNUMBER:
            dumpnumber(L, f, -1, indentate);
            break;
        case LUA_TSTRING:
            dumpstring(L, f, -1, indentate);
            break;
        case LUA_TLIGHTUSERDATA:
            dumplightuserdata(L, f, -1, indentate);
            break;
        case LUA_TUSERDATA:
            dumpuserdata(L, f, -1, indentate);
            break;
        case LUA_TTHREAD:
            dumpthread(L, f, -1, indentate);
            break;
        default:
            printindentate(f, indentate);
            fprintf(f, "unknown type %s", lua_typename(L, lua_type(L, -1)));
    }
    lua_pop(L, 1);
}

void
dumpboolean(lua_State *L, FILE *f, int index, int indentate)
{
    printindentate(f, indentate);
    lua_pushvalue(L, index);
    if (lua_toboolean(L, -1))
    {
        printf("%s", "true");
    }
    else
    {
        printf("%s", "false");
    }
    lua_pop(L, 1);
}

void
dumpnil(lua_State *L, FILE *f, int index, int indentate)
{
    printindentate(f, indentate);
    if (lua_isnil(L, index))
    {
        printf("%s", "nil");
    }
}

void
dumpnumber(lua_State *L, FILE *f, int index, int indentate)
{
    printindentate(f, indentate);
    int isnum = 0;
    lua_Number num = lua_tonumberx(L, index, &isnum);
    if (isnum)
    {
        printf("%lf", num);
    }
}

void
dumpstring(lua_State *L, FILE *f, int index, int indentate)
{
    printindentate(f, indentate);
    size_t len = 0;
    const char *str;
    if (lua_isstring(L, index))
    {
        str = lua_tolstring(L, index, &len);
    }
    fwrite(str, sizeof(char), len, stdout);
}

void
dumplightuserdata(lua_State *L, FILE *f, int index, int indentate)
{
    printindentate(f, indentate);
    printf("lightuserdate");
}

void
dumpuserdata(lua_State *L, FILE *f, int index, int indentate)
{
    printindentate(f, indentate);
    printf("userdate");
}

void
dumpthread(lua_State *L, FILE *f, int index, int indentate)
{
    printindentate(f, indentate);
    printf("thread");
}

void
dumpfunction(lua_State *L, FILE *f, int index, int indentate)
{
    lua_pushvalue(L, index); // 函数的副本
    fprintf(f, "%s", lua_typename(L, lua_type(L, -1)));
    lua_pop(L, 1);
}

// 对栈顶的表进行dump
void
dumptable(lua_State *L, FILE *f, int index, int indentate)
{
    lua_pushvalue(L, index); // 表的副本
    lua_pushnil(L);
    printindentate(f, indentate);
    fprintf(f, "table\n");
    while (lua_next(L, -2) != 0)
    {
        printindentate(f, indentate);
        dumpany(L, f, -2, indentate + 4);  /* KEY */
        printf(" : ");
        dumpany(L, f, -1, indentate + 4);  /* VALUE */
        fprintf(f, "\n");
        lua_pop(L, 1);
    }
    lua_pop(L, 1);

}

void
stackdumnp(lua_State *L, FILE *f)
{
    int stack_len = lua_gettop(L);
    for (int i = 1; i <= stack_len; i++)
    {
        dumpany(L, f, i, 0);
    }

}




