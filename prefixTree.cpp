

#include "prefixTree.h"
#include "treeNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <map>
#include <memory>
using std::shared_ptr;

#include <cstdlib>
using namespace std;

prefixTree::prefixTree()
{
    rootPtr = nullptr;
}  // end default constructor


prefixTree::prefixTree(std::string filename)
{
    std::string line;
    std::string myString;
    
    std::string networkID;
    int portNumber;
    
    treeNode p;
    prefixTree q;
    
    std::ifstream iFile;
    iFile.open(filename);
    
    if (!iFile.is_open())
    {
        std::cerr << "ERROR: could not open file " << filename << "\n";
    }
    
    else
    {
        while (getline(iFile, line))
        {
            stringstream ss(line);
        
            getline(ss, myString, ':');
            networkID = (myString);
            p.setNetId(myString);
            
            getline(ss, myString, '\n');
            portNumber = stoi(myString);
            p.setPort(portNumber);
            
            prefixTree().add(p.getNetId(), p.getPort());
            
        }
    }
    
}


prefixTree::~prefixTree()
{
    RemoveSubtree(rootPtr);
}


void prefixTree::RemoveSubtree(std::shared_ptr<treeNode> ptr)
{
    if (ptr != nullptr)
    {
        if (ptr->getLeftChildPtr() != nullptr)
        {
            RemoveSubtree(ptr->getLeftChildPtr());
        }
        if (ptr->getRightChildPtr() != nullptr)
        {
            RemoveSubtree(ptr->getRightChildPtr());
        }
        
        cout << "Deleting the node contaiing key " << ptr->getNetId() << endl;
    }
}

bool prefixTree::add(const std::string netid, const int port)
{
    addLeaf(netid, port);
    return true;
}


void prefixTree::addLeaf(const std::string netid, const  int port)
{
    addLeafPrivate(netid, port, rootPtr);
}


void prefixTree::addLeafPrivate(const std::string netid, const  int port, std::shared_ptr<treeNode> ptr)
{
    if (rootPtr == nullptr)
    {
        rootPtr = createLeaf(netid, port);
    }
    
    else if (port < ptr->getPort())
    {
        if (ptr->getLeftChildPtr() != nullptr)
        {
            addLeafPrivate(netid, port, ptr->getLeftChildPtr());
        }
        else
            ptr->setLeftChildPtr(createLeaf(netid, port));
    }
    
    else if (port > ptr->getPort())
    {
        if (ptr->getRightChildPtr() != nullptr)
        {
            addLeafPrivate(netid, port, ptr->getRightChildPtr());
        }
        else
            ptr->setRightChildPtr(createLeaf(netid, port));
    }
    
    else
        cout << " The port " << port << " has already been added to the tree \n";
}


std::shared_ptr<treeNode> prefixTree::createLeaf(const std::string netid, const  int port)
{
    std::shared_ptr<treeNode> n;
    n->setPort(port);
    n->setNetId(netid);
    n->setRightChildPtr(nullptr);
    n->setLeftChildPtr(nullptr);
    return n;
    
}


int prefixTree::findPort(std::string ipaddr) const
{
	return -1;
}


bool prefixTree::remove(const std::string prefix)
{
    if (rootPtr == nullptr)
    {
        return false;
    }
    
    removeNodePrivate(prefix, rootPtr);
    return true;
}

void prefixTree::clear()
{
    rootPtr = nullptr;
	return;
}


std::string prefixTree::postorderTraverseHelper(std::string visit(std::shared_ptr<treeNode> NodePtr), std::shared_ptr<treeNode> treePtr) const
{
	return "";
}

RoutingEntry  prefixTree::getRoutingEntry(const std::string netId) const 
{
	return RoutingEntry{ "", -1 };
}

std::string prefixTree::postorderTraverse(std::string visit(std::shared_ptr<treeNode> NodePtr)) const
{
	return "";
}


void prefixTree::removeNodePrivate(std::string prefix, std::shared_ptr<treeNode> parent)
{
    if (rootPtr != nullptr)
    {
        if ((rootPtr->getNetId() == prefix))
        {
            RemoveNodeMatch();
        }
        else
        {
            if (prefix < parent->getNetId() && parent->getLeftChildPtr() != nullptr)
            {
                parent->getLeftChildPtr()->getNetId() == prefix ?
                RemoveMatch(parent, parent->getLeftChildPtr(), true) :
                removeNodePrivate(prefix, parent->getLeftChildPtr());
            }
            else if (prefix > parent->getNetId() && parent->getRightChildPtr() != nullptr)
            {
                parent->getRightChildPtr()->getNetId() == prefix ?
                RemoveMatch(parent, parent->getRightChildPtr(), false):
                removeNodePrivate(prefix, parent->getRightChildPtr());
            }
            else
                cout<<" The prefix was not in the tree ";
        }
    }
}



void prefixTree::RemoveNodeMatch()
{
    if (rootPtr != nullptr)
    {
        std::shared_ptr<treeNode> delPtr = rootPtr;
        std::string rootKey = rootPtr->getNetId();
        std::string smallestInRightSubtree;
        
        //case 0-0 kids
        if (rootPtr->getLeftChildPtr() == nullptr && rootPtr->getRightChildPtr() == nullptr)
        {
            rootPtr = nullptr;
            //delete delPtr;
        }
        
        //case 1
        else if (rootPtr->getLeftChildPtr() == nullptr && rootPtr->getRightChildPtr() != nullptr)
        {
            rootPtr = rootPtr->getRightChildPtr();
            delPtr->setRightChildPtr(nullptr);
            //delete the delPtr
            std::cout<<" The root node with key " << rootKey << " was deleted. " <<" The new root countains key " << rootPtr->getNetId()<< endl;
        }
        
        else if (rootPtr->getLeftChildPtr() != nullptr && rootPtr->getRightChildPtr() == nullptr)
        {
            rootPtr = rootPtr->getLeftChildPtr();
            delPtr->setLeftChildPtr(nullptr);
            //delete delptr
            std::cout<<" The root node with key " << rootKey << " was deleted. " <<" The new root countains key " << rootPtr->getNetId()<< endl;
        }
        
        
        //case 2 2 kids
        else
        {
            smallestInRightSubtree = FindSmallestPrivate(rootPtr->getRightChildPtr());
            removeNodePrivate(smallestInRightSubtree, rootPtr);
            rootPtr->getNetId() = smallestInRightSubtree;
            std::cout<<" THE root key containing key " << rootKey << " was overwritten with key " << rootPtr->getNetId() << endl;
        }
    }
    else
        std::cout << "Can not remove root. The tree is EMPTY\n";
    
}


void prefixTree::RemoveMatch(std::shared_ptr<treeNode> parent, std::shared_ptr<treeNode> match, bool left)
{
    if (rootPtr != nullptr)
    {
        std::shared_ptr<treeNode> delPtr = rootPtr;
        string matchKey = match->getNetId();
        string smallestInRightSubtree;
        
        //case 0 - 0 kinds
        if (match->getLeftChildPtr() == nullptr && match->getRightChildPtr() == nullptr)
        {
            delPtr = match;
            left == true ? parent->setLeftChildPtr(nullptr) : parent->setRightChildPtr(nullptr);
            delPtr = nullptr;
            cout<<"The node contaiing key " << matchKey << " was removed \n";
        }
        
        // case 2
        else if (match->getLeftChildPtr() == nullptr && match->getRightChildPtr() != nullptr)
        {
            left == true ? parent->getLeftChildPtr() = match->getRightChildPtr() : parent->getRightChildPtr() = match->getRightChildPtr();
            match->setRightChildPtr(nullptr);
            delPtr = match;
            delPtr = nullptr;
            cout << "The node contaiing key " << matchKey << " was removed \n";
        }
        
        else if (match->getLeftChildPtr() != nullptr && match->getRightChildPtr() == nullptr)
        {
            left == true ? parent->getLeftChildPtr() = match->getLeftChildPtr() : parent->getRightChildPtr() = match->getLeftChildPtr();
            match->setLeftChildPtr(nullptr);
            delPtr = match;
            delPtr = nullptr;
            cout << "The node contaiing key " << matchKey << " was removed \n";
        }
        
        //case2 2 kids
        else{
            smallestInRightSubtree = FindSmallestPrivate(match->getRightChildPtr());
            removeNodePrivate(smallestInRightSubtree, match);
            match->setNetId(smallestInRightSubtree);
        }
    }
}


int prefixTree::FindSmallestPrivate(std::shared_ptr<treeNode> ptr)
{
    if (rootPtr == nullptr)
    {
        return -1000;
        std::cout<<"This tree is empty \n";
    }
    
    else
    {
        if (ptr->getLeftChildPtr() != nullptr)
        {
            return FindSmallestPrivate(ptr->getLeftChildPtr());
        }
        else
        {
            return ptr->getPort();
        }
    }
}


int prefixTree::FindSmallest()
{
    return FindSmallestPrivate(rootPtr);
}

int prefixTree::getHeightHelper(std::shared_ptr<treeNode> subTreePtr) const
{
    if (rootPtr == nullptr)
    return 0;
    
    int lh = getHeightHelper(subTreePtr->getLeftChildPtr());
    int rh = getHeightHelper(subTreePtr->getRightChildPtr());
    
    return 1 + max(lh, rh);
}


int prefixTree::max(int a, int b) const
{
    return ((a > b) ? a : b);
}

int prefixTree::getNumberOfNodesHelper(std::shared_ptr<treeNode> subTreePtr) const
{
    int n = 1;
    
    if (subTreePtr == nullptr)
        return 0;
    
    if(subTreePtr->getLeftChildPtr() != nullptr)
    {
        n = n+1;
        n = getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
    }
    
    if (subTreePtr->getRightChildPtr() != nullptr)
    {
        n = n+1;
        n = getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
    }
    
    return n;
	
}

bool prefixTree::isEmpty() const
{
    bool result;
    
    if (rootPtr == nullptr)
    {
        result = true;
    }
    
    else if (rootPtr != nullptr && rootPtr->getLeftChildPtr() == nullptr && rootPtr->getRightChildPtr() == nullptr)
    {
        result = true;
    }
    
    else
        result = false;
    
    return result;
}



int prefixTree::getHeight() const
{
    return getHeightHelper(rootPtr);
}


int prefixTree::getNumberOfNodes() const
{
    return getNumberOfNodesHelper(rootPtr);
}



