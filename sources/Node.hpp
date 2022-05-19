#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace ariel
{
    class Node
    {
        public:
            Node();
            Node(const string& str, unsigned int index);
            ~Node();
            string& getData() { return _name; }
            unsigned int getIndex() const { return _index; }
            Node& operator=(const Node& other);
            
            
        private:
            string _name;
            unsigned int _index;
            //vector<Node*> _children;
    };
    
}
