#include "OrgChart.hpp"
#include <chrono>
#include <thread>
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
    os << org.toString(org._root, "");
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

vector<Node*> OrgChart::getPreorderNodes()
{
    vector<Node*> nodes;
    setPreorderRec(_root, nodes);
    return nodes;

}

// by given vector create the preorder vector
void OrgChart::setPreorderRec(Node& head, vector <Node*>& nodes)
{
    if (!isNodeExists(head))
    {
        return;
    }
    nodes.push_back(&head);
    for (Node* node : getChildrenPointers(head))
    {
        if (node == nullptr)
        {
            continue;
        }
        setPreorderRec(*node, nodes);
    }
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

string OrgChart::toString(Node& head, string s)
{
    string retStr;
    if (!isNodeExists(head))
    {
        return "";
    }

    //retStr += toupper(head.getData());
    for (char ch : head.getData())
    {
        retStr += toupper(ch);
    }
    
    auto v = getChildrenPointers(head);
    
    if (v.size() == 0)
    {
        retStr += "\n ";
        retStr += (s + "\n") + " ";
        return (retStr);
    }

    if (v.size() > 0)
    {
        retStr += string(13, '-');
    }

    unsigned int spaceCalc = head.getData().size() + 12;
    string stry(spaceCalc, ' ');
    int i = 0;
    for (Node* node : v)
    {
        if (node == nullptr)
        {
            continue;
        }
        string st = s + stry;
        if (i > 0)
        {
            retStr += st;
        }
        st += (i < v.size()-1) ? "|" : " ";

        retStr += toString(*node, st);
        
        i++;

    }
    
    return retStr;
}

//begin and end parts

OrgChart::Iterator OrgChart::begin()
{
    return OrgChart::Iterator(*this, levelOrderVect());
}

OrgChart::Iterator OrgChart::end()
{
    return OrgChart::Iterator(*this, levelOrderVect(), true);
}


OrgChart::level_iterator OrgChart::begin_level_order()
{
    return OrgChart::level_iterator(*this);
}

OrgChart::level_iterator OrgChart::end_level_order()
{
    return OrgChart::level_iterator(*this, true);
}

OrgChart::reverse_iterator OrgChart::begin_reverse_order()
{
    return OrgChart::reverse_iterator(*this);
}

OrgChart::reverse_iterator OrgChart::end_reverse_order()
{
    return OrgChart::reverse_iterator(*this, true);
}

OrgChart::preorder_iterator OrgChart::begin_preorder()
{
    return OrgChart::preorder_iterator(*this);
}

OrgChart::preorder_iterator OrgChart::end_preorder()
{
    return OrgChart::preorder_iterator(*this, true);
}


/******************************* iterator class *******************************/



OrgChart::Iterator::Iterator(OrgChart& org, const vector<Node*>& nodes, bool isEnd) : _org(org)
{
    _vectNode = nodes;
    //take the size as the last index
    _index = isEnd ? _vectNode.size() : 0;
    _vectNode.push_back(nullptr);
}

OrgChart::Iterator& OrgChart::Iterator::operator++()
{
    if (_index >= _vectNode.size())
    {
        throw runtime_error("unresticked area");
    }
    _index++;
    return (*this);
}

string& OrgChart::Iterator::operator*() const
{
    return _vectNode[_index]->getData();
}

bool OrgChart::Iterator::operator!=(const Iterator& other)
{
    return !(*this == other);
}

bool OrgChart::Iterator::operator==(const Iterator& other)
{
    if (&_org != &(other._org))
    {
        throw runtime_error("not the same organization");
    }
    return (_index == other._index &&
            (_index < this->_vectNode.size() && other._index < other._vectNode.size()) && 
            _vectNode[_index] == other._vectNode[_index]);
}

const string* OrgChart::Iterator::operator->()
{
    return &(_vectNode[_index]->getData());
}



/******************************* level_iterator class *******************************/


OrgChart::level_iterator::level_iterator(OrgChart& org, bool isEnd) : Iterator(org, org.levelOrderVect(), isEnd)
{

}

/******************************* reverse_iterator class *******************************/


OrgChart::reverse_iterator::reverse_iterator(OrgChart& org, bool isEnd) : Iterator(org, org.levelOrderReverseVect(), isEnd)
{
    
}


/******************************* preorder_iterator class *******************************/


OrgChart::preorder_iterator::preorder_iterator(OrgChart& org, bool isEnd) : Iterator(org, org.getPreorderNodes(), isEnd)
{

}








