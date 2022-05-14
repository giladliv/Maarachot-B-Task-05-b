#include "OrgChart.hpp"

using ariel::OrgChart;


/******************************* OrgChart part *******************************/

OrgChart::OrgChart()
{
    _root = nullptr;
}

OrgChart::~OrgChart()
{
    restartTree();
}

OrgChart& OrgChart::add_root(const string& name)
{
    restartTree();
    _root = new Node(name);
    addNodeToMap(_root);
    return (*this);
}

OrgChart& OrgChart::add_sub(const string& head, const string& name)
{
    if (_mapNameNodes.count(head) == 0 || _mapNameNodes[head].size() == 0)
    {
        throw runtime_error("element doesn't exist - make sure that sub/root was added");
    }
    Node* node = _mapNameNodes[head][0]->addNext(name);
    if (node != nullptr)
    {
        _mapNameNodes[head].push_back(node);
        addNodeToMap(node);
    }
    
    return (*this);
}

ostream& ariel::operator<<(ostream& os, OrgChart& org)
{
    vector<Node*> vec = org.levelOrderVect(org._root);
    for (Node* n: vec)
    {
        os << n->getData() << " ";
    }
    return os;
}

void OrgChart::restartTree()
{
    Node::freeAllTree(_root);
    _mapNameNodes.clear();
    _root = nullptr;
}

void OrgChart::addNodeToMap(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    string name = node->getData();
    if (_mapNameNodes.count(name) == 0)
    {
        _mapNameNodes[name] = vector<Node*>();
    }
    _mapNameNodes[name].push_back(node);
}

vector<Node*> OrgChart::levelOrderVect(Node* node)
{
    vector<Node*> vectNodes{node};
    unsigned int i = 0;
    while (i < vectNodes.size())
    {
        if (vectNodes[i] == nullptr)
        {
            // remove the curr index if null - dont inc the index
            vectNodes.erase(vectNodes.begin() + i);
            continue;
        }
        
        vector<Node*> currV = vectNodes[i]->getNext();
        vectNodes.insert(vectNodes.end(), currV.begin(), currV.end());
        i++;
    }
    return (vectNodes);
}

//begin and end parts

OrgChart::iterator OrgChart::begin()
{
    return OrgChart::iterator();
}

OrgChart::iterator OrgChart::end()
{
    return OrgChart::iterator();
}


OrgChart::level_iterator OrgChart::begin_level_order()
{
    return OrgChart::level_iterator(_root);
}

OrgChart::level_iterator OrgChart::end_level_order()
{
    return OrgChart::level_iterator(_root, true);
}

OrgChart::reverse_iterator OrgChart::begin_reverse_order()
{
    return OrgChart::reverse_iterator();
}

OrgChart::reverse_iterator OrgChart::end_reverse_order()
{
    return OrgChart::reverse_iterator();
}

OrgChart::preorder_iterator OrgChart::begin_preorder()
{
    return OrgChart::preorder_iterator();
}

OrgChart::preorder_iterator OrgChart::end_preorder()
{
    return OrgChart::preorder_iterator();
}



/******************************* iterator class *******************************/


OrgChart::iterator::iterator()
{

}

OrgChart::iterator& OrgChart::iterator::operator++()
{
    return (*this);
}

string OrgChart::iterator::operator*() const
{
    return "";
}

bool OrgChart::iterator::operator!=(const iterator& other)
{
    return (false);
}

string* OrgChart::iterator::operator->()
{
    return nullptr;
}



/******************************* level_iterator class *******************************/


OrgChart::level_iterator::level_iterator(Node* node, bool isEnd)
{
    _vectNode = OrgChart::levelOrderVect(node);
    _index = isEnd ? _vectNode.size() : 0;
    _vectNode.push_back(nullptr);
}

OrgChart::level_iterator& OrgChart::level_iterator::operator++()
{
    if (_index >= _vectNode.size())
    {
        throw runtime_error("unresticked area");
    }
    _index++;
    return (*this);
}

string OrgChart::level_iterator::operator*() const
{
    return _vectNode[_index]->getData();
}

bool OrgChart::level_iterator::operator!=(const level_iterator& other)
{
    return (_index != other._index &&
            _index < this->_vectNode.size() && _index < other._vectNode.size() && 
            _vectNode[_index] == other._vectNode[_index]);
}

string* OrgChart::level_iterator::operator->()
{
    return &(_vectNode[_index]->getData());
}



/******************************* reverse_iterator class *******************************/


OrgChart::reverse_iterator::reverse_iterator()
{

}

OrgChart::reverse_iterator& OrgChart::reverse_iterator::operator++()
{
    return (*this);
}

string OrgChart::reverse_iterator::operator*() const
{
    return "";
}

bool OrgChart::reverse_iterator::operator!=(const reverse_iterator& other)
{
    return (false);
}

string* OrgChart::reverse_iterator::operator->()
{
    return nullptr;
}



/******************************* preorder_iterator class *******************************/


OrgChart::preorder_iterator::preorder_iterator()
{

}

OrgChart::preorder_iterator& OrgChart::preorder_iterator::operator++()
{
    return (*this);
}

string OrgChart::preorder_iterator::operator*() const
{
    return "";
}

bool OrgChart::preorder_iterator::operator!=(const preorder_iterator& other)
{
    return (false);
}

string* OrgChart::preorder_iterator::operator->()
{
    return nullptr;
}








