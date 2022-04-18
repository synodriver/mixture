//
// Created by Vin on 2021/8/6.
//
#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include "Windows.h"

static PyObject *
test_message(PyObject *self, PyObject *args)
{
    const char *word, *title;
    int type, ret;
    if (!PyArg_ParseTuple(args, "ssi", &word, &title, &type))
    {
        return NULL;
    }
    ret = MessageBoxA(0, word, title, type);
    return PyLong_FromLong(ret);

}

static PyObject *
check_self(PyObject *self, PyObject *args)
{
    return Py_TYPE(self);
}

static PyMethodDef test_methods[] = {
        {"message", &test_message, METH_VARARGS, PyDoc_STR("message(word:str,title:str,type:int)->int")},
        {"check_self", &check_self, METH_NOARGS, PyDoc_STR("check_self()->type")},
        {NULL, NULL, 0,                          NULL}
};

static PyModuleDef testmodule = {
        PyModuleDef_HEAD_INIT,
        "test",
        PyDoc_STR("test"),
        -1,
        test_methods
};

PyMODINIT_FUNC
PyInit__test(void)
{
    PyObject *m;
    m = PyModule_Create(&testmodule);
    if (m == NULL)
    {
        return NULL;
    }
    return m;
}
