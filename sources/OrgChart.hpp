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
            void restartTree();
            unsigned int addNodeToMap(const string& name);
            vector<Node*> levelOrderVect();
            vector<Node*> levelOrderReverseVect();
            vector<vector<Node*>> levelOrderDetailed();
            bool isNodeExists(string node);
            bool isNodeExists(Node& node);
            vector<Node*> getChildrenPointers(Node& node);


        public:
            OrgChart();
            ~OrgChart();
            OrgChart& add_root(const string& name);
            OrgChart& add_sub(const string& head, const string& name);

            friend ostream& operator<<(ostream& os, OrgChart& org);

            class level_iterator : public iterator<output_iterator_tag, string>
            {
                public:
                    level_iterator(OrgChart& org, vector<Node*> nodes, bool isEnd = false);
                    level_iterator& operator++();
                    string operator*() const;
                    bool operator!=(const level_iterator& other);
                    const string* operator->();
                    
                protected:
                    unsigned int _index;
                    vector<Node*> _vectNode;
                    OrgChart& _org;

            };

            class Iterator : public level_iterator
            {
                public:
                    Iterator(OrgChart& org, vector<Node*> nodes, bool isEnd = false);

            };

            class reverse_iterator : public level_iterator
            {
                public:
                    reverse_iterator(OrgChart& org, vector<Node*> nodes, bool isEnd = false);
                
                private:

            };

            class preorder_iterator
            {
                public:
                    preorder_iterator();
                    preorder_iterator& operator++();
                    string operator*() const;
                    bool operator!=(const preorder_iterator& other);
                    string* operator->();
                
                private:

            };

            Iterator begin();
            Iterator end();
            level_iterator begin_level_order();
            level_iterator end_level_order();
            reverse_iterator begin_reverse_order();
            reverse_iterator end_reverse_order();
            preorder_iterator begin_preorder();
            preorder_iterator end_preorder();
            
    };
    
}
