//UMBC - CSEE - CMSC 341 - Fall 2021 - Proj1
#include "graph.h"
Graph::Graph(){
  m_head = nullptr;
  m_dataFile = "data.txt";
  m_numNodes = 0;    
}

Graph::Graph(string dataFile){
  m_head = nullptr;
  m_numNodes = 0;
  m_dataFile = dataFile;
  loadData();
}

Graph::~Graph(){
  clearResult();
  clearVisited();
  clearGraph();    
}

void Graph::loadData(){
  int numNodes;
  int node, n, e, s, w; 
  ifstream dataFile;
  dataFile.open(m_dataFile);
  if (dataFile.is_open()) {
    dataFile >> numNodes;
    m_numNodes = numNodes;
    for (int i = 0; i < numNodes; i++) {
      dataFile >> node >> n >> e >> s >> w;
      insert(node, n, e, s, w);
    }
  }
  else
    //the following statement provides the reason if a file doesn't open
    //please note: not all platforms are providing the same message
    cerr << "Error: " << strerror(errno) << endl;
}

void Graph::insert(int node, int n, int e, int s, int w){
  if (findNode(node) == nullptr){ //if it is a new node
    Node * newNode = new Node(node); //creates new node
    insertAtHead(newNode); //inserts int list
    if (n != -1){ //if there is something to the north
      if (findNode(n) == nullptr){//if the node does not exist
	Node * north = new Node(n);
	findNode(node)->setNorth(north); 
	insertAtHead(north); 
      }else{ //if node already exists
	findNode(node)->setNorth(findNode(n));
      }
    }else{//if node already exists
      findNode(node)->setNorth(nullptr);
    }
    if (e != -1){ //same as the north segment above
      if (findNode(e) == nullptr){
	Node * east = new Node(e); //creates a new node
	findNode(node)->setEast(east); //sets east value
	insertAtHead(east);  //inserts into list
      }else{ //if node already exists
	findNode(node)->setEast(findNode(e)); //set the value
      }
    }else{ //if there is nothing to east
      findNode(node)->setEast(nullptr); //set as nullptr
    }
    if (s != -1){
      if (findNode(s) == nullptr){
	Node * south = new Node(s);
	findNode(node)->setSouth(south);
	insertAtHead(south);
      }else{
	findNode(node)->setSouth(findNode(s));
      }
    }else{
      findNode(node)->setSouth(nullptr);
    }
    if (w != -1){
      if (findNode(w) == nullptr){
	Node * west = new Node(w);
	findNode(node)->setWest(west);
	insertAtHead(west);
      }else{
	findNode(node)->setWest(findNode(w));
      }
    }else{
      findNode(node)->setWest(nullptr);
    }
    
  }else{ //if node already exists
    
    if (n != -1){ //if there is something to the north
      if (findNode(n) == nullptr){ //and it doesn't exist yet
	Node * north = new Node(n); //creates a new node
	findNode(node)->setNorth(north); //sets value
	insertAtHead(north); //inserts into list
      }else{ //if it already exists
	findNode(node)->setNorth(findNode(n)); //sets the value
      }
    }else{ //if there is nothing to the north
      findNode(node)->setNorth(nullptr); //set to null
    }
    
    if (e != -1) { //same as north
      if (findNode(e) == nullptr){ //if it does exist
	Node * east = new Node(e);
	findNode(node)->setEast(east);
	insertAtHead(east); //create new node and insert
      }else{ //otherwise set value
	findNode(node)->setEast(findNode(e));
      }
    }else{ //otherwise set to null 
      findNode(node)->setEast(nullptr);
    }
    
    if (s != -1){ //checks for south
      if (findNode(s) == nullptr){
	Node * south = new Node(s);
	findNode(node)->setSouth(south);
	insertAtHead(south);
      }else{
	findNode(node)->setSouth(findNode(s));
      }
    }else{
      findNode(node)->setSouth(nullptr);
    }
    
    if (w != -1){ //checls for west
      if (findNode(w) == nullptr){
	Node * west = new Node(w);
	findNode(node)->setWest(west);
	insertAtHead(west);
      }else{
	findNode(node)->setWest(findNode(w));
      }
    }else{
      findNode(node)->setWest(nullptr);
    }
  }
  
}

void Graph::insertAtHead(Node * aNode){
  if (m_numNodes != 0){ //if it is not the first node
    aNode->m_next = m_head; //set the next value to current head
    m_head = aNode; //and set head to the new node
  }else{ //if it is first node
    m_head = aNode; //sets head
  }
}

Node * Graph::findNode(int nodeValue){
  Node * curr = m_head; 
  while (curr != nullptr){ //checks through the list
    if (curr->m_value == nodeValue) //if there is a match
      return curr; //return address 
    curr = curr->m_next; 
  }
  return nullptr;   //if node not found
}

bool Graph::findPath(int start, int end){
  clearVisited(); //resets visited values to false
  clearResult(); //clears stack
  if ((!findNode(end)) || (!findNode(start))) { //if node is not in tree
    return false; 
  }
  findPath(findNode(start), end); //starts search    
}

bool Graph::findPath(Node* aNode, int end){
  if (aNode->getValue() == end) { //When you reach the end
    m_path.push(aNode->getValue()); //adds the destination to stack
    return true;
  }
  if((!aNode->getNorth()) && (!aNode->getEast()) && (!aNode->getSouth()) && (!aNode->getWest())){ //if node is dead end
    return false;
  }
  if (aNode->getVisited()) { //if node is already visited
    return false;
  }
  aNode->setVisited(true); //sets node to visited
  m_path.push(aNode->getValue()); //adds to stack
  //this segment checks all directions and calls recursively
  if (aNode->getNorth()) { 
    findPath(findNode(aNode->getNorth()->getValue()), end);
  }
  if (aNode->getEast()) {
    findPath(findNode(aNode->getEast()->getValue()), end);
  }
  if (aNode->getSouth()) {
    findPath(findNode(aNode->getSouth()->getValue()), end);
  }
  if (aNode->getWest()) {
    findPath(findNode(aNode->getWest()->getValue()), end);
  }
  
}

void Graph::dump(){
  stack<int> temp = m_path; //makes temp stack
  clearResult(); //erases m_path so it can be reversed
  while (!temp.empty()){ //populates m_path again
    int x = temp.top(); 
    m_path.push(x); //in reverse order
    temp.pop();
  }
  temp = m_path; //sets the empty stack to m_head
  while (!temp.empty()){ //iterates and print list
    int y = temp.top();
    cout << y << "=>";
    temp.pop();
  }
  cout << "END" << endl;
}

void Graph::clearResult(){
  while(!m_path.empty()){ //while stack is not empty
    m_path.pop(); //removes top value
  }   
}

void Graph::clearVisited(){
  Node * curr = m_head; 
  while(curr){ //iterates through linked list
    curr->setVisited(false); //clears visited
    curr = curr->m_next; 
  }   
}

void Graph::buildGraph(string file){
  clearGraph(); 
  clearResult();
  clearVisited();
  m_dataFile = file;
  loadData();   //builds a new graph object
}

void Graph::clearGraph(){
  while(m_head){ //iterate through linked list
    Node * temp = m_head->m_next;
    delete m_head; 
    m_head = nullptr; //deallocates memory
    m_head = temp; 
  }
  m_numNodes = 0;
}

const Graph & Graph::operator=(const Graph & rhs) {
  if (this != &rhs) { //prevents self assignment
    clearVisited();
    clearResult();
    clearGraph();
    m_dataFile = rhs.m_dataFile;
    m_numNodes = rhs.m_numNodes;
    
    Node *curr = rhs.m_head;
    while (curr) {
      int node = curr->getValue();
      int n = -1, e = -1, s = -1, w = -1;
      if(curr->getNorth())
	n = curr->getNorth()->getValue();
      if(curr->getEast())
	e = curr->getEast()->getValue();
      if(curr->getSouth())
	s = curr->getSouth()->getValue();
      if(curr->getWest())
	w = curr->getWest()->getValue();
      insert(node, n,e,s,w);
      curr = curr->getNext();
    }
    
  }
  
  return *this;
  
}

bool Graph::empty() const		// is the list empty?
{ return m_head == nullptr; }
