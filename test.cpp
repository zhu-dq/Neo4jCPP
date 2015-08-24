#include "Graph.h"
#include <Python.h>
#include "Singleton.hpp"
#include <iostream>
#include <fstream>
#include "OperJson.h"
using namespace std;
#pragma execution_character_set("utf-8")

int main()
{

	std::string jsonnode = R"({"ID": "12345", "AVP_LIST": [{"ATTRIBUTE": "topic_equivalent_webpage", "VALUE": "http://baike.baidu.com/view/20338.htm"}, {"ATTRIBUTE": "name", "VALUE": "�ɵ�"}, {"ATTRIBUTE": "entity_pv", "VALUE": "672"}, {"ATTRIBUTE": "entity_category", "VALUE": "���,����"}, {"ATTRIBUTE": "�鳤", "VALUE": "���졢��೤�����ϰ�"}, {"ATTRIBUTE": "��Ҫ����", "VALUE": "���塢��ū����Խ��"}, {"ATTRIBUTE": "��������", "VALUE": "����ר������"}, {"ATTRIBUTE": "����", "VALUE": "������"}, {"ATTRIBUTE": "��Ҫ����", "VALUE": "��Խ��"}, {"ATTRIBUTE": "��������", "VALUE": "��ѯ"}, {"ATTRIBUTE": "��ѧ���", "VALUE": "����"}, {"ATTRIBUTE": "�׶�", "VALUE": "��������������"}, {"ATTRIBUTE": "���", "VALUE": "��"}, {"ATTRIBUTE": "��������", "VALUE": "����"}, {"ATTRIBUTE": "��Ҫ����", "VALUE": "����"}, {"ATTRIBUTE": "��Ҫ�ڽ�", "VALUE": "����"}, {"ATTRIBUTE": "��Ҫ����", "VALUE": "�����������͡�����������"}, {"ATTRIBUTE": "��Ҫ����", "VALUE": "����"}, {"ATTRIBUTE": "������", "VALUE": "����"}, {"ATTRIBUTE": "ʱ��", "VALUE": "������"}, {"ATTRIBUTE": "��Ҫ����", "VALUE": "����"}, {"ATTRIBUTE": "��������", "VALUE": "����"}, {"ATTRIBUTE": "�������", "VALUE": "1400/1040/2560��˵����һ��"}, {"ATTRIBUTE": "��Ҫ����", "VALUE": "��ū"}, {"ATTRIBUTE": "��Ҫ����", "VALUE": "����"}, {"ATTRIBUTE": "�˿�����", "VALUE": "Լ6000�򣨹�Ԫ2�꣩"}, {"ATTRIBUTE": "Ӣ������", "VALUE": "TheHanDynasty"},  {"ATTRIBUTE": "��Ҫ����", "VALUE": "����"}, {"ATTRIBUTE": "��������", "VALUE": "����"}, {"ATTRIBUTE": "�ٷ�����", "VALUE": "��ԭ�ٻ�"}, {"ATTRIBUTE": "��Ҫ����", "VALUE": "��"},{"ATTRIBUTE": "������", "VALUE": "��"}]})";
	Graph *g = Singleton<Graph>::instance();
	Graph::NodeOpration noderef;
	Graph::Relationship relationref;
	//noderef.addMultiNodesFromJsonFile("data4.txt");
	//relationref.findShortestPathBetweemTwoNodes(1,5);
	//relationref.getRelationBetwenNodes(1,5);
	relationref.getRelatedNodes(5);
	//����ǿ 135  51616
	//��Ϳ134    9590469
	//��ӳ�� 137
	//¬�� 138
	/*
		//---------------------����  propertyref
	PROPERTY p;
	p.first = "����";
	p.second = "����";
	PROPERTY p1;
	p1.first = "ʵ����";
	p1.second = "CILB";
	PROPERTYS ps;
	ps.push_back(p);
	ps.push_back(p1);
	noderef.addProperties(141,ps);
	//noderef.addProperty(141,p);
	*/
	/*
		//------------------����  labelref
	vector<string> v;
	v.push_back("ɵ��ɵ��");
	noderef.addLabels(141,v);
	*/
	//noderef.addLabel(141,"ɵ��");	
	//noderef.addMultiNodesFromJsonFile("data4.txt");
	//noderef.addNode(jsonnode.c_str());
	//noderef.getNodeCount();
	//noderef.Delete("137");
	//noderef.DeleteAll();
	/*
	//---------����getAllNodes+
	NODES	nodes=noderef.getAllNodes();
	ofstream fout("output.txt");
	if (!fout)
		return 0;
	for (auto& elem : nodes)
	{
		//std::cout << elem.getJson() << std::endl;
		fout << elem.getJson() << endl;
	}
	*/
	/*
	//-------------����jsconcpp
	OperJson operjson;
	fstream fin("data4.txt");
	string s;
	while (getline(fin, s))
	{
		operjson.Resolve_json(s);
		//noderef.addNode(s.c_str());
	}
	*/
	system("pause");
	return 0;
}