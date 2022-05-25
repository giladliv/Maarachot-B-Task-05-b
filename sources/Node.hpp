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
            // return data of string
            string& getData() { return _name; }
            // return index if the node
            unsigned int getIndex() const { return _index; }
            
            
        private:
            string _name;
            unsigned int _index;
    };
    
}
