#include "OrgChart.hpp"

using ariel::OrgChart;


/******************************* OrgChart part *******************************/

/**
 * @brief Construct a new Org Chart:: Org Chart object
 * 
 * @param other 
 */
OrgChart::OrgChart(const OrgChart& other)
{
    (*this) = other;
}

/**
 * @brief copy operator - deep copy
 * 
 * @param other 
 * @return OrgChart& 
 */
OrgChart& OrgChart::operator=(const OrgChart& other)
{
    if (this == &other)
    {
        return (*this);
    }
    _root = other._root;
    _mapNameNodes = other._mapNameNodes;
    setAllOrders();
    return (*this);
}

/**
 * @brief adds a root and replace the old - since root can be one and only - can be deleted
 * 
 * @param name 
 * @return OrgChart& 
 */
OrgChart& OrgChart::add_root(const string& name)
{
    // get the result of the adding
    unsigned int index = addNodeToMap(name);
    if (isNodeExists(_root))
    {
        // get the content of its children
        if (_mapNameNodes[_root.getData()].size() > _root.getIndex())
        {
            _mapNameNodes[name][index] = _mapNameNodes[_root.getData()][_root.getIndex()];
        }
        // delete the root
        _mapNameNodes.erase(_root.getData());
        
    }
    // set as the new root
    _root = Node(name, index);
    setAllOrders();             // set all the relevant vectors for the iterator
    return (*this);

}

/**
 * @brief add subdevision for the devision
 * 
 * @param head 
 * @param name 
 * @return OrgChart& 
 */
OrgChart& OrgChart::add_sub(const string& head, const string& name)
{
    // if dosn't exist throw an exception
    if (!isNodeExists(head) || _mapNameNodes[head].empty())
    {
        throw runtime_error("element doesn't exist - make sure that sub/root was added");
    }

    unsigned int addIndex = 0;       // which one of the roots with same name to add
    // the index of the node is returned from adding
    unsigned int index = addNodeToMap(name);
    _mapNameNodes[head][addIndex].push_back(Node(name, index));
    setAllOrders();
    return (*this);
}

ostream& ariel::operator<<(ostream& os, OrgChart& org)
{
    // set the output as needed
    os << org.toString();
    return os;
}

/**
 * @brief if node exists in the tree -by name
 * 
 * @param node 
 * @return true 
 * @return false 
 */
bool OrgChart::isNodeExists(const string& node)
{
    return (_mapNameNodes.count(node) != 0);
}

/**
 * @brief is node exists by name and location
 * 
 * @param node 
 * @return true 
 * @return false 
 */
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

/**
 * @brief reset the tree
 * 
 */
void OrgChart::restartTree()
{
    _mapNameNodes.clear();
    _levelOrder.clear();
    _reverseOrder.clear();
    _preOrder.clear();
    _root = Node();
}

/**
 * @brief this function is for the iterators - it sets the vectors that is been sent to the iterator - save thier vectors
 * 
 */
void OrgChart::setAllOrders()
{
    vector<vector<Node*>> detailed = levelOrderDetailed();
    setLevelOrderVect(detailed);
    setLevelOrderReverseVect(detailed);
    setPreorderNodes();
}

/**
 * @brief set the order level vector by using queue style - by using function that gives the orders
 * 
 * @param detailed 
 */
void OrgChart::setLevelOrderVect(const vector<vector<Node*>>& detailed)
{
    _levelOrder.clear();
    for (const vector<Node*>& line : levelOrderDetailed())
    {
        _levelOrder.insert(_levelOrder.end(), line.begin(), line.end());
    }
    _levelOrder.push_back(nullptr);
}

/**
 * @brief set the reversed order level vector by using queue style - by using function that gives the orders
 * 
 * @param detailed 
 */
void OrgChart::setLevelOrderReverseVect(const vector<vector<Node*>>& detailed)
{
    _reverseOrder.clear();
    for (const vector<Node*>& line : levelOrderDetailed())
    {
        // push at the beginning the current level
        _reverseOrder.insert(_reverseOrder.begin(), line.begin(), line.end());
    }
    _reverseOrder.push_back(nullptr);
}

/**
 * @brief this function returns the nodes by their levels
 * 
 * @return vector<vector<Node*>> 
 */
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
            if (children.empty())
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

/**
 * @brief set the vector of the pre order
 * 
 */
void OrgChart::setPreorderNodes()
{
    _preOrder.clear();
    // call the recursive function
    setPreorderRec(_root);
    // set the last as the end
    _preOrder.push_back(nullptr);

}

// by given vector create the preorder vector
void OrgChart::setPreorderRec(Node& head)
{
    // if head doesn't exist then it is leaf
    if (!isNodeExists(head))
    {
        return;
    }
    // preorder pushing
    _preOrder.push_back(&head);
    // set all the kids to the recursive call
    for (Node* node : getChildrenPointers(head))
    {
        if (node == nullptr)
        {
            continue;
        }
        setPreorderRec(*node);
    }
}

/**
 * @brief  by given node it returns the vector of its children pointers
 * 
 * @param node 
 * @return vector<Node*> 
 */
vector<Node*> OrgChart::getChildrenPointers(Node& node)
{
    vector<Node*> retVec;
    // return empty if not in the tree
    if (!isNodeExists(node))
    {
        return (retVec);
    }
    string name = node.getData();
    unsigned int index = node.getIndex();
    // run on all of the children and set to the vector (their addresses)
    for (unsigned int i = 0; i < _mapNameNodes[node.getData()][index].size(); i++)
    {
        Node* currNode = &(_mapNameNodes[node.getData()][index][i]);
        retVec.push_back(currNode);
    }
    
    return (retVec);
}

/**
 * @brief using recursive skills the fnction returns a good org flow
 * 
 * @param head 
 * @param s 
 * @return string 
 */
string OrgChart::toString(Node& head, const string& s)
{
    string retStr;
    // if leaf - add nothing
    if (!isNodeExists(head))
    {
        return "";
    }
    // add the current node
    retStr += head.getData();
    
    // get the children pointer
    auto v = getChildrenPointers(head);
    
    // if empty - then leaf set new line and set the flow lines from before
    if (v.empty())
    {
        retStr += "\n ";
        retStr += (s + "\n") + " ";
        return (retStr);
    }
    // set the flow by its number
    retStr += string(SPACE_NUM, '-');

    // take one less beacuse its peint with offset
    unsigned int spaceCalc = head.getData().size() + SPACE_NUM - 1;
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

        // according to the jump decide if space or |
        if (i < v.size()-1)
        {
            st += "|";
        }
        else
        {
            st += " ";
        }

        // add the result to the cuurent working string
        retStr += toString(*node, st);
        
        i++;

    }
    
    return retStr;
}

/**
 * @brief return the orgchart as a org flow
 * 
 * @return string 
 */
string OrgChart::toString()
{
    return toString(_root);
}

//begin and end parts

OrgChart::Iterator OrgChart::begin()
{
    return OrgChart::Iterator(*this, _levelOrder);
}

OrgChart::Iterator OrgChart::end()
{
    // set the end to be true
    return OrgChart::Iterator(*this, _levelOrder, true);
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

OrgChart::reverse_iterator OrgChart::reverse_order()
{
    return end_reverse_order();
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



OrgChart::Iterator::Iterator(const OrgChart& org, const vector<Node*>& nodes, bool isEnd) : _org(org), _vectNode(nodes)
{
    //take the size as the last index
    if (nodes.empty())
    {
        throw runtime_error("cannot be empty");
    }
    _index = isEnd ? _vectNode.size() - 1 : 0;
}

OrgChart::Iterator& OrgChart::Iterator::operator++()
{
    // if over the top then set it was wrong
    if (_index >= _vectNode.size())
    {
        throw runtime_error("unresticked area");
    }
    _index++;
    return (*this);
}

/**
 * @brief get the referance of the string
 * 
 * @return string& 
 */
string& OrgChart::Iterator::operator*() const
{
    return _vectNode[_index]->getData();
}

/**
 * @brief cheack if other if not the same
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool OrgChart::Iterator::operator!=(const Iterator& other)
{
    return !(*this == other);
}

/**
 * @brief chaeck if the iterator is the same
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool OrgChart::Iterator::operator==(const Iterator& other)
{
    if (&_vectNode != &(other._vectNode))
    {
        throw runtime_error("not the same data structure");
    }
    return (_index == other._index &&
            (_index < this->_vectNode.size() && other._index < other._vectNode.size()) && 
            _vectNode[_index] == other._vectNode[_index]);
}

/**
 * @brief return its dtring pointer as const - so no change can be made
 * 
 * @return const string* 
 */
const string* OrgChart::Iterator::operator->()
{
    return &(_vectNode[_index]->getData());
}



/******************************* level_iterator class *******************************/

/**
 * @brief Construct a new OrgChart::level_iterator::level_iterator object
 * set the iterator with the level order vector
 * 
 * @param org 
 * @param isEnd 
 */
OrgChart::level_iterator::level_iterator(OrgChart& org, bool isEnd) : Iterator(org, org._levelOrder, isEnd)
{

}

/******************************* reverse_iterator class *******************************/


/**
 * @brief Construct a new OrgChart::reverse_iterator::reverse_iterator object
 * set the reverswith the org vector
 * 
 * @param org 
 * @param isEnd 
 */
OrgChart::reverse_iterator::reverse_iterator(OrgChart& org, bool isEnd) : Iterator(org, org._reverseOrder, isEnd)
{
    
}


/******************************* preorder_iterator class *******************************/

/**
 * @brief Construct a new OrgChart::preorder_iterator::preorder_iterator object
 * set the preorder with the org preorder vector
 * 
 * @param org 
 * @param isEnd 
 */
OrgChart::preorder_iterator::preorder_iterator(OrgChart& org, bool isEnd) : Iterator(org, org._preOrder, isEnd)
{

}








