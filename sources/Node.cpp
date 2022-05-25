#include "Node.hpp"

using ariel::Node;

Node::Node() : Node("", 0)
{

}

Node::Node(const string& str, unsigned int index) : _index(index)
{
    _name = str;
}
