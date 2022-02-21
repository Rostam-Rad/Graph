#include "graph.h"

class Tester{ // Tester class to implement test functions
public:
  bool testAltConstructor();
  bool testBuildEmptyGraph();
  bool testPaths();
  bool testAssignmentOperator();
};
int main(){
  cout << "Testing Alternate Constructor: ";
  Tester test1;
  if(test1.testAltConstructor()){
    cout << "TEST PASSED!"<< endl;
  }else{
    cout << "TEST FAILED!" << endl;
  }
  cout << "Testing Creating An Empty Graph Object: ";
  Tester test2;
  if(test2.testBuildEmptyGraph()){
    cout << "TEST PASSED!"<< endl;
  }else{
    cout << "TEST FAILED!" << endl;
  }
  Tester test3;
  test3.testPaths();
  cout << "Testing Assignment Operator: ";
  Tester test4;
  if(test4.testAssignmentOperator()){
    cout << "TEST PASSED!"<< endl;
  }else{
    cout << "TEST FAILED!" << endl;
  }

  return 0;
}

bool Tester::testAltConstructor() {
  Graph aGraph("testdata.txt");
  for (int i = 0; i < aGraph.m_numNodes; i++){
    if (!aGraph.findNode(i)){
      return false;
    }
  }
  return true;
}
bool Tester::testBuildEmptyGraph() {
  Graph aGraph;
  aGraph.buildGraph("testdata.txt");
  for (int i = 0; i < aGraph.m_numNodes; i++){
    if (!aGraph.findNode(i)){
      return false;
    }
  }
  return true;
}

bool Tester::testPaths() {
  int counter = 0;
  Graph aGraph("testdata.txt");
  cout << "Testing A Non-Existent Path In Graph: ";
  if (aGraph.findPath(0, 20)){
    cout << "TEST FAILED!" << endl;
  }else{
    cout << "TEST PASSED!" << endl;
    counter++;
  }
  cout << "Testing Path that exists: ";
  if (!aGraph.findPath(0,5)){
    cout << "TEST PASSED!" << endl;
    counter++;
  }else{
    cout << "TEST FAILED!" << endl;
  }
  cout << "Testing A Path To Itself: ";
  if (aGraph.findPath(10,10)){
    cout << "TEST PASSED!" << endl;
    counter++;
  }else{
    cout << "TEST FAILED!" << endl;
  }
  cout << "Testing A Path With Non-Existent Start Node: ";
  if (aGraph.findPath(20, 0)){
    cout << "TEST FAILED!" << endl;
  }else{
    cout << "TEST PASSED!" << endl;
    counter ++;
  }
  cout << "Testing A Path With Non-Existent End Node: ";
  if (aGraph.findPath(0, 20)){
    cout << "TEST FAILED!" << endl;
  }else{
        cout << "TEST PASSED!" << endl;
        counter++;
  }
  if(counter==5){
    return true;
  }else{
    return false;
  }
}

bool Tester::testAssignmentOperator() {
  Graph aGraph("testdata.txt");
  Graph bGraph("data.txt");
  aGraph = bGraph;
  if (aGraph.m_numNodes != bGraph.m_numNodes) {
    return false;
  }
  for (int i = 0; i < aGraph.m_numNodes; i++) {
    if (aGraph.findNode(i)->getValue() != bGraph.findNode(i)->getValue()) {
      return false;
    }
  }
  if (&aGraph == &bGraph) {
    return false;
  } else {
    return true;
  }
}
