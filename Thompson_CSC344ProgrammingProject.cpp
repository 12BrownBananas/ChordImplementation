/* 
 * File:   Thompson_CSC344ProgrammingProject.cpp
 * Author: Garrett Thompson
 *
 * Created on October 28, 2016, 12:32 PM
 */

#include <iostream>
#include <typeinfo>
#include <valarray>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

/*
 * 
 */
int getValidInt() {
    string badInput;
    int val;
    cin>>val;
    while (cin.fail()) {
        cout << "Error: Non-integer value. Please re-enter: ";
        cin.clear();
        getline(cin,badInput);
        cin>>val;
    }
    return val;
}
int* getUserInput() {
    int b;
    int n;
    int* userInput = new int[2];
    cout<<"Please enter a value for B (> 0): ";
    b = getValidInt();
    while (b < 5 || b > 10) {
        if (b < 5) {
            cout<<"Error: B is < 5. Please re-enter: ";
        }
        if (b > 10) {
            cout<<"Error: B is > 10. Please re-enter: ";
        }
        b = getValidInt();
    }
    userInput[0] = b;
    cout<<"Please enter a value for N (> 0, <= 2^B): ";
    n = getValidInt();
    while (n < 5 || n > 15) {
        if (n < 5) {
            cout<<"Error: N is < 5. Please re-enter: ";
        }
        if (n > 15) {
            cout<<"Error: N is > 15. Please re-enter: ";
        }
        n = getValidInt();
    }
    userInput[1] = n;
    return userInput;
}
int* addNodeToIDSpace(int* nodeList, int IDSpaceSize, int listIdx) {
    time_t timer;
    srand(time(&timer));
    
    int nodeID = (rand()%IDSpaceSize)+1;
    for (int i = 0; i < IDSpaceSize; i++) {
        if (nodeID == nodeList[i]) {
            i = -1;
            nodeID = (rand()%IDSpaceSize)+1;
        }
    }
    nodeList[listIdx] = nodeID;
    return nodeList;
}
int getLargestIdx(int* nodeList, int IDSpaceSize) {
    int largest = 0;
    for (int i = 0; i < IDSpaceSize; i++) {
        if (nodeList[i] > nodeList[largest]) {
            largest = i;
        }
    }
    return largest;
}
int getSmallestIdx(int* nodeList, int IDSpaceSize) {
    int smallest = 0;
    for (int i = 0; i < IDSpaceSize; i++) {
        if (nodeList[i] < nodeList[smallest] && nodeList[i] != 0) {
            smallest = i;
        }
    }
    return smallest;
}
int getSecondSmallestIdx(int* nodeList, int IDSpaceSize) {
    int smallest = getSmallestIdx(nodeList, IDSpaceSize);
    int secondSmallest = 0;
    for (int i= 0; i < IDSpaceSize; i++) {
        if (nodeList[i] < nodeList[secondSmallest] && nodeList[i] != 0 && nodeList[i] != nodeList[smallest]) {
            secondSmallest = i;
        }
    }
    return secondSmallest;
}
int* makeFingerTable(int* nodeList, int IDSpaceSize, int nodeIdx, int m) {
    int* fingerTable = new int[m];
    int tableIdx = 1;    
    int nodeID = nodeList[nodeIdx];
    fingerTable[0] = nodeID;  //Identifies whose finger table this is
    int nextIndex;
    int largestIdx = getLargestIdx(nodeList, IDSpaceSize);
    
    for (int i = 1; i <= m; i=2*i) { //This is the +x value attached to the node ID
        if (nodeID+i < IDSpaceSize) {
            if (nodeID+i < nodeList[largestIdx]){
                nextIndex = nodeID+i;
            }
            else {
                nextIndex = 0;
            }
        }
        else {
            nextIndex = (nodeID+i)-IDSpaceSize;
        }
        //Now we want to find the closest larger-valued node.
        int closestNode = -1;
        for (int j = 0; j < IDSpaceSize; j++) {
            if (nodeList[j] >= nextIndex && nodeList[j] != 0) {
                if (nodeList[j] - nextIndex < closestNode-nextIndex || closestNode == -1) {
                    closestNode = nodeList[j];
                }
            }
        }
        fingerTable[tableIdx] = closestNode;
        tableIdx++;
    }
    return fingerTable;
}
int findClosestNode(int* nodeList, int keyID, int idSpace) {
    int closestNode;
    if (keyID > nodeList[getLargestIdx(nodeList, idSpace)]) {
        closestNode = nodeList[getSmallestIdx(nodeList, idSpace)];
    }
    else {
        closestNode = -1;
        for (int i = 0; i < idSpace; i++) {
            if (nodeList[i]-keyID >= 0) {
                if (nodeList[i]-keyID < closestNode-keyID || closestNode == -1) {
                    closestNode = nodeList[i];
                }
            }
        }
    }
    return closestNode;
}
int getIdxOf(int* nodeList, int nodeID, int idSpace) {
    for (int i = 0; i < idSpace; i++) {
        if (nodeList[i] == nodeID) {
            return i;
        }
    }
    return -1;
}
int findNextVisitingNode(int* fingerTable, int bMinusOne, int closestNode) {
    //Exhaust the finger table until you find either the key ID or the last idx of the table
    for (int i = 1; i <= bMinusOne; i++) {
        if (fingerTable[i] == closestNode) {
            return fingerTable[i];
        }
        else {
            if (i != 0) {
                if (fingerTable[i] > closestNode && fingerTable[i-1] < closestNode) {
                    return fingerTable[i-1];
                }
            }
            if (i == 0) {
                if (fingerTable[i] > closestNode && fingerTable[0] < closestNode) {
                    return fingerTable[i];
                }
            }
            if (i == bMinusOne) {
                return fingerTable[i];
            }
        }
    }
}
bool hasKeyID(int* fingerTable, int bMinusOne, int closestNode) {
    for (int i = 1; i <= bMinusOne; i++) {
        if (fingerTable[i] == closestNode) {
            return true;
        }
        else if (i == bMinusOne) {
            return false;
        }
    }
}
void printFingerTable(int* fingerTable, int bMinusOne) {
    int addedNum = 1;
    cout<<"Finger table for N";cout<<fingerTable[0];cout<<": "<<endl;
    for (int i = 1; i <= bMinusOne; i++) {
        cout<<"N+";cout<<addedNum;cout<<": ";cout<<fingerTable[i]<<endl;
        addedNum = addedNum*2;
    }
    cout<<"\n";
}
int main(int argc, char** argv) {
    int* userInput = getUserInput();
    int numNodes = userInput[1];
    int idSpace = pow(2, userInput[0]);
    int listIdx = 0;
    int* nodeList = new int[idSpace];
    for (int i = 0; i < idSpace; i++) {
        nodeList[i] = 0;
    }
    cout<<"\nNodeIDs created: ";
    for (int i = 0; i < numNodes; i++) {
        addNodeToIDSpace(nodeList, idSpace, listIdx);
        cout<<nodeList[listIdx];cout<<", ";
        listIdx++;
    }
    int m = pow(2, userInput[0]-1);
    int** fingerTables = new int*[numNodes];
    for (int i = 0; i < numNodes; i++) {
        int* fingerTable = makeFingerTable(nodeList, idSpace, i, m);
        fingerTables[i] = fingerTable;
    }
    //Now that we've generated finger tables for every node...
    int keyID = (rand()%idSpace)+1;
    int currNodeIdx = getSecondSmallestIdx(nodeList, idSpace);
    int nStart = nodeList[currNodeIdx];
    int closestNode = findClosestNode(nodeList, keyID, idSpace);
    cout<<"\nKey ID: ";cout<<keyID<<endl;
    cout<<"nStart: ";cout<<nStart<<endl;
    //Now, use the finger table to locate the node with this key.
    //Go up through that node's finger table until you find the closest
    //larger or equal node to the key. 
    int currNode = nStart;
    std::vector<int> visitingOrder;
    visitingOrder.push_back(currNode);
    while (hasKeyID(fingerTables[currNodeIdx], userInput[0]-1, closestNode) == false) {
        currNode = findNextVisitingNode(fingerTables[currNodeIdx], userInput[0]-1, closestNode);
        currNodeIdx = getIdxOf(nodeList, currNode, idSpace);
        visitingOrder.push_back(currNode);
    }
    currNode = findNextVisitingNode(fingerTables[currNodeIdx], userInput[0]-1, closestNode);
    visitingOrder.push_back(currNode);
    cout<<"\nVisiting Order: ";
    for (int i = 0; i < visitingOrder.size(); i++) {
        if (i != visitingOrder.size()-1) {
            cout<<visitingOrder.at(i);cout<<", ";
        }
        else {
            cout<<visitingOrder.at(i)<<endl;
        }
    }
    cout<<"\n";
    for (int i = 0; i < visitingOrder.size(); i++) {
        printFingerTable(fingerTables[getIdxOf(nodeList, visitingOrder.at(i), idSpace)], userInput[0]-1);
    }
}