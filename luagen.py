"""
Copyright (c) 2008-2021 synodriver <synodriver@gmail.com>
"""
import asyncio
from typing import List

import aiofiles


# lualib_name = "win32api"  # 生成的.c 文件名字 luaopen_{} 的名字

# include_name = "<Windows.h>"  # include头文件名字
# wrap_functions = []  # 要包装的C函数

async def write_copyright(f, name: str):
    await f.write(f"/* Copyright (c) 2008-2021 synodriver <{name}> */\n")


async def write_includes(f, includes: List[str]):
    for include in includes:
        await f.write(f"#include\"{include}\"\n")
    await f.write("""
#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#elif
#define DLLEXPORT
#endif /* _WIN32 */\n\n""")


async def write_luafunction(f, lualib_name: str, cfunction_name: str):
    """
    根据c函数名字 自动产生包装代码
    static int name(lua_State *L)
    :param f:
    :param  lualib_name: lua库名字
    :param cfunction_name: c函数原名
    :return:
    """
    await f.write("static int\n")
    await f.write(f"{lualib_name}_{cfunction_name}(lua_State *L)\n")  # lua里面看到的函数对应的C语言函数名字
    await f.write("{\n")
    await f.write("    double op1 = luaL_checknumber(L, 1);\n")
    await f.write(f"    double ret = {cfunction_name}(op1);\n")
    await f.write("    lua_pushnumber(L, ret);\n")
    await f.write("    return 1;\n")  # lua返回值个数
    await f.write("}\n\n")


async def write_luafuncs(f, lualib_name: str, cfunction_names: List[str]):
    for name in cfunction_names:
        await write_luafunction(f, lualib_name, name)


async def write_reg(f, lualib_name: str, cfunction_names: List[str]):
    """
    static luaL_Reg lua_funcs[] = {
    :param f:
    :param lualib_name:
    :param cfunction_names:
    :return:
    """
    await f.write("static luaL_Reg lua_funcs[] = {\n")
    for name in cfunction_names:
        await f.write("    {\"" + name + "\",     " + "&" + f"{lualib_name}_{name}" + "},\n")
    await f.write("    {NULL, NULL}\n")
    await f.write("};\n\n")


async def write_luaopen(f, lualib_name: str, ):
    """
    DLLEXPORT int luaopen_test(lua_State *L)
    :param f:
    :return:
    """
    await f.write(f"DLLEXPORT int\nluaopen_{lualib_name}(lua_State *L)\n")
    await f.write("{\n")
    await f.write("    luaL_newlib(L, lua_funcs);\n")
    await f.write("    return 1;\n")
    await f.write("}\n\n")


async def gencfile(f, includes: List[str], lualib_name: str, cfunction_names: List[str]):
    """
    产生c函数
    :param f:
    :param includes:
    :param lualib_name:
    :param cfunction_names:
    :return:
    """
    await write_copyright(f, "synodriver@gmail.com")
    await write_includes(f, includes)
    await write_luafuncs(f, lualib_name, cfunction_names)
    await write_reg(f, lualib_name, cfunction_names)
    await write_luaopen(f, lualib_name)


async def main():
    async with aiofiles.open("win32api" + ".c", "w", encoding='utf-8') as f:
        await gencfile(f, ["Windows.h", "lauxlib.h", "lua.h"], "win32api",
                       ["MessageboxA", "GetCursorPos", "SetCursorPos"])


if __name__ == "__main__":
    asyncio.run(main())
