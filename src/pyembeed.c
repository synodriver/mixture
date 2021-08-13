//
// Created by Vin on 2021/8/4.
//
#include <stdio.h>
#include <Python.h>

#define COPYRIGHT \
"Type \"help\", \"copyright\", \"credits\" or \"license\" " \
"for more information."

// PYTHONPATH 环境变量加入 C:\ProgramData\Anaconda3\Lib
int main(int argc, char *argv[])
{
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    fprintf(stdout, "Python %s on %s\n", Py_GetVersion(), Py_GetPlatform());

    fprintf(stdout, "%s\n", COPYRIGHT);

//    PyRun_SimpleString("print(1+1)");
    PyRun_AnyFile(stdin, "<stdin>");

    Py_Finalize();
    return 0;
}