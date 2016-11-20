//
// Created by HANG JIANG on 13/09/2016.
//

#include "Graph.h"

int main(){

    /****************************** TEST 1 (PASS) ****************************/
//    // create 3 graphs
//    gdwg::Graph<int,int> g;
//    gdwg::Graph<std::string,double> g2{};
//    gdwg::Graph<std::shared_ptr<int>,std::string> g3{};
//
//    // add some nodes to each graph.
//    g.addNode(1);
//    int i = 2;
//    g.addNode(i);
//    double d = 3.41;
//    g.addNode(static_cast<int>(d));
//
//    std::string s = "world";
//    g2.addNode(s);
//    g2.addNode("Hello");
//
//    std::shared_ptr<int> sp = std::make_shared<int>(5);
//    g3.addNode(sp);
//    g3.addNode(std::make_shared<int>(6));
//
//    // print the nodes from each graph.
//    std::cout << "Graph g nodes:" << std::endl;
//    g.printNodes();
//    std::cout << "Graph g2 nodes:" << std::endl;
//    g2.printNodes();
//    std::cout << "isNode test:" << std::endl;
//    std::cout << std::boolalpha << g3.isNode(sp) << std::endl;
    /****************************** TEST 1 (PASS) ****************************/




    /****************************** TEST 2 ****************************/
//    // create 3 graphs
//    gdwg::Graph<int,int> g;
//    gdwg::Graph<std::string,double> g2{};
//    gdwg::Graph<std::shared_ptr<int>,std::string> g3{};
//
//    // add some nodes to each graph.
//    g.addNode(1);
//    int i = 2;
//    g.addNode(i);
//    double d = 3.41;
//    g.addNode(static_cast<int>(d));
//
//    g2.addNode("Hello");
//    std::string s = "world";
//    g2.addNode(s);
//
//    std::shared_ptr<int> sp = std::make_shared<int>(5);
//    g3.addNode(sp);
//    g3.addNode(std::make_shared<int>(6));
//
//    // add some edges
//    g.addEdge(2,1,3);
//    int j = 3;
//    g.addEdge(i,j,1);
//
//    g2.addEdge("Hello","world",d);
//
//    g.printEdges(2);
//    g2.printEdges("Hello");
//    g2.printEdges("world");
//
//    std::cout << "Printing nodes in graph g to check print order" << std::endl;
//    g.printNodes();
    /****************************** TEST 2 ****************************/






    /****************************** TEST 3 ****************************/
//    // create 3 graphs
//    gdwg::Graph<int,int> g;
//    gdwg::Graph<std::string,double> g2{};
//    gdwg::Graph<std::shared_ptr<int>,std::string> g3{};
//
//    // add some nodes to each graph.
//    g.addNode(1);
//    int i = 2;
//    g.addNode(i);
//    double d = 3.41;
//    g.addNode(static_cast<int>(d));
//
//    g2.addNode("Hello");
//    std::string s = "world";
//    g2.addNode(s);
//
//    std::shared_ptr<int> sp = std::make_shared<int>(5);
//    g3.addNode(sp);
//    g3.addNode(std::make_shared<int>(6));
//
//    // try to add some duplicated data
//    i = 1;
//    std::cout << "testing adding duplicate data" << std::endl;
//    std::cout << std::boolalpha << g.addNode(i) << std::endl;
//    std::cout << g2.addNode("Hello") << std::endl;
//    std::cout << g3.addNode(sp) << " " << g3.addNode(std::make_shared<int>(6)) << std::endl;
//
//    // add some edges
//    g.addEdge(2,1,3);
//    int j = 3;
//    g.addEdge(i,j,1);
//    g2.addEdge("Hello","world",d);
//
//    std::cout << "testing adding duplicate edges" << std::endl;
//    // try to add some duplicated edges
//    std::cout << g.addEdge(2,1,3) << std::endl;
//    // try to add an edge with a different weight
//    std::cout << g.addEdge(2,1,2) << std::endl;
//
//    std::cout << "testing adding edges between nodes not in the graph" << std::endl;
//    // try to add an edge to somewhere not in the graph
//    try {
//        g.addEdge(7,1,3);
//    } catch( const std::exception &ex ) {
//        //std::cerr << ex.what() << std::endl;
//        std::cout << "exception caught" << std::endl;
//    }
//    try {
//        g.addEdge(2,7,3);
//    } catch( const std::exception &ex ) {
//        std::cout << "exception caught" << std::endl;
//    }
//
//    std::cout << "testing isConnected" << std::endl;
//    try {
//        std::cout << g2.isConnected("world","Hello") << std::endl;
//        std::cout << g2.isConnected("hello","pluto") << std::endl;
//    } catch( const std::exception &ex ) {
//        std::cout << "exception caught" << std::endl;
//    }
//
//    std::cout << "testing print with an unknown node" << std::endl;
//    try {
//        g.printEdges(5);
//    } catch( const std::exception &ex ) {
//        std::cout << "exception caught" << std::endl;
//    }
    /****************************** TEST 3 ****************************/






    /****************************** TEST 4 ****************************/
//    gdwg::Graph<std::string,int> gCopy;
//
//    // create some data to store as nodes.
//    std::string s = "a";
//    std::string t = "b";
//    std::string u = "c";
//
//    // add this data into the graph
//    gCopy.addNode(s);
//    gCopy.addNode(t);
//    gCopy.addNode(u);
//
//    gCopy.addEdge(u,t,1);
//    gCopy.addEdge(u,t,2);
//
//    std::cout << "Graph g before attempted change" << std::endl;
//    gCopy.printNodes();
//    // change the value of t and make sure that the graph still prints out the original value
//    t = "d";
//    std::cout << "Graph g after attempted change" << std::endl;
//    gCopy.printNodes();
//
//    gdwg::Graph<std::shared_ptr<std::string>,std::shared_ptr<int>> gPtr;
//    std::shared_ptr<std::string> sPtr = std::make_shared<std::string>("a");
//    std::shared_ptr<std::string> tPtr = std::make_shared<std::string>("b");
//    std::shared_ptr<std::string> uPtr = std::make_shared<std::string>("c");
//    gPtr.addNode(sPtr);
//    gPtr.addNode(tPtr);
//    gPtr.addNode(uPtr);
//
//    // add an edge between u and t
//    gPtr.addEdge(uPtr,tPtr,std::make_shared<int>(1));
//    // add a second edge between u and t with a different weight
//    gPtr.addEdge(uPtr,tPtr,std::make_shared<int>(2));
//
//    // change the value of the data in the ptr
//    *tPtr = "d";
//
//    std::cout << "Confirming that data has changed if we are using ptrs" << std::endl;
//    // this should have updated in the graph as well as it is a pointer.
//    // can confirm this using isNode
//    std::cout << std::boolalpha << gCopy.isNode(t) << " " << gPtr.isNode(tPtr) << std::endl;
    /****************************** TEST 4 ****************************/







    /****************************** TEST 5 ****************************/
//    gdwg::Graph<std::string,int> gCopy;
//
//    // create some data to store as nodes.
//    std::string s = "a";
//    std::string t = "b";
//    std::string u = "c";
//
//    // add this data into the graph
//    gCopy.addNode(s);
//    gCopy.addNode(t);
//    gCopy.addNode(u);
//
//    gCopy.addEdge(u,t,1);
//    gCopy.addEdge(u,t,2);
//
//    std::cout << "Graph before node replacement" << std::endl;
//    gCopy.printNodes();
//
//    // replace node
//    gCopy.replace("a","e");
//    std::cout << "Graph after node replacement" << std::endl;
//    gCopy.printNodes();
//
//    std::cout << "trying to replace node with an existing node" << std::endl;
//    std::cout << std::boolalpha << gCopy.replace("b","c") << std::endl;
//
//    std::cout << "trying to replace node with a node not in the graph" << std::endl;
//    try {
//        gCopy.replace("a","d");
//    } catch( const std::exception &ex ) {
//        //std::cerr << ex.what() << std::endl;
//        std::cout << "exception caught" << std::endl;
//    }
    /****************************** TEST 5 ****************************/





    /****************************** TEST 6 ****************************/
//    // make a graph
//    gdwg::Graph<unsigned int,std::string> g;
//
//    g.addNode(1);
//    g.addNode(2);
//    g.addNode(3);
//    g.addNode(4);
//
//    g.addEdge(1,2,"1->2");
//    g.addEdge(2,3,"2->3");
//    g.addEdge(2,4,"2->4");
//    g.addEdge(3,2,"3->2");
//    g.addEdge(3,4,"3->4");
//    g.addEdge(2,4,"cs6771");
//    g.addEdge(3,4,"cs6771");
//
//    std::cout << "Before calling mergReplace(2,3)" << std::endl;
//    g.printEdges(1);
//    g.printEdges(2);
//    g.printEdges(3);
//    g.printEdges(4);
//
//    g.mergeReplace(2,3);
//
//    std::cout << std::endl << "After calling mergReplace(2,3)" << std::endl;
//    g.printEdges(1);
//    std::cout << "checking that node 2 has been destroyed" << std::endl;
//    try {
//        g.printEdges(2);
//    } catch( const std::exception &ex ) {
//        std::cout << "exception caught" << std::endl;
//    }
//    g.printEdges(3);
//    g.printEdges(4);
    /****************************** TEST 6 ****************************/






    /****************************** TEST 7 ****************************/
//    // make a graph
//    gdwg::Graph<unsigned int,std::string> g;
//
//    g.addNode(1);
//    g.addNode(2);
//    g.addNode(3);
//    g.addNode(4);
//
//    g.addEdge(1,2,"1->2");
//    g.addEdge(2,3,"2->3");
//    g.addEdge(2,4,"2->4");
//    g.addEdge(3,2,"3->2");
//    g.addEdge(3,4,"3->4");
//    g.addEdge(2,4,"cs6771");
//    g.addEdge(3,4,"cs6771");
//
//    std::cout << "Before calling mergReplace(2,3)" << std::endl;
//    g.printEdges(1);
//    g.printEdges(2);
//    g.printEdges(3);
//    g.printEdges(4);
//
//    g.mergeReplace(2,3);
//
//    std::cout << std::endl << "After calling mergReplace(2,3)" << std::endl;
//    g.printEdges(1);
//    std::cout << "checking that node 2 has been destroyed" << std::endl;
//    try {
//        g.printEdges(2);
//    } catch( const std::exception &ex ) {
//        std::cout << "exception caught" << std::endl;
//    }
//    g.printEdges(3);
//    g.printEdges(4);
    /****************************** TEST 7 ****************************/





    /****************************** TEST 8c ****************************/
//    auto gHeap = new gdwg::Graph<std::string,int>{};
//
//    // add this data into the graph
//    gHeap->addNode("a");
//    gHeap->addNode("b");
//    gHeap->addNode("c");
//    gHeap->addNode("d");
//
//    gHeap->addEdge("b","a",3);
//    gHeap->addEdge("b","a",5);
//    gHeap->addEdge("b","d",4);
//    gHeap->addEdge("c","a",3);
//
//    std::cout << "original graph" << std::endl;
//    gHeap->printNodes();
//    gHeap->printEdges("b");
//
//    auto gHeapCopy = *gHeap;
//    gHeap->deleteNode("a");
//    std::cout << "original graph after delete" << std::endl;
//    gHeap->printNodes();
//    gHeap->printEdges("b");
//    std::cout << "copied graph after delete in other graph" << std::endl;
//    gHeapCopy.printNodes();
//    gHeapCopy.printEdges("b");
//
//    delete gHeap;
//    std::cout << "copied graph after other graph is deleted" << std::endl;
//    gHeapCopy.printNodes();
    /****************************** TEST 8c ****************************/





    /****************************** TEST 8m ****************************/
//    auto gHeap = new gdwg::Graph<std::string,int>{};
//
//    // add this data into the graph
//    gHeap->addNode("a");
//    gHeap->addNode("b");
//    gHeap->addNode("c");
//    gHeap->addNode("d");
//
//    gHeap->addEdge("b","a",3);
//    gHeap->addEdge("b","a",5);
//    gHeap->addEdge("b","d",4);
//    gHeap->addEdge("c","a",3);
//
//    std::cout << "original graph" << std::endl;
//    gHeap->printNodes();
//    gHeap->printEdges("b");
//
//    auto gHeapCopy = std::move(*gHeap);
//    // We shouldn't use a moved-from object, in general.
//    // However, here, for testing purposes, we assumed
//    // a moved-from graph is an empty graph.
//    std::cout << "moved-from graph (expected to be empty)" << std::endl;
//    gHeap->printNodes();
////    delete gHeap;
//
//    std::cout << "moved-to graph" << std::endl;
//    gHeapCopy.printNodes();
//    gHeapCopy.printEdges("b");
    /****************************** TEST 8m ****************************/






    /****************************** TEST 9c ****************************/
//    auto gHeap = new gdwg::Graph<std::string,int>{};
//
//    // add this data into the graph
//    gHeap->addNode("a");
//    gHeap->addNode("b");
//    gHeap->addNode("c");
//    gHeap->addNode("d");
//
//    gHeap->addEdge("b","a",3);
//    gHeap->addEdge("b","a",5);
//    gHeap->addEdge("c","a",3);
//
//    std::cout << "original graph" << std::endl;
//    gHeap->printNodes();
//    gHeap->printEdges("b");
//
//    gdwg::Graph<std::string,int> gHeapCopy;
//    gHeapCopy.addNode("z");
//    std::cout << "Graph before copy assignment" << std::endl;
//    gHeapCopy.printNodes();
//
//    gHeapCopy = *gHeap;	// copy assignment
//    gHeap->deleteNode("a");
//    std::cout << "original graph after delete" << std::endl;
//    gHeap->printNodes();
//    gHeap->printEdges("b");
//    std::cout << "copied graph after delete in other graph" << std::endl;
//    gHeapCopy.printNodes();
//    gHeapCopy.printEdges("b");
//
//    delete gHeap;
//    std::cout << "copied graph after other graph is deleted" << std::endl;
//    gHeapCopy.printNodes();
    /****************************** TEST 9c ****************************/







    /****************************** TEST 9m ****************************/
//    auto gHeap = new gdwg::Graph<std::string,int>{};
//
//    // add this data into the graph
//    gHeap->addNode("a");
//    gHeap->addNode("b");
//    gHeap->addNode("c");
//    gHeap->addNode("d");
//
//    gHeap->addEdge("b","a",3);
//    gHeap->addEdge("b","a",5);
//    gHeap->addEdge("c","a",3);
//
//    std::cout << "original graph" << std::endl;
//    gHeap->printNodes();
//    gHeap->printEdges("b");
//
//    gdwg::Graph<std::string,int> gHeapCopy;
//    gHeapCopy.addNode("z");
//    std::cout << "Graph before copy assignment" << std::endl;
//    gHeapCopy.printNodes();
//
//    gHeapCopy = std::move(*gHeap);	// move assignment
//
//    // We shouldn't use a moved-from object, in general.
//    // However, here, for testing purposes, we assumed
//    // a moved-from graph is an empty graph.
//    std::cout << "moved-from graph (expected to be empty)" << std::endl;
//    gHeap->printNodes();
//    delete gHeap;
//
//    std::cout << "moved-to graph" << std::endl;
//    gHeapCopy.printNodes();
//    gHeapCopy.printEdges("b");
    /****************************** TEST 9m ****************************/






    /****************************** TEST 10 ****************************/
//    gdwg::Graph<std::string,int> gCopy;
//
//    // create some data to store as nodes.
//    std::string s = "a";
//    std::string t = "b";
//    std::string u = "c";
//
//    // add this data into the graph
//    gCopy.addNode(s);
//    gCopy.addNode(t);
//    gCopy.addNode(u);
//
//    gCopy.addEdge(u,t,1);
//    gCopy.addEdge(u,t,2);
//
//    const auto& constGraph = gCopy;
//
//    std::cout << std::boolalpha << constGraph.isNode("a") << std::endl;
//    std::cout << std::boolalpha << constGraph.isConnected("a","b") << std::endl;
//    std::cout << std::boolalpha << constGraph.isConnected("c","b") << std::endl;
//
//    std::cout << "Const graph: " << std::endl;
//    constGraph.printNodes();
    /****************************** TEST 10 ****************************/







    /****************************** TEST 11 ****************************/
//    // make a graph
//    gdwg::Graph<unsigned int,std::string> g;
//
//    g.addNode(1);
//    g.addNode(2);
//    g.addNode(3);
//    g.addNode(4);
//
//    g.addEdge(1,2,"1->2");
//    g.addEdge(2,3,"2->3");
//    g.addEdge(2,4,"2->4");
//    g.addEdge(3,2,"3->2");
//    g.addEdge(3,4,"3->4");
//    g.addEdge(2,4,"cs6771");
//    g.addEdge(3,4,"cs6771");
//
//    std::cout << "Before calling mergReplace(2,3)" << std::endl;
//    g.printEdges(1);
//    g.printEdges(2);
//    g.printEdges(3);
//
//    g.mergeReplace(2,3);
//
//    std::cout << "After calling mergReplace(2,3)" << std::endl;
//    g.printEdges(1);
//    std::cout << "checking that node 2 has been destroyed" << std::endl;
//    try {
//        g.printEdges(2);
//    } catch( const std::exception &ex ) {
//        std::cout << "exception caught" << std::endl;
//    }
//    g.printEdges(3);
    /****************************** TEST 11 ****************************/





    /****************************** TEST 12 ****************************/
//    // make a graph
//    gdwg::Graph<unsigned int,int> g;
//
//    g.addNode(1);
//    g.addNode(2);
//    g.addNode(3);
//    g.addNode(4);
//
//    g.addEdge(1,2,12);
//    g.addEdge(1,3,13);
//    g.addEdge(1,4,14);
//    g.addEdge(2,1,21);
//    g.addEdge(2,3,23);
//    g.addEdge(3,1,31);
//    g.addEdge(3,4,34);
//
//    g.printNodes();
    /****************************** TEST 12 ****************************/






    /****************************** TEST 13 ****************************/
//    // make a graph
//    gdwg::Graph<unsigned int,int> g;
//
//    g.addNode(1);
//    g.addNode(2);
//    g.addNode(3);
//    g.addNode(4);
//
//    g.addEdge(1,2,12);
//    g.addEdge(1,3,13);
//    g.addEdge(1,4,14);
//    g.addEdge(2,1,21);
//    g.addEdge(2,3,23);
//    g.addEdge(3,1,31);
//    g.addEdge(3,4,34);
//
//    for (g.begin(); !g.end(); g.next())
//        std::cout << g.value() << std::endl;
//
//    const auto& cg = g;
//
//    for (cg.begin(); !cg.end(); cg.next())
//        std::cout << cg.value() << std::endl;
    /****************************** TEST 13 ****************************/






    return 0;
}
