//
// Created by Harry on 13/09/2016.
//

#ifndef COMP6771_ASS3_GRAPH_H
#define COMP6771_ASS3_GRAPH_H

#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <list>
#include <stdexcept>
#include <exception>
#include <algorithm>

// Bugs:
// 1. Test 6/Test 7, mergeReplace method

// Questions:
// 1. When move constructor or move assignment operator, make the share_ptr = null or should use reset()
// 2. Nested public/private, how they work ?
// 3. MergeReplace (What if the old node and new old are exactly the same node)
// 4. Do the delete operation (include reset()) would also release nested resources such as std::list<std::shared_ptr<Edge>> ?
// 5. The container method erase will also destroy its smart pointer element even includes its embedded node shared pointer ?
// 6. Hint: if you are using weak ptrs for edges you may be able to do this quite simply. How to interpret this ?
// 7. What if the value or weight passed in by user are pointers, do we need to recognise it and explicitly delete these stuff ?


namespace gdwg {

    template <typename N, typename E> class Graph {
    private:
        class Node;
        class Edge;

        class Node {
        public:
            Node(const N &n): data(n) { }
            Node(const N &n, std::list<std::shared_ptr<Edge>> &outgoing_edges):
                    data(n), outgoing_edges(outgoing_edges) { }

//        private:
            N data;
            std::list<std::shared_ptr<Edge>> outgoing_edges;
        };

        class Edge {
        public:
            Edge(std::shared_ptr<Node> src_node, std::shared_ptr<Node> dst_node, E weight): src_node(src_node), dst_node(dst_node), weight(weight) { }

//        private:
            E weight;
            std::shared_ptr<Node> src_node, dst_node;
        };

        std::vector<std::shared_ptr<Node>> nodes;
        mutable typename std::vector<std::shared_ptr<Node>>::const_iterator iter;	// use vector iterator as graph fake iterator

    public:
        // Constructor
        Graph();

        // Copy constructor:
        Graph(const Graph &graph);
        // Move constructor:
        Graph(Graph &&graph) noexcept;

        // Copy assignment operators
        Graph& operator=(const Graph &);
        // Move assignment operators
        Graph& operator=(Graph &&) noexcept;

        // Deconstructor
        ~Graph();


        // Adds a new node with value val to the graph. This function returns true if the node is added to the
        // graph and false if there is already a node containing val in the graph (with the graph unchanged).
        bool addNode(const N &val);


        // Adds a new edge src → dst with weight w. This function returns true if the edge is added and false
        // if the edge (with weight w) already exists in the graph. A std::runtime_error is thrown if either
        // src or dst is not in the graph.
        bool addEdge(const N& src, const N &dst, const E &w);


        // Replaces the original data, oldData, stored at this particular node by the replacement data, newData.
        // If no node that contains value oldData can be found, then a std::runtime_error is thrown. This function
        // returns false if a node that contains value newData already exists in the graph (with the graph unchanged)
        // and true otherwise.
        bool replace(const N &oldData, const N &newData);



        // Replaces the data, oldData, stored at one node, denoted OldNode, with the data, newData, stored at another
        // node, denoted NewNode, in the graph. If either node cannot be found in the graph, then a std::runtime_error
        // is thrown. After the operation has been performed successfully, every incoming (outgoing) edge of OldNode
        // becomes an incoming (outgoing) edge of newNode, except that duplicate edges must be removed. Note that the
        // edges that connect OldNode and NewNode are handled identically by this edge merging rule. See test6.cpp for
        // an example.
        void mergeReplace(const N &oldData, const N &newData);

        

        // Deletes a given node and all its associated incoming and outgoing edges. This function does nothing if
        // the node that is to be deleted does not exist in the graph. Hint: if you are using weak ptrs for edges
        // you may be able to do this quite simply. This function should not throw any exceptions.
        void deleteNode(const N &val) noexcept;
        // Deletes an edge from src to dst with weight w. No exceptions are thrown. This method would be called by
        // deleteNode, Not use deleteEdge because already know the node where the edge(s) should be deleted
        void _deleteEdge(std::shared_ptr<Node> &node, std::list<std::shared_ptr<Edge>> &list) noexcept;



        // Deletes an edge from src to dst with weight w, only if the edge exists in the graph. No exceptions are thrown
        void deleteEdge(const N &src, const N &dst, const E &w) noexcept;



        // Remove all nodes and edges from the graph. New nodes or edges can be added to the graph afterwards.
        void clear() noexcept;



        // Returns true if a node with value val exists in the graph and false otherwise.
        bool isNode(const N &val) const;



        // Returns true if src → dst exists in the graph and false otherwise. This function throws a
        // std::runtime_error if either src or dst is not in the graph.
        bool isConnected(const N &src, const N &dst) const;



        // Prints the data stored in all the nodes in the graph, with one node per line, starting from the node with
        // the smallest outdgree to the node with the largest. If two nodes have the same edge count, then the one
        // with the smaller node value determined by the < operator is printed first. See test11.cpp for an example.
        static bool nodeSortRule(const std::shared_ptr<Node> &node1, const std::shared_ptr<Node> &node2);
        void printNodes() const;



        // Prints the outgoing edges of a given node, SrcNode, containing value val. The first line must be "Edges
        // attached to Node X", where X is the data stored at SrcNode. Then, the outgoing edges of SrcNode are printed
        // in increasing order of their weights, with one edge per line adhering to the following format:
        // [the data at the destination node DstNode] [the cost of the edge]
        // For example, if SrcNode → DstNode has a weight 3 (of type int), where the data at DstNode is "abc"
        // (of type std::string), then the print out is "abc3". If SrcNode does not exist in the graph, then a
        // std::runtime_error is thrown with no output printed. If the outdegree of SrcNode is 0, then the first
        // line of the print should work and the second line should be "(null)". If two edges have the same weight,
        // then the edge whose destination node has a smaller node value, again determined by the < operator, is
        // printed first. See test12.cpp for an example.
        static bool edgeSortRule(const std::shared_ptr<Edge> &edge1, const std::shared_ptr<Edge> &edge2);
        void printEdges(const N &val) const;



        // Sets an internal iterator, i.e., ``pointer'' to the first element of a sequence.
        void begin() const;

        // Returns true if the iterator goes past the last element of the sequence and false otherwise.
        bool end() const;

        // Moves the iterator to the next element of the sequence.
        void next() const;

        // Returns the value of the node pointed to by the iterator.
        const N& value() const;
    };




    /***************************************************************************************/
    // Constructor
    template <typename N, typename E> Graph<N, E>::Graph():
            nodes(std::vector<std::shared_ptr<Node>>()), iter(nodes.begin()) { };

    // Copy constructor:
    template <typename N, typename E> Graph<N, E>::Graph(const Graph &graph){
        for( auto _nodePtr : graph.nodes ){
            std::list<std::shared_ptr<Edge>> edgePtrList;
            auto _edgePtrList = _nodePtr->outgoing_edges;
            for( auto _edgePtr : _edgePtrList ){
                std::shared_ptr<Node> srcNodePtr = std::make_shared<Node>(*_edgePtr->src_node);
                std::shared_ptr<Node> dstNodePtr = std::make_shared<Node>(*_edgePtr->dst_node);
                Edge edge(srcNodePtr, dstNodePtr, _edgePtr->weight);
                edgePtrList.emplace_back(std::make_shared<Edge>(edge));
            }
            Node node(_nodePtr->data, edgePtrList);
            this->nodes.push_back(std::make_shared<Node>(node));
        }
        iter = (this->nodes).begin();
    }

    // Move constructor:
    template <typename N, typename E> Graph<N, E>::Graph(Graph &&graph) noexcept{
        iter = graph.iter;
        nodes = graph.nodes;  // directly assign nodes
        for( auto _nodePtr : nodes ){
//            for( auto _edgePtr : _nodePtr->outgoing_edges ){
//                _edgePtr->src_node.reset();
//                _edgePtr->dst_node.reset();
//            }
            _nodePtr.reset();
        }
        graph.nodes.clear();
    }

    // Copy assignment operator
    template <typename N, typename E> Graph<N, E>& Graph<N, E>::operator=(const Graph &graph){
        for( auto _nodePtr : this->nodes ){
            for( auto _edgePtr : _nodePtr->outgoing_edges ){
                _edgePtr->src_node.reset();
                _edgePtr->dst_node.reset();
                _edgePtr.reset();
            }
            _nodePtr->outgoing_edges.clear();
            _nodePtr.reset();
        }
        this->nodes.clear();

        for( auto _nodePtr : graph.nodes ){
            std::list<std::shared_ptr<Edge>> edgePtrList;
            auto _edgePtrList = _nodePtr->outgoing_edges;
            for( auto _edgePtr : _edgePtrList ){
                std::shared_ptr<Node> srcNodePtr = std::make_shared<Node>(*_edgePtr->src_node);
                std::shared_ptr<Node> dstNodePtr = std::make_shared<Node>(*_edgePtr->dst_node);
                Edge edge(srcNodePtr, dstNodePtr, _edgePtr->weight);
                edgePtrList.emplace_back(std::make_shared<Edge>(edge));
            }
            Node node(_nodePtr->data, edgePtrList);
            this->nodes.push_back(std::make_shared<Node>(node));
        }
        iter = this->nodes.begin();
        return *this;
    }

    // Move assignment operator
    template <typename N, typename E> Graph<N, E>& Graph<N, E>::operator=(Graph &&graph) noexcept{
        if( this != &graph ){
            iter = graph.iter;
            nodes = graph.nodes;  // directly assign nodes
            for( auto _nodePtr : graph.nodes ){
//                for( auto _edgePtr : _nodePtr->outgoing_edges ){
//                    _edgePtr->src_node.reset();
//                    _edgePtr->dst_node.reset();
//                }
                _nodePtr.reset();
            }
            graph.nodes.clear();
        }
        return *this;
    }

    // Deconstructor ~Graph()
    template <typename N, typename E> Graph<N, E>::~Graph() {
        for( auto _nodePtr : nodes ){
            for( auto _edgePtr : _nodePtr->outgoing_edges ){
                _edgePtr->src_node.reset();
                _edgePtr->dst_node.reset();
            }
            _nodePtr.reset();
        }
        nodes.clear();

    }


    // Adds a new node with value val to the graph. This function returns true if the node is added to the
    // graph and false if there is already a node containing val in the graph (with the graph unchanged).
    template <typename N, typename E> bool Graph<N, E>::addNode(const N &val){
        for( auto _nodePtr : nodes ){
            if( _nodePtr->data == val ){
                return false;
            }
        }
        nodes.push_back( std::shared_ptr<Node>(new Node(val)) );
        return true;
    }


    // Adds a new edge src → dst with weight w. This function returns true if the edge is added and false
    // if the edge (with weight w) already exists in the graph. A std::runtime_error is thrown if either
    // src or dst is not in the graph.
    template <typename N, typename E> bool Graph<N, E>::addEdge(const N &src, const N &dst, const E &w){
        // 1: Find source node and dest node, throw exception if either one could not be found.
        // 2: Check whether the edge does already exists or not, return false if exists, otherwise true
        // 3: Really add the edge to the adjacent list if not exists.
        std::shared_ptr<Node> src_node = nullptr;
        std::shared_ptr<Node> dst_node = nullptr;
        for( auto node : nodes ){
            if( node->data == src ){
                src_node = node;
            }
            if( node->data == dst ){
                dst_node = node;
            }
        }
        if( src_node == nullptr || dst_node == nullptr ){
            throw std::runtime_error("The node does not exist !");
        }

        for( auto _edgePtr : src_node->outgoing_edges ){
            if( _edgePtr->dst_node->data == dst && _edgePtr->weight == w ){
                return false;
            }
        }

        src_node->outgoing_edges.insert( src_node->outgoing_edges.begin(), std::shared_ptr<Edge>(new Edge(src_node, dst_node, w)) );
        return true;
    };


    // Replaces the original data, oldData, stored at this particular node by the replacement data, newData.
    // If no node that contains value oldData can be found, then a std::runtime_error is thrown. This function
    // returns false if a node that contains value newData already exists in the graph (with the graph unchanged)
    // and true otherwise.
    template <typename N, typename E> bool Graph<N, E>::replace(const N &oldData, const N &newData){
        bool flagExistNewData = false;
        std::shared_ptr<Node> node = nullptr;

        for( auto _node : nodes ){
            if( _node->data == oldData ){
                node = _node;
            }
            if( _node->data == newData ){
                flagExistNewData = true;
            }
        }
        if( node == nullptr ){
            throw std::runtime_error("The node to be replaced could not be found !");
        }
        if( flagExistNewData == true ){
            return false;
        }

        node->data = newData;
        return true;
    };



    // Replaces the data, oldData, stored at one node, denoted OldNode, with the data, newData, stored at another
    // node, denoted NewNode, in the graph. If either node cannot be found in the graph, then a std::runtime_error
    // is thrown. After the operation has been performed successfully, every incoming (outgoing) edge of OldNode
    // becomes an incoming (outgoing) edge of newNode, except that duplicate edges must be removed. Note that the
    // edges that connect OldNode and NewNode are handled identically by this edge merging rule. See test6.cpp for
    // an example.
    template <typename N, typename E> void Graph<N, E>::mergeReplace(const N &oldData, const N &newData){
        // 1. Check whether either node does not exist, throw the exception if it is
        // 2. Change every outgoing edge of oldNode to be that of newNode as long as it is not duplicated
        // 3. Change every incomming edge of oldNode within other nodes to be that of new Node as long as it is not duplicated
        // 4. Destroy the old node
        std::shared_ptr<Node> oldNode = nullptr;
        std::shared_ptr<Node> newNode = nullptr;
        for( auto node : nodes ){
            if( node->data == oldData ){
                oldNode = node;
            }
            if( node->data == newData ){
                newNode = node;
            }
        }
        if( oldNode == nullptr || newNode == nullptr ){
            throw std::runtime_error("The node does not exist !");
        }
        if( oldData == newData ){  // If the two nodes are same, do nothing.
            return;
        }

        std::list<std::shared_ptr<Edge>> replacedList;
        for( auto old_edge : oldNode->outgoing_edges ){
            bool flagSameEdge = false;
            for( auto new_edge : newNode->outgoing_edges ){
                if( old_edge->dst_node == new_edge->dst_node && old_edge->weight == new_edge->weight ){
                    flagSameEdge = true;
                    break;
                }
            }
            if( flagSameEdge == false ){
                old_edge->src_node = newNode;
                replacedList.push_back(old_edge);
            }
        }
        newNode->outgoing_edges.insert( newNode->outgoing_edges.begin(), replacedList.begin(), replacedList.end() );

        for( auto node : nodes ){
            if( node != oldNode ){
                for( auto edge : node->outgoing_edges ){
                    if( edge->dst_node == oldNode ){
                        auto weightCompared = edge->weight;

                        auto iter = std::find_if(node->outgoing_edges.begin(), node->outgoing_edges.end(),
                            [newNode, weightCompared](const std::shared_ptr<Edge> &edge){
                                return (edge->dst_node == newNode && edge->weight == weightCompared); } );
                        if( iter == node->outgoing_edges.end() ){ // Does not find duplicated replaced edge
                            edge->dst_node = newNode;
                        } else {                                  // Find duplicated replaced edge need to remove it
                            node->outgoing_edges.remove(edge);
                        }
                    }
                }
            }
        }


//        for( auto edgePtr : oldNode->outgoing_edges ){
//            edgePtr->src_node.reset();
//            edgePtr->dst_node.reset();
//        }
        oldNode->outgoing_edges.clear();

        for( auto iter=nodes.begin(); iter != nodes.end(); iter++ ){
            if( (*iter) == oldNode ){
                nodes.erase(iter);
                break;
            }
        }
        oldNode.reset();
    };




    // Deletes a given node and all its associated incoming and outgoing edges. This function does nothing if
    // the node that is to be deleted does not exist in the graph. Hint: if you are using weak ptrs for edges
    // you may be able to do this quite simply. This function should not throw any exceptions.
    template <typename N, typename E> void Graph<N, E>::deleteNode(const N &val) noexcept{
        // 1. Find the node to be deleted
        // 2. Delete all its outgoing edges
        // 3. Delete all its incoming edges
        // 4. Delete the node from the graph
        bool existNode = false;
        std::shared_ptr<Node> nodeToBeDeleted = nullptr;
        for( auto node : nodes ){
            if( node->data == val ){
                existNode = true;
                nodeToBeDeleted = node;
            }
        }
        if( existNode == false ){
            return;
        }

        for( auto edgePtr : nodeToBeDeleted->outgoing_edges ){
            edgePtr->src_node.reset();
            edgePtr->dst_node.reset();
        }
        nodeToBeDeleted->outgoing_edges.clear();

        for( auto node : nodes ){
            if( node != nodeToBeDeleted ){
                _deleteEdge( nodeToBeDeleted, node->outgoing_edges );
            }
        }

        for( auto iter=nodes.begin(); iter != nodes.end(); iter++ ){
            if( (*iter)->data == val ){
                nodes.erase(iter);
                break;
            }
        }
        nodeToBeDeleted.reset();

    };
    // Deletes an edge from src to dst with weight w. No exceptions are thrown. This method would be called by deleteNode
    // Not use deleteEdge because already know the node where the edge(s) should be deleted
    template <typename N, typename E> void Graph<N, E>::_deleteEdge(std::shared_ptr<Node> &node, std::list<std::shared_ptr<Edge>> &list) noexcept {
        bool flagExitLoop = false;
        while( flagExitLoop == false ){
            bool flagHasElementErased = false;
            typename std::list<std::shared_ptr<Edge>>::iterator iter = list.begin();
            for( iter=list.begin(); iter != list.end(); iter++ ){
                if( (*iter)->dst_node == node ){
                    list.erase(iter);
                    flagHasElementErased = true;

                    (*iter)->src_node.reset();
                    (*iter)->dst_node.reset();
                }
            }
            if( flagHasElementErased == false ){
                flagExitLoop = true;
            }
        }
    }



    // Deletes an edge from src to dst with weight w, only if the edge exists in the graph. No exceptions are thrown
    template <typename N, typename E> void Graph<N, E>::deleteEdge(const N &src, const N &dst, const E &w) noexcept {
        for( auto node : nodes ){
            if( node->data == src ){
                for( auto iter=node->outgoing_edges.begin(); iter != node->outgoing_edges.end(); iter++ ){
                    if( (*iter)->dst_node->data == dst && (*iter)->weight == w ){
                        (*iter)->src_node.reset();
                        (*iter)->dst_node.reset();

                        node->outgoing_edges.erase(iter);
                        break;
                    }
                }
                break;
            }
        }
    }




/****************** Below start to take care of all objects resources allocation and deallocation ********************/

    // Remove all nodes and edges from the graph. New nodes or edges can be added to the graph afterwards.
    template <typename N, typename E> void Graph<N,E>::clear() noexcept {
        while( !nodes.empty() ){
//            std::weak_ptr<Node> node(nodes.back());
//            auto test = node.lock()->data;

            deleteNode( nodes.back()->data );
            nodes.pop_back();
        }
    }


    // Returns true if a node with value val exists in the graph and false otherwise.
    template <typename N, typename E> bool Graph<N, E>::isNode(const N &val) const {
        for( auto node : nodes ){
            if( node->data == val ){
                return true;
            }
        }
        return false;
    };


    // Returns true if src → dst exists in the graph and false otherwise. This function throws a
    // std::runtime_error if either src or dst is not in the graph.
    template <typename N, typename E> bool Graph<N, E>::isConnected(const N &src, const N &dst) const {
        std::shared_ptr<Node> src_node = nullptr;
        std::shared_ptr<Node> dst_node = nullptr;
        for( auto node : nodes ){
            if( node->data == src ){
                src_node = node;
            }
            if( node->data == dst ){
                dst_node = node;
            }
        }
        if( src_node == nullptr || dst_node == nullptr ){
            throw std::runtime_error("The node does not exist !");
        }

        for( auto edge : src_node->outgoing_edges ){
            if( edge->dst_node == dst_node ){
                return true;
            }
        }
        return false;
    }


    // Prints the data stored in all the nodes in the graph, with one node per line, starting from the node with
    // the smallest outdgree to the node with the largest. If two nodes have the same edge count, then the one
    // with the smaller node value determined by the < operator is printed first. See test11.cpp for an example.
    template <typename N, typename E> bool Graph<N, E>::nodeSortRule(const std::shared_ptr<Node> &node1, const std::shared_ptr<Node> &node2) {
        if( node1->outgoing_edges.size() < node2->outgoing_edges.size() ){
            return (node1->outgoing_edges.size() < node2->outgoing_edges.size());
        }
        else if( node2->outgoing_edges.size() < node1->outgoing_edges.size() ){
            return (node1->outgoing_edges.size() < node2->outgoing_edges.size());
        }
        else {   // The number of outgoing edges is same
            return (node1->data < node2->data);
        }
    }
    template <typename N, typename E> void Graph<N, E>::printNodes() const {
        std::vector<std::shared_ptr<Node>> nodesCopy = nodes;
        std::sort(nodesCopy.begin(), nodesCopy.end(), nodeSortRule);
        for( auto node : nodesCopy ){
            std::cout << node->data << std::endl;
        }
    }




    // Prints the outgoing edges of a given node, SrcNode, containing value val. The first line must be "Edges
    // attached to Node X", where X is the data stored at SrcNode. Then, the outgoing edges of SrcNode are printed
    // in increasing order of their weights, with one edge per line adhering to the following format:
    // [the data at the destination node DstNode] [the cost of the edge]
    // For example, if SrcNode → DstNode has a weight 3 (of type int), where the data at DstNode is "abc"
    // (of type std::string), then the print out is "abc3". If SrcNode does not exist in the graph, then a
    // std::runtime_error is thrown with no output printed. If the outdegree of SrcNode is 0, then the first
    // line of the print should work and the second line should be "(null)". If two edges have the same weight,
    // then the edge whose destination node has a smaller node value, again determined by the < operator, is
    // printed first. See test12.cpp for an example.
    template <typename N, typename E> bool Graph<N, E>::edgeSortRule(const std::shared_ptr<Edge> &edge1, const std::shared_ptr<Edge> &edge2){
        if( edge1->weight < edge2->weight ){
            return (edge1->weight < edge2->weight);
        } else if( edge2->weight < edge1->weight){
            return (edge1->weight < edge2->weight);
        } else {  // The weight of two edges is same
            return edge1->dst_node->data < edge2->dst_node->data;
        }
    }
    template <typename N, typename E> void Graph<N, E>::printEdges(const N &val) const {
        std::shared_ptr<Node> node = nullptr;
        for( auto _node : this->nodes ){
            if( _node->data == val ){
                node = _node;
            }
        }
        if( node == nullptr ){
            throw std::runtime_error("The node does not exist !");
        }

        std::list<std::shared_ptr<Edge>> edgesList = node->outgoing_edges;
        std::cout << "Edges attached to Node " << node->data << std::endl;
        if( edgesList.size() == 0 ){
            std::cout << "(null)" << std::endl;
            return;
        }

        edgesList.sort( edgeSortRule );
        // std::sort( edgesList.begin(), edgesList.end(), edgeSortRule);
        for( auto edge : edgesList ){
            std::cout << edge->dst_node->data << " " << edge->weight << std::endl;
        }
    }




    // Sets an internal iterator, i.e. ''pointer'' to the first element of a sequence.
    template <typename N, typename E> void Graph<N, E>::begin() const{
        iter = nodes.begin();
    };

    // Returns true if the iterator goes past the last element of the sequence and false otherwise.
    template <typename N, typename E> bool Graph<N, E>::end() const{
        return (iter == nodes.end());
    };

    // Moves the iterator to the next element of the sequence.
    template <typename N, typename E> void Graph<N, E>::next() const{
        iter ++;
    };

    // Returns the value of the node pointed to by the iterator.
    template <typename N, typename E> const N& Graph<N,E>::value() const{
        return (*iter)->data;
    };

}

#endif //COMP6771_ASS3_GRAPH_H
