#include "doctest.h"
#include "sources/OrgChart.hpp"

using namespace std;
using ariel::OrgChart;

TEST_CASE("bad organization build")
{
    OrgChart organization;

    CHECK_THROWS(organization.add_sub("Hadar", "Gilad"));
    CHECK_THROWS(organization.add_sub("Gilad", "Hadar"));
    
    CHECK_NOTHROW(organization.add_root("Hadar"));
    CHECK_THROWS(organization.add_sub("Gilad", "Hadar"));
    CHECK_NOTHROW(organization.add_sub("Hadar", "Gilad"));
    CHECK_NOTHROW(organization.add_sub("Hadar", "Gilad"));
    CHECK_NOTHROW(organization.add_sub("Hadar", "G"));

    CHECK_NOTHROW(organization.add_root("Gilad"));
    CHECK_THROWS(organization.add_sub("Hadar", "Gilad"));
    CHECK_NOTHROW(organization.add_sub("Gilad", "Hadar"));
    
}


TEST_CASE("good level iterator and regular")
{
    OrgChart organization;
    organization.add_root("jack");
    
    organization.add_sub("jack", "vika")
                .add_sub("jack", "tomer")
                .add_sub("jack", "ami");
    
    organization.add_sub("vika", "noam")
                .add_sub("vika", "mor");

    organization.add_sub("noam", "gilad")
                .add_sub("noam", "daniel")
                .add_sub("noam", "alex")
                .add_sub("noam", "nir");
    
    organization.add_sub("mor", "anton")
                .add_sub("mor", "nikol")
                .add_sub("mor", "arthur");
    
    organization.add_sub("tomer", "hai")
                .add_sub("tomer", "avia")
                .add_sub("tomer", "hadar");

    organization.add_sub("ami", "shir")
                .add_sub("ami", "ariel");

    vector<string> levelOrder ={"jack", 
                                "vika", "tomer", "ami",
                                "noam", "mor", "hai", "avia", "hadar", "shir", "ariel",
                                "gilad", "daniel", "alex", "nir", "anton", "nikol", "arthur"};

    auto it = organization.begin_level_order();                            
    for (unsigned int i = 0; i < levelOrder.size(); ++it, i++)
    {
        CHECK_EQ((*it), levelOrder[i]);
    }

    unsigned int i = 0;
    for (string name: organization)
    {
        if (i == levelOrder.size())
        {
            break;
        }
        CHECK_EQ(name, levelOrder[i++]);
    }
}

TEST_CASE("good reverse")
{
    OrgChart organization;
    organization.add_root("jack");
    
    organization.add_sub("jack", "vika")
                .add_sub("jack", "tomer")
                .add_sub("jack", "ami");
    
    organization.add_sub("vika", "noam")
                .add_sub("vika", "mor");

    organization.add_sub("noam", "gilad")
                .add_sub("noam", "daniel")
                .add_sub("noam", "alex")
                .add_sub("noam", "nir");
    
    organization.add_sub("mor", "anton")
                .add_sub("mor", "nikol")
                .add_sub("mor", "arthur");
    
    organization.add_sub("tomer", "hai")
                .add_sub("tomer", "avia")
                .add_sub("tomer", "hadar");

    organization.add_sub("ami", "shir")
                .add_sub("ami", "ariel");

    vector<string> levelOrder ={"jack", 
                                "vika", "tomer", "ami",
                                "noam", "mor", "hai", "avia", "hadar", "shir", "ariel",
                                "gilad", "daniel", "alex", "nir", "anton", "nikol", "arthur"};

    reverse(levelOrder.begin(), levelOrder.end());
                       
    auto it = organization.begin_reverse_order();                            
    for (unsigned int i = 0; i < levelOrder.size(); ++it, i++)
    {
        CHECK_EQ((*it), levelOrder[i]);
    }

    int j = levelOrder.size() - 1;

    for (string name: organization)
    {
        if (j >= 0)
        {
            break;
        }
        CHECK_EQ(name, levelOrder[(unsigned int)j]);
        j++;
    }
}