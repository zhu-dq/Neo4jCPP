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

	std::string jsonnode = R"({"ID": "12345", "AVP_LIST": [{"ATTRIBUTE": "topic_equivalent_webpage", "VALUE": "http://baike.baidu.com/view/20338.htm"}, {"ATTRIBUTE": "name", "VALUE": "成电"}, {"ATTRIBUTE": "entity_pv", "VALUE": "672"}, {"ATTRIBUTE": "entity_category", "VALUE": "年代,朝代"}, {"ATTRIBUTE": "组长", "VALUE": "邵领、冯班长、符老板"}, {"ATTRIBUTE": "主要民族", "VALUE": "汉族、匈奴、南越族"}, {"ATTRIBUTE": "政治体制", "VALUE": "君主专制政体"}, {"ATTRIBUTE": "货币", "VALUE": "汉五铢"}, {"ATTRIBUTE": "主要民族", "VALUE": "南越族"}, {"ATTRIBUTE": "国家领袖", "VALUE": "刘询"}, {"ATTRIBUTE": "文学体裁", "VALUE": "汉赋"}, {"ATTRIBUTE": "首都", "VALUE": "长安（今西安）"}, {"ATTRIBUTE": "简称", "VALUE": "汉"}, {"ATTRIBUTE": "国家领袖", "VALUE": "刘彻"}, {"ATTRIBUTE": "主要民族", "VALUE": "汉族"}, {"ATTRIBUTE": "主要宗教", "VALUE": "道教"}, {"ATTRIBUTE": "主要城市", "VALUE": "长安、宛、临淄、洛阳、邯郸"}, {"ATTRIBUTE": "主要城市", "VALUE": "长安"}, {"ATTRIBUTE": "所属洲", "VALUE": "亚洲"}, {"ATTRIBUTE": "时区", "VALUE": "东八区"}, {"ATTRIBUTE": "主要城市", "VALUE": "邯郸"}, {"ATTRIBUTE": "国家领袖", "VALUE": "刘邦"}, {"ATTRIBUTE": "国土面积", "VALUE": "1400/1040/2560万（说法不一）"}, {"ATTRIBUTE": "主要民族", "VALUE": "匈奴"}, {"ATTRIBUTE": "主要城市", "VALUE": "洛阳"}, {"ATTRIBUTE": "人口数量", "VALUE": "约6000万（公元2年）"}, {"ATTRIBUTE": "英文名称", "VALUE": "TheHanDynasty"},  {"ATTRIBUTE": "主要城市", "VALUE": "临淄"}, {"ATTRIBUTE": "中文名称", "VALUE": "西汉"}, {"ATTRIBUTE": "官方语言", "VALUE": "中原官话"}, {"ATTRIBUTE": "主要城市", "VALUE": "宛"},{"ATTRIBUTE": "烦烦烦", "VALUE": "吐"}]})";
	Graph *g = Singleton<Graph>::instance();
	Graph::NodeOpration noderef;
	Graph::Relationship relationref;
	//noderef.addMultiNodesFromJsonFile("data4.txt");
	//relationref.findShortestPathBetweemTwoNodes(1,5);
	//relationref.getRelationBetwenNodes(1,5);
	relationref.getRelatedNodes(5);
	//王永强 135  51616
	//糊涂134    9590469
	//吴映洁 137
	//卢毅 138
	/*
		//---------------------测试  propertyref
	PROPERTY p;
	p.first = "本科";
	p.second = "西邮";
	PROPERTY p1;
	p1.first = "实验室";
	p1.second = "CILB";
	PROPERTYS ps;
	ps.push_back(p);
	ps.push_back(p1);
	noderef.addProperties(141,ps);
	//noderef.addProperty(141,p);
	*/
	/*
		//------------------测试  labelref
	vector<string> v;
	v.push_back("傻吊傻吊");
	noderef.addLabels(141,v);
	*/
	//noderef.addLabel(141,"傻吊");	
	//noderef.addMultiNodesFromJsonFile("data4.txt");
	//noderef.addNode(jsonnode.c_str());
	//noderef.getNodeCount();
	//noderef.Delete("137");
	//noderef.DeleteAll();
	/*
	//---------测试getAllNodes+
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
	//-------------测试jsconcpp
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