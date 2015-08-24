#include "Graph.h"
#include <string>
#include <Python.h>
#include <fstream>
using namespace std;
#pragma execution_character_set("utf-8")
PyObject* graph = NULL;
PyObject* result = NULL;										
PyObject* pPara = NULL;											
PyObject* pModule = NULL;										
PyObject* pFunc = NULL;
bool  IsFinal = false;
/*
	CALLFUNC : 调用函数
	PYINIT ： 确定要调的模块及函数
	PARA  :设置参数
	RESULT : 获取结果
*/
#define CALLFUNC  PyEval_CallObject(pFunc, pPara);
#define PYINIT(cnt, filename, funcname)								\
	pModule = PyImport_ImportModule((filename));					\
	if (pModule == nullptr)											\
		{															\
		std::cout << "pModule is null" << std::endl;				\
		}															\
	pFunc = PyObject_GetAttrString(pModule, (funcname));			\
	pPara = PyTuple_New((cnt));
#define PARA(loc,type,value)										\
	PyTuple_SetItem(pPara, (loc), Py_BuildValue(#type, (value)));
#define RESULT(type,name)											\
	PyArg_Parse(result,#type,(name));
Graph::Graph()
{
	std::cout << "structor" << std::endl;
	Py_Initialize();
	PYINIT(2, "newOne", "connect")
	std::string  UserName("neo4j");
	std::string  PassWord("123456");
	PARA(0,s,UserName.c_str())
	PARA(1,s,PassWord.c_str())
	graph = CALLFUNC
}
void Graph::NodeOpration::addNode(const char* jsonNode)const
{
	PYINIT(2, "newOne", "addNode")
	PARA(0,O,graph)
	PARA(1,s,jsonNode)
	result = CALLFUNC
}
void Graph::NodeOpration::addMultiNodesFromJsonFile(const char * filename)const
{
	PYINIT(2, "newOne", "addMultiNodesFromJsonFile")
	PARA(0,O,graph)
	PARA(1,s,filename)
	result = CALLFUNC
}
int Graph::NodeOpration::getNodeCount()
{
	PYINIT(1, "newOne", "getNodeCount")
	PARA(0,O,graph)
	result = CALLFUNC
	int count = 0;
	RESULT(i, &count)
	return count;
}
NODES Graph::NodeOpration::getAllNodes()const
{
	PYINIT(1, "newOne", "getAllNodes")
	PARA(0, O, graph)
	result = CALLFUNC
	int listSize = PyList_Size(result);
	NODES jsons;
	for (int i = 0; i < listSize; i++)
	{
		string s = PyString_AsString(PyList_GetItem(result, i));
		NODE node(s.substr(s.find_first_of('('), s.find_last_of(')')));
		jsons.push_back(node);
	}
	return jsons;
}
void Graph::NodeOpration::Delete(int ID)const
{
	PYINIT(2,"newOne","delete")
	PARA(0,O,graph)
	PARA(1, i, ID)
	CALLFUNC
}
void Graph::NodeOpration::DeleteAll()const
{
	PYINIT(1,"newOne","deleteAll")
	PARA(0, O, graph)
	CALLFUNC
}
void Graph::NodeOpration::addLabel(int node_id, std::string newLabel)const
{
	PYINIT(3, "newOne", "addLabel")
	PARA(0, O, graph)
	PARA(1, i, node_id)
	PARA(2, s, newLabel.c_str())
	CALLFUNC
}
void Graph::NodeOpration::addLabels(int node_id, vector<string>& labels)const
{
	PyObject* pTuple = PyTuple_New(labels.size());
	for (int i = 0; i < labels.size(); i++)
		PyTuple_SetItem(pTuple, i, Py_BuildValue("s", labels[i].c_str()));
	PYINIT(3,"newOne","addLabels")
	PARA(0,O,graph)
	PARA(1,i,node_id)
	PARA(2,O, pTuple)
	//PyTuple_SetItem(pPara, 2, Py_BuildValue("(items)",pTuple));
	CALLFUNC

}
void Graph::NodeOpration::addProperty(int node_id, PROPERTY property)const
{
		PYINIT(4, "newOne", "addProperty")
		PARA(0,O,graph)
		PARA(1,i,node_id)
		PARA(2,s,property.first.c_str())
		PARA(3,s,property.second.c_str())
		CALLFUNC
}
void Graph::NodeOpration::addProperties(int node_id, PROPERTYS propertys)const  
{
	PyObject* pDict = PyDict_New();
	for (auto& elem : propertys)
		PyDict_SetItem(pDict, Py_BuildValue("s", elem.first.c_str()), Py_BuildValue("s", elem.second.c_str()));
	PYINIT(3,"newOne","addProperties")
	PARA(0,O,graph)
	PARA(1,i,node_id)
	PARA(2,O,pDict)
	CALLFUNC
}
//---------------------------relationship操作函数

int Graph::Relationship::getRelationCount()const
{
	PYINIT(1,"newOne","getRelationCount")
	PARA(0,O,graph)
	result = CALLFUNC
	int count = -1;
	RESULT(i, &count)
	return count;
}
/*
	python那边没有写好。此功能没有完成。
*/
void Graph::Relationship::findShortestPathBetweemTwoNodes(int Node1_id, int Node2_id)const
{
	PYINIT(3,"newOne","findShortestPathBetweenTwoNodes")
	PARA(0,O,graph)
	PARA(1,i,Node1_id)
	PARA(2,i,Node2_id)
	CALLFUNC
}
std::vector<int> Graph::Relationship::getRelatedNodes(int Node_id)const
{
	PYINIT(2, "newOne", "getRelatedNodes")
	PARA(0, O, graph)
	PARA(1, i, Node_id)
	result = CALLFUNC
	std::vector<int> v;
	int len = PyList_Size(result);
	for (int i = 0; i < len; i++)
	{
		int relate_id = PyInt_AsSsize_t(PyList_GetItem(result, i));
		v.push_back(relate_id);
	}
	return v;
}
RELATIONS Graph::Relationship::getRelationBetwenNodes(int Node1_id, int Node2_id)const
{
	PYINIT(3, "newOne", "getRelationBetwenNodes")
	PARA(0, O, graph)
	PARA(1, i, Node1_id)
	PARA(2, i, Node2_id)
	result = CALLFUNC
	int len = PyList_Size(result);
	RELATIONS relations;
	for (int i = 0; i < len; i++)
	{
		PyObject *pValue = PyList_GetItem(result, i);
		int n = PyTuple_Size(pValue);
		int a, b;
		string s;
		a = PyInt_AsSsize_t(PyTuple_GetItem(pValue, 0));
		s = PyString_AsString(PyTuple_GetItem(pValue, 1));
		b = PyInt_AsSsize_t(PyTuple_GetItem(pValue, 2));
		RELATION relation(a,s,b);
		relations.push_back(relation);
	}
	return relations;
}
Graph::~Graph()
{	
	std::cout << "destructor" << std::endl;
	if (!IsFinal)
	{
		Py_Finalize();
		IsFinal = true;
	}	
}
