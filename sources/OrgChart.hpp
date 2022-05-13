#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

namespace ariel
{
    class OrgChart
    {
        public:
            OrgChart();
            ~OrgChart();
            OrgChart& add_root(string name);
            OrgChart& add_sub(string head, string name);

            friend ostream& operator<<(ostream& os, const OrgChart& org);

            class iterator
            {
                public:
                    iterator();
                    iterator& operator++();
                    string operator*() const;
                    bool operator!=(const iterator& other);
                    string* operator->();
                
                private:

            };
            
            class level_iterator
            {
                public:
                    level_iterator();
                    level_iterator& operator++();
                    string operator*() const;
                    bool operator!=(const level_iterator& other);
                    string* operator->();
                    
                private:

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

        private:
            
    };
    
}
