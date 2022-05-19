#include "OrgChart.hpp"

using ariel::OrgChart;


/******************************* OrgChart part *******************************/

OrgChart::OrgChart()
{
    _root = Node();
}

OrgChart::~OrgChart()
{
    restartTree();
}

OrgChart& OrgChart::add_root(const string& name)
{
    restartTree();
    _root = Node(name, 0);
    addNodeToMap(name);
    return (*this);
}

OrgChart& OrgChart::add_sub(const string& head, const string& name)
{
    if (!isNodeExists(head) || _mapNameNodes[head].size() == 0)
    {
        throw runtime_error("element doesn't exist - make sure that sub/root was added");
    }

    unsigned int addIndex = 0;       // which one of the roots with same name to add
    // the index of the node is returned from adding
    unsigned int index = addNodeToMap(name);
    _mapNameNodes[head][addIndex].push_back(Node(name, index));
    
    return (*this);
}

ostream& ariel::operator<<(ostream& os, OrgChart& org)
{
    vector<Node*> vec = org.levelOrderVect();
    for (Node* n: vec)
    {
        os << n->getData() << " ";
    }
    return os;
}

bool OrgChart::isNodeExists(string node)
{
    return (_mapNameNodes.count(node) != 0);
}

bool OrgChart::isNodeExists(Node& node)
{
    string nodeStr = node.getData();
    return (isNodeExists(nodeStr) && node.getIndex() < _mapNameNodes[nodeStr].size());
}

/**
 * @brief the function add the node to the keys (if needed) of the map and create new node
 * 
 * @param name 
 * @return int 
 */
unsigned int OrgChart::addNodeToMap(const string& name)
{
    
    // if name does not exsist create it
    if (!isNodeExists(name))
    {
        _mapNameNodes[name] = vector<vector<Node>>();
    }
    unsigned int index = _mapNameNodes[name].size();
    // give him the firs index
    _mapNameNodes[name].push_back(vector<Node>());
    return (index);
}

void OrgChart::restartTree()
{
    _mapNameNodes.clear();
    _root = Node();
}

vector<Node*> OrgChart::levelOrderVect()
{
    vector<Node*> vectNodes = vector<Node*>();
    for (vector<Node*> line : levelOrderDetailed())
    {
        vectNodes.insert(vectNodes.end(), line.begin(), line.end());
    }
    
    return (vectNodes);
}

vector<Node*> OrgChart::levelOrderReverseVect()
{
    vector<Node*> vectNodes = vector<Node*>();
    for (vector<Node*> line : levelOrderDetailed())
    {
        vectNodes.insert(vectNodes.begin(), line.begin(), line.end());
    }
    
    return (vectNodes);
}

vector<vector<Node*>> OrgChart::levelOrderDetailed()
{
    vector<vector<Node*>> nodeLines { vector<Node*> {&_root} };
    unsigned int row = 0;

    // while not reached to the last line
    while (row < nodeLines.size())
    {
        for (unsigned int i = 0; i < nodeLines[row].size(); i++)    // run for each root in row
        {
            vector<Node*> children = getChildrenPointers(*(nodeLines[row][i]));
            // if there are no children then there is nothing to do here
            if (children.size() == 0)
            {
                continue;
            }
            
            // if there are children and this is the last then add one line to the end
            if (row == nodeLines.size() - 1)
            {
                nodeLines.push_back(vector<Node*>());
            }

            // appending all the vector
            nodeLines[row + 1].insert(nodeLines[row + 1].end(), children.begin(), children.end());
        }
        row++;
    }
    return (nodeLines);
}

vector<Node*> OrgChart::getChildrenPointers(Node& node)
{
    vector<Node*> retVec;
    if (!isNodeExists(node))
    {
        return (retVec);
    }
    string name = node.getData();
    unsigned int index = node.getIndex();
    for (unsigned int i = 0; i < _mapNameNodes[node.getData()][index].size(); i++)
    {
        Node* currNode = &(_mapNameNodes[node.getData()][index][i]);
        retVec.push_back(currNode);
    }
    
    return (retVec);
}

//begin and end parts

OrgChart::Iterator OrgChart::begin()
{
    return OrgChart::Iterator(*this, levelOrderVect());
}

OrgChart::Iterator OrgChart::end()
{
    return OrgChart::Iterator(*this, levelOrderVect());
}


OrgChart::level_iterator OrgChart::begin_level_order()
{
    return OrgChart::level_iterator(*this, levelOrderVect());
}

OrgChart::level_iterator OrgChart::end_level_order()
{
    return OrgChart::level_iterator(*this, levelOrderVect(), true);
}

OrgChart::reverse_iterator OrgChart::begin_reverse_order()
{
    return OrgChart::reverse_iterator(*this, levelOrderReverseVect());
}

OrgChart::reverse_iterator OrgChart::end_reverse_order()
{
    return OrgChart::reverse_iterator(*this, levelOrderReverseVect(), true);
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


OrgChart::Iterator::Iterator(OrgChart& org, vector<Node*> nodes, bool isEnd) : level_iterator(org, nodes, isEnd)
{
    
}



/******************************* level_iterator class *******************************/


OrgChart::level_iterator::level_iterator(OrgChart& org, vector<Node*> nodes, bool isEnd) : _org(org)
{
    _vectNode = nodes;
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
    if (&_org != &(other._org))
    {
        throw runtime_error("not the same organization");
    }
    return (_index != other._index &&
            _index < this->_vectNode.size() && _index < other._vectNode.size() && 
            _vectNode[_index] == other._vectNode[_index]);
}

const string* OrgChart::level_iterator::operator->()
{
    return &(_vectNode[_index]->getData());
}



/******************************* reverse_iterator class *******************************/


OrgChart::reverse_iterator::reverse_iterator(OrgChart& org, vector<Node*> nodes, bool isEnd) : level_iterator(org, nodes, isEnd)
{
    
}

// OrgChart::reverse_iterator& OrgChart::reverse_iterator::operator++()
// {
//     return (*this);
// }

// string OrgChart::reverse_iterator::operator*() const
// {
//     return "";
// }

// bool OrgChart::reverse_iterator::operator!=(const reverse_iterator& other)
// {
//     return (false);
// }

// string* OrgChart::reverse_iterator::operator->()
// {
//     return nullptr;
// }



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








