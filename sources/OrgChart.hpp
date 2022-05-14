#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Node.hpp"

using namespace std;
using ariel::Node;

namespace ariel
{
    class OrgChart
    {
        private:
            Node* _root;
            unordered_map<string, vector<Node*>> _mapNameNodes;
            void restartTree();
            void addNodeToMap(Node* node);
            static vector<Node*> levelOrderVect(Node* node);

        public:
            OrgChart();
            ~OrgChart();
            OrgChart& add_root(const string& name);
            OrgChart& add_sub(const string& head, const string& name);

            friend ostream& operator<<(ostream& os, OrgChart& org);

            class iterator
            {
                public:
                    iterator();
                    iterator& operator++();
                    string operator*() const;
                    bool operator!=(const iterator& other);
                    string* operator->();
                
                private:
                    unsigned int _index;
                    vector<Node*> _vectNode;

            };
            
            class level_iterator
            {
                public:
                    level_iterator(Node * node, bool isEnd = false);
                    level_iterator& operator++();
                    string operator*() const;
                    bool operator!=(const level_iterator& other);
                    string* operator->();
                    
                private:
                    unsigned int _index;
                    vector<Node*> _vectNode;

            };

            class reverse_iterator
            {
                public:
                    reverse_iterator();
                    reverse_iterator& operator++();
                    string operator*() const;
                    bool operator!=(const reverse_iterator& other);
                    string* operator->();
                
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

            iterator begin();
            iterator end();
            level_iterator begin_level_order();
            level_iterator end_level_order();
            reverse_iterator begin_reverse_order();
            reverse_iterator end_reverse_order();
            preorder_iterator begin_preorder();
            preorder_iterator end_preorder();
            
    };
    
}
