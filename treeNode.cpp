#include "treeNode.h"
#include <cassert>
using std::shared_ptr;



treeNode::treeNode()
{
    rtEntry.netId = "";
    rtEntry.port = -1;
    RoutingEntry s = {"", -1};
}

treeNode::treeNode(const std::string netId_in,  int port_in)
{
    rtEntry.netId = netId_in;
    rtEntry.port = port_in;
}

void treeNode::setNetId(const std::string netId_in)
{
    rtEntry.netId = netId_in;
}

void treeNode::setPort(const int port_in)
{
    rtEntry.port = port_in;
}



std::string treeNode::getNetId() const
{
	return rtEntry.netId;
}


 int treeNode::getPort() const
{
	 return rtEntry.port;
}


 RoutingEntry treeNode::getRoutingEntry() const
{
	 RoutingEntry s = { rtEntry.netId , rtEntry.port };
	 return s;
}


bool treeNode::isLeaf() const
{
	if(getLeftChildPtr() != nullptr || getRightChildPtr() != nullptr)
    {
        return true;
    }
	return false;
}

std::shared_ptr<treeNode> treeNode::getLeftChildPtr() const
{
    return leftChildPtr;
}

std::shared_ptr<treeNode>  treeNode::getRightChildPtr() const
{
	return rightChildPtr;
}


void treeNode::setLeftChildPtr(std::shared_ptr<treeNode> leftPtr)
{
    leftChildPtr = leftPtr;
}

void treeNode::setRightChildPtr(std::shared_ptr<treeNode> rightPtr)
{
    rightChildPtr = rightPtr;
}
