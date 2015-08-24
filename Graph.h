#ifndef _GRAPH_H
#define _GRAPH_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;
#define NODEOPRATION Graph::NodeOpration
#define NODE Graph::NodeOpration::Node
#define NODES std::vector<Graph::NodeOpration::Node>
#define PROPERTY   pair<string,string>
#define PROPERTYS  vector<PROPERTY>
#define RELATIONSHIP Graph::Relationship
#define RELATION Graph::Relationship::Relation
#define RELATIONS std::vector<Graph::Relationship::Relation>
class Graph
{
public:
	/*
		构造：连接到neo4j数据库
	*/
	Graph();
	~Graph();

	class NodeOpration
	{
	public:
		class Node
		{
		private:
			std::string str_json = "";
		public:
			Node(const string &strjson) :str_json(strjson){}
			std::string getJson()
			{
				return str_json;
			}
			int getNode_id()
			{
				return atoi((str_json.substr(str_json.find_first_of('(') + 2, str_json.find_first_of(':') - 2)).c_str());
			}
			PROPERTYS& getNodeProperties()const
			{
			
			}
		};
		int getNodeCount();
		NODES getAllNodes()const;
		void addNode(const char* jsonNode)const;
		void addMultiNodesFromJsonFile(const char* filename)const;
		void Delete(int ID)const;
		void DeleteAll()const;
		void addLabel(int node_id, std::string newLabel)const;
		void addLabels(int node_id, vector<string>& labels)const;
		void addProperty(int node_id,  PROPERTY property)const;
		void addProperties(int node_id, PROPERTYS propertys)const;
	};
	class Relationship
	{
	public:
		class Relation
		{
		public:
			Relation(int id_1, string infomation, int id_2)
			{
				node1_id = id_1;
				node2_id = id_2;
				info = infomation;
			}
		private:
			int node1_id;
			int node2_id;
			string info;
		};
		int getRelationCount()const;
		RELATIONS getRelationBetwenNodes(int Node1_id,int Node2_id)const;
		void findShortestPathBetweemTwoNodes(int Node1_id, int Node2_id)const;
		std::vector<int> getRelatedNodes(int Node_id)const;
		void addRelation(Relation relation)const;

	};



};

#endif