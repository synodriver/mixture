//
// Created by LAB on 2021/8/16.
//

#ifndef LUAWIN32_STACKDUMP_H
#define LUAWIN32_STACKDUMP_H

#include "lua.h"  // 基础运行时
#include "lauxlib.h"  // 内置标准库


void dumpany(lua_State *L, FILE *f, int index, int indentate);

void dumptable(lua_State *L, FILE *f, int index, int indentate);

void dumpboolean(lua_State *L, FILE *f, int index, int indentate);

void dumpfunction(lua_State *L, FILE *f, int index, int indentate);

void dumpnil(lua_State *L, FILE *f, int index, int indentate);

void dumpnumber(lua_State *L, FILE *f, int index, int indentate);

void dumpstring(lua_State *L, FILE *f, int index, int indentate);

void dumplightuserdata(lua_State *L, FILE *f, int index, int indentate);

void dumpuserdata(lua_State *L, FILE *f, int index, int indentate);

void dumpthread(lua_State *L, FILE *f, int index, int indentate);

void stackdumnp(lua_State *L, FILE *f);


#endif //LUAWIN32_STACKDUMP_H
