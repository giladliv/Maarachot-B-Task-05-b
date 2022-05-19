#include "Node.hpp"

using ariel::Node;

Node::Node() : Node("", 0)
{

}

Node::Node(const string& str, unsigned int index) : _index(index)
{
    _name = str;
}

Node::~Node()
{
    
}

Node& Node::operator=(const Node& other)
{
    if (this == &other)
    {
        return (*this);
    }
    _index = other._index;
    _name = other._name;
    return (*this);

}