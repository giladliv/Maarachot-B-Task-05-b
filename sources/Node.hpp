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
            Node(const string& str);
            Node* addNext(const string& str);
            ~Node();
            string& getData() { return _name; }
            vector<Node*> getNext()  { return (_children); }
            // vector<Node*> _children;
            static void freeAllTree(Node* node);
            
            
        private:
            string _name;
            vector<Node*> _children;
            //vector<Node*> _children;
    };
    
}
