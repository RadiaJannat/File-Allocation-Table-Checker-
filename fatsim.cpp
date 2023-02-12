// -------------------------------------------------------------------------------------
// this is the only file you need to edit
// -------------------------------------------------------------------------------------
//
// (c) 2021, Pavol Federl, pfederl@ucalgary.ca
// Do not distribute this file.

#include "fatsim.h"
#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>


#include <vector>
using namespace std;





//Reference for the code for the 'Graph' struct is from Stephane's tutorial github:
//https://github.com/stephanedorotich/t457/blob/main/6-FAT/FATgraph_v2.cpp


struct Graph {
    std::vector<std::vector<int>> adj_list;
    std::vector<int> terminating_nodes;
    
    // Constructor
    Graph (int n) {
        adj_list.resize(n);
        terminating_nodes = std::vector<int>();
        // Fill adj_list with n empty vectors
        std::fill(adj_list.begin(), adj_list.end(), std::vector<int>());
    }
};





//Reference for the code for the function 'build_graph' is from Stephane's tutorial github:
//https://github.com/stephanedorotich/t457/blob/main/6-FAT/FATgraph_v2.cpp


void build_graph(Graph & g, const std::vector<long> & fat) {
    // TASK: build a graph such that
    // for each element of FAT
    //  there is an outgoing edge from the node denoted by the index
    //  to the node denoted by the value.
    //  e.g.
    //      if   FAT[7] = 13
    //      then     7 -> 13
    
    // populate the adj_list (a node's adj_list stores its incoming edges)


    for(unsigned long p = 0; p < fat.size(); p+=1) {
        if(fat[p] != -1) {
            g.adj_list[fat[p]].push_back(p); 
        }
        else if(fat[p] == -1) {
            g.terminating_nodes.push_back(p); 
        }
    }
}




vector<long> finalRes;

// reimplement this function
std::vector<long> fat_check(const std::vector<long> & fat) {

    //Making a Graph struct 'g' of the size of the 'fat' file and then 
    Graph g = Graph(fat.size());
    //building the graph by populating the adjacency list vector and termnating nodes vector;
    build_graph(g, fat);

    
    long longestLength, lengthNow, nodeNow;
    //longestLength variable will keep in track the longest length found till now
    //lengthNow variable checks what is the current length
    //nodeNow variable checks what current variable is

    //We'll be using stack to solve the assignment problem
    stack<pair<long, long>> stackUse; 

    
    //Initially longestLength is 0
    longestLength = 0;
    for(long value : g.terminating_nodes) { 

        //we start wiith a terminating node and an initial length of 1, emplacing this into the stack created
        stackUse.emplace(value, 1); 

        while(!stackUse.empty()) { 

            nodeNow = stackUse.top().first; //Value that is stored in the top of the stack
            lengthNow = stackUse.top().second; //Length of the node that is stored at the top of the stack

            //After storing the data we need from the top of stack in separate variables, we then pop it from the stack
            stackUse.pop();

            // printf("nodeNow %ld, lengthNow %ld\n", nodeNow, lengthNow); 

            //if current length is greater than the longest length we had previously stored, we have found a new longest length
            if(lengthNow > longestLength) {

                //Hence we clear the previous results and set the new longest length
                finalRes.clear();
                longestLength = lengthNow;
                
                //finalRes.push_back(nodeNow);
            }

            //now we iterate through the adjacent nodes and add them to the stack with 1 greater length
            for(long unsigned int r = 0; r < g.adj_list[nodeNow].size(); r+=1){
                auto n = g.adj_list[nodeNow].at(r);
                stackUse.emplace(n, lengthNow+1);
            }
 
            //if the lenth of current node is equal to the longest length saved, then we push this node into the results vector
            if(lengthNow == longestLength){
                finalRes.push_back(nodeNow);
            }
             
        }
    } 

    //This is to sort the results vector in ascending order
    sort(finalRes.begin(), finalRes.end());
    return finalRes;
}

