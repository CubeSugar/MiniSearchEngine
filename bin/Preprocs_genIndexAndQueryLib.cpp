#include <iostream>
#include <Python/Python.h>

using namespace std;

int main()
{
	Py_Initialize();  
 
    if (!Py_IsInitialized())   
    {  
        return -1;  
    }  
 
    //PyRun_SimpleString("import sys");  
    PyRun_SimpleString("sys.path.append('./')");  
	PyObject *pName   = NULL;
	PyObject *pModule = NULL;
	PyObject *pDict   = NULL;
	PyObject *pFunc   = NULL;
	PyObject *pArgs   = NULL;  
  
    pName = PyString_FromString("Preprocs_generateIndexAndQueryLib");  
    pModule = PyImport_Import(pName);  
    if (!pModule)  
    {  
        printf("can't find Preprocs_generateIndexAndQueryLib.py");  
        getchar();  
        return -1;  
    }

    pDict = PyModule_GetDict(pModule);  
    if (!pDict)   
    {  
        return -1;  
    }  
 
    pFunc = PyDict_GetItemString(pDict, "generateIndexAndQueryLib"); 
    //PyEval_CallObject(pFunc, NULL); 
    if (!pFunc || !PyCallable_Check(pFunc))  
    {  
        printf("can't find function [generateIndexAndQueryLib]");  
        getchar();  
        return -1;  
    }

    Py_Finalize();
	return 0;
}