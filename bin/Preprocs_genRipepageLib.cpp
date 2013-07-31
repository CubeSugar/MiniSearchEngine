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
  
    pName = PyString_FromString("Preprocs_generateRipepageLib");  
    pModule = PyImport_Import(pName);  
    if (!pModule)  
    {  
        printf("can't find Preprocs_generateRipepageLib.py");  
        getchar();  
        return -1;  
    }

    pDict = PyModule_GetDict(pModule);  
    if (!pDict)   
    {  
        return -1;  
    }  
 
    pFunc = PyDict_GetItemString(pDict, "generateRipepageLib"); 
    //PyEval_CallObject(pFunc, NULL); 
    if (!pFunc || !PyCallable_Check(pFunc))  
    {  
        printf("can't find function [generateRipepageLib]");  
        getchar();  
        return -1;  
    }

    Py_Finalize();
	return 0;
}