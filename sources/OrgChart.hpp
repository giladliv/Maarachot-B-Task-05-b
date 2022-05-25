#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include "Node.hpp"

using namespace std;
using ariel::Node;

namespace ariel
{
    class OrgChart
    {
        private:
            Node _root;
            unordered_map<string, vector<vector<Node>>> _mapNameNodes;
            vector<Node*> _preOrder;
            vector<Node*> _levelOrder;
            vector<Node*> _reverseOrder;

            void restartTree();
            unsigned int addNodeToMap(const string& name);
            void setAllOrders();
            
            void setLevelOrderVect(const vector<vector<Node*>>& detailed);
            void setLevelOrderReverseVect(const vector<vector<Node*>>& detailed);
            vector<vector<Node*>> levelOrderDetailed();
            void setPreorderNodes();
            void setPreorderRec(Node& head);
            bool isNodeExists(string node);
            bool isNodeExists(Node& node);
            vector<Node*> getChildrenPointers(Node& node);


        public:
            OrgChart();
            ~OrgChart();
            OrgChart& add_root(const string& name);
            OrgChart& add_sub(const string& head, const string& name);
            string toString(Node& head, string s = "");
            friend ostream& operator<<(ostream& os, OrgChart& org);

            class Iterator : public iterator<forward_iterator_tag, string>
            {
                public:
                    Iterator(OrgChart& org, const vector<Node*>& nodes = vector<Node*>(), bool isEnd = false);
                    Iterator& operator++();
                    string& operator*() const;
                    bool operator!=(const Iterator& other);
                    bool operator==(const Iterator& other);
                    const string* operator->();
                    
                protected:
                    unsigned int _index;
                    const vector<Node*>& _vectNode;
                    OrgChart& _org;

            };
            
            class level_iterator : public Iterator
            {
                public:
                    level_iterator(OrgChart& org, bool isEnd = false);

            };

            class reverse_iterator : public Iterator
            {
                public:
                    reverse_iterator(OrgChart& org, bool isEnd = false);
                

            };

            class preorder_iterator : public Iterator
            {
                public:
                    preorder_iterator(OrgChart& org, bool isEnd = false);
                

            };

            Iterator begin();
            Iterator end();
            level_iterator begin_level_order();
            level_iterator end_level_order();
            reverse_iterator begin_reverse_order();
            reverse_iterator end_reverse_order();
            preorder_iterator begin_preorder();
            preorder_iterator end_preorder();

            // void try_me()
            // {
            //     auto b = begin();
            //     auto e = end_level_order();
            //     cout << (b != e) << endl;
            // }
            
    };
    
}
