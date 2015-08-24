# -*- coding: utf-8 -*-
import json as simplejson
from py2neo import Graph,neo4j,Node,Relationship
#global INDEX
INDEX = None

def connect(username, password):
     url = 'http://localhost:7474'
     neo4j.authenticate(url.strip('http://'), username, password)
     NeoGraph= Graph(url + '/db/data/')
     if NeoGraph is None:
         print "unconnect"
         return 0
     else:
         print "connected  with neo4j"
         return NeoGraph

def getNodeCount(NeoGraph): 
    return NeoGraph.order

def getAllNodes(neoGraph):
    allNodes = []
    cyoherQuery = "MATCH (n) RETURN n"
    result =  neoGraph.cypher.execute(cyoherQuery)
    for node in result:
        allNodes.append(str(node))
    return allNodes

def addNode(neoGraph,jsonNode):
    respCmtJson = jsonNode.replace("'", "\"");
    # turn string to json
    js = simplejson.loads(respCmtJson)
    # lable  and key_values
    labels = []
    key_values = {}
    #put ID into the dict
    key_values['ID'] = js['ID']
    keyValues = js['AVP_LIST']
    # for all key_values in the AVP_LIST
    for keyValue in keyValues:
    # if ATTRIBUTE is category then put the value into label
        if keyValue['ATTRIBUTE'] == 'entity_category':
            labels = keyValue['VALUE'].split(',')
            labels = tuple(labels)
        else:
            key_values[keyValue['ATTRIBUTE']] = keyValue['VALUE']
    # labels is tuple  and key_values is a dict
    node = Node()
    neoGraph.create(node)
    node.__init__(*labels,**key_values)
    node.push() 
    #createIndexofNode(node)
    #autoBuildRelationShip(node) 
 
def addMultiNodesFromJsonFile(neoGraph,filename):
    file = open(filename)
# for all lines in the file
    while 1:
        line = file.readline()
        if not line:
            break
        # replace '' with ""
        respCmtJson = line.replace("'", "\"");
        # ture string to json
        js = simplejson.loads(respCmtJson)
        # lable  and key_values
        labels = []
        key_values = {}
        #put ID into the dict
        key_values['ID'] = js['ID']
        keyValues = js['AVP_LIST']
        # for all key_values in the AVP_LIST
        for keyValue in keyValues:
            # if ATTRIBUTE is category then put the value into label
              if keyValue['ATTRIBUTE'] == 'entity_category':
                  labels = keyValue['VALUE'].split(',')
                  labels = tuple(labels)
                  #print len(labels)
              else:
                  key_values[keyValue['ATTRIBUTE']] = keyValue['VALUE']
        # labels is tuple  and key_values is a dict
        # use with which can create a node
        node = Node()
        neoGraph.create(node)
        node.__init__(*labels,**key_values)
        node.push() 
        createIndexofNode(neoGraph,node)
        autoBuildRelationShip(neoGraph,node)  
        
def addLabel(neoGraph,node_id,newLabel):
    node = neoGraph.node(node_id)
    node.labels.add(newLabel)
    node.push()
    
def addLabels(neoGraph,node_id ,LabelTuple):
    node = neoGraph.node(node_id)
    label = tuple(node.labels)
    properties = node.properties
    newLabels = label + LabelTuple
    node.__init__(*newLabels , **properties)
    node.push()    

def addProperty(neoGraph,node_id,key,value):

    node = neoGraph.node(node_id)
    node.properties[key] = value
    node.push() 

def addProperties(neoGraph,node_id,dic_key_value):

    node =  neoGraph.node(node_id)
    # get the origin labels
    label = node.labels
    prope = node.properties
    # merge the origin properties and the new ones
    properties = dict(prope.items()+dic_key_value.items())
    node.__init__(*label,**properties)
    node.push()
    
def delete(neoGraph,id):
    n = neoGraph.node(id)
    delete_string1 = """START begining = node(%d) 
                      MATCH begining-[r]-() 
                      delete r""" %(id)
    delete_string2 = """START begining = node(%d) 
                      MATCH ()-[r]-begining 
                      delete r""" %(id)
    neoGraph.cypher.execute(delete_string1)
    neoGraph.cypher.execute(delete_string2)
    n.delete()
    
def deleteAll(neoGraph):
    
    neoGraph.cypher.execute("MATCH ()-[r]-()  DELETE r")
    neoGraph.cypher.execute("MATCH n DELETE n")
    
def getOrCreatIndex(neoGraph):
    global  INDEX
    
    INDEX = neoGraph.legacy.get_or_create_index(neo4j.Node, "node")
    #return INDEX
     
def createIndexofNode(neoGraph, node):
    global  INDEX
    if INDEX is None:
        getOrCreatIndex(neoGraph)
    
    labels = ()
    keyValues = {}
    label = node.labels
    keyValues = node.properties
    for label in labels:
        INDEX.add("label",label,node)
    for (key,value) in keyValues.items():
        INDEX.add("properties",value,node)
        
# StaticMethods of Neo4j for RelationShips
##
def getRelationCount(neoGraph):

     return neoGraph.size
     
def getRelatedNodes(neoGraph,id):

    relatedNodes = []                       #relatedNodes = set()
    
    get_string =  """START begining = node(%d) 
                      MATCH begining-[]-(n) 
                      RETURN n""" %(id)
                      
    result = neoGraph.cypher.execute(get_string)     
       
    for record in result:
        relatedNodes.append(record.n._id)   #relatedNodes.add(record.n._id)
    
    return relatedNodes
  


def getRelationBetwenNodes(neoGraph,node1_id ,node2_id):
   Result = []
   query_string = """START node1 = node(%d) ,node2 = node(%d)
                      MATCH node1-[r]-node2 
                      RETURN r""" %(node1_id, node2_id)
   result = neoGraph.cypher.execute(query_string)   
   for record in result:
       tepTuple = (record.r.start_node._id,str(record.r.rel),record.r.end_node._id)
       Result.append(tepTuple)
   return Result
       
def autoBuildRelationShip(neoGraph,node):
    
    global INDEX
    if INDEX is None:
        getOrCreatIndex(neoGraph)
    
    labels = node.labels
    keyValues = node.properties  
    
    for label in labels:
        labelCrossNodes = INDEX.get("label",label)
        for crossNode in labelCrossNodes:
            Relationship_labelCross = neoGraph.match_one(start_node= node,rel_type="lableCross",end_node=crossNode)
            if crossNode != node:            
                if Relationship_labelCross:
                    labes = Relationship_labelCross["label"]
                    labes = labes +","+label
                    Relationship_labelCross["label"] = labes
                    Relationship_labelCross.push()
                else:
                    otherRelationship = neoGraph.match_one(start_node= crossNode,rel_type="lableCross",end_node=node)
                    if otherRelationship:
                        labes = otherRelationship["label"]
                        labes = labes +","+label
                        otherRelationship["label"] = labes
                        otherRelationship.push()    
                    else:    
                        LableCross = Relationship(node,"lableCross",crossNode,label =label )
                        neoGraph.create(LableCross)
     
    for (key,value) in keyValues.items():
        propertyCrossNodes = INDEX.get("properties",value)
        for propertyCrossnode in propertyCrossNodes:
            Relationship_propertyCross = neoGraph.match_one(start_node= node,rel_type="propertyCross",end_node=propertyCrossnode)
            if propertyCrossnode != node:
                if Relationship_propertyCross:
                    Relationship_propertyCross[key] = value
                    Relationship_propertyCross.push()
                else:
                    other_propertyCross = neoGraph.match_one(start_node= propertyCrossnode,rel_type="propertyCross",end_node=node)
                    if  other_propertyCross:
                        other_propertyCross[key]=value
                        other_propertyCross.push()
                    else:
                        propertyCross = Relationship(node,"propertyCross",propertyCrossnode)
                        propertyCross[key] = value
                        neoGraph.create(propertyCross)

def findShortestPathBetweenTwoNodes(neoGraph,node1_id, node2_id):
    
    query_string = """START begining = node(%d), end= node(%d) 
                      MATCH p = shortestPath(begining-[*..10]->end) 
                      RETURN p""" %(node1_id, node2_id)
    result =  neoGraph.cypher.execute(query_string)
    for res in result:                                 # res is a Record Object
       for relationship in res.p.relationships:        # relationships Tuple in this path
           endNode =  relationship.end_node
           startNode = relationship.start_node
           print startNode['name'] + str(relationship.properties) + endNode['name']
