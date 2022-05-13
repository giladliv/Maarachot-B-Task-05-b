#include "OrgChart.hpp"

using ariel::OrgChart;

/******************************* OrgChart part *******************************/

OrgChart::OrgChart()
{
}

OrgChart::~OrgChart()
{

}

OrgChart& OrgChart::add_root(string name)
{
    return (*this);
}

OrgChart& OrgChart::add_sub(string head, string name)
{
    return (*this);
}

ostream& ariel::operator<<(ostream& os, const OrgChart& org)
{
    return os;
}

//begin and end parts

OrgChart::iterator OrgChart::begin()
{
    return OrgChart::iterator();
}

OrgChart::iterator OrgChart::end()
{
    return OrgChart::iterator();
}


OrgChart::level_iterator OrgChart::begin_level_order()
{
    return OrgChart::level_iterator();
}

OrgChart::level_iterator OrgChart::end_level_order()
{
    return OrgChart::level_iterator();
}

OrgChart::reverse_iterator OrgChart::begin_reverse_order()
{
    return OrgChart::reverse_iterator();
}

OrgChart::reverse_iterator OrgChart::end_reverse_order()
{
    return OrgChart::reverse_iterator();
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


OrgChart::iterator::iterator()
{

}

OrgChart::iterator& OrgChart::iterator::operator++()
{
    return (*this);
}

string OrgChart::iterator::operator*() const
{
    return "";
}

bool OrgChart::iterator::operator!=(const iterator& other)
{
    return (false);
}

string* OrgChart::iterator::operator->()
{
    return nullptr;
}



/******************************* level_iterator class *******************************/


OrgChart::level_iterator::level_iterator()
{

}

OrgChart::level_iterator& OrgChart::level_iterator::operator++()
{
    return (*this);
}

string OrgChart::level_iterator::operator*() const
{
    return "";
}

bool OrgChart::level_iterator::operator!=(const level_iterator& other)
{
    return (false);
}

string* OrgChart::level_iterator::operator->()
{
    return nullptr;
}



/******************************* reverse_iterator class *******************************/


OrgChart::reverse_iterator::reverse_iterator()
{

}

OrgChart::reverse_iterator& OrgChart::reverse_iterator::operator++()
{
    return (*this);
}

string OrgChart::reverse_iterator::operator*() const
{
    return "";
}

bool OrgChart::reverse_iterator::operator!=(const reverse_iterator& other)
{
    return (false);
}

string* OrgChart::reverse_iterator::operator->()
{
    return nullptr;
}



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








