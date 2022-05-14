#include "Node.hpp"

using ariel::Node;

Node::Node(const string& str)
{
    _name = str;
}

Node::~Node()
{
    
}

Node* Node::addNext(const string& str)
{
    Node* node = new Node(str);
    
    if (node != nullptr)
    {
        _children.push_back(node);
    }
    
    return (node);
}

void Node::freeAllTree(Node* node)
{
    vector<Node*> vectNodes{node};
    unsigned int i = 0;
    while (i < vectNodes.size())
    {
        if (vectNodes[i] == nullptr)
        {
            i++;
            continue;
        }
        
        vector<Node*> currV = vectNodes[i]->_children;
        vectNodes.insert(vectNodes.end(), currV.begin(), currV.end());
        
        delete vectNodes[i];
        i++;
    }
    
}