/*
Copyright (c) 2018 jones

https://github.com/jones2000/hqchartPy2/blob/master/LICENSE

��Դ��Ŀ https://github.com/jones2000/hqchartPy2

jones_2000@163.com

*/

#pragma once

#include <Python.h>

namespace HQChart { namespace Complier { namespace Py {

class PyCallbackFunction
{
public:
	PyCallbackFunction(PyObject* p);
	~PyCallbackFunction();


	PyObject* Call(PyObject* pArgs);
private:

	PyObject* m_pCallbackFunction = NULL;	//�ص�����
	PyObject* m_pResult = NULL;				//��������
};


}
}
}