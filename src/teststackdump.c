//
// Created by LAB on 2021/8/16.
//
#include "stackdump.h"


int
main()
{
    lua_State *L=luaL_newstate();
    if (L==NULL)
    {
        fprintf(stderr,"out of mem\n");
        return 1;
    }
    lua_newtable(L);
    lua_pushinteger(L,1);
    lua_pushinteger(L,1);
    lua_settable(L,-3);
    lua_pushinteger(L,2);
    lua_pushinteger(L,2);
    lua_settable(L,-3);
    // [{1,2}]
    lua_pushinteger(L,3);
    lua_newtable(L); // [{1,2},3,{}]
    lua_pushinteger(L,1);
    lua_pushinteger(L,1);// [{1,2},3,{},1,1]
    lua_settable(L,-3); // [{1,2},3,{1}]
    lua_settable(L,-3); //[{1,2,{1}}]
    lua_pushinteger(L,4);
    lua_pushinteger(L,10); //[{1,2,{1}},4,10]
    lua_settable(L,-3); //[{1,2,{1},10}]


    lua_pushinteger(L,4);  // [{1,2,{1},10} ,4  ]
    stackdumnp(L,stdout);
    lua_close(L);
    return 0;

}