/**
 * Demo file for the exercise on iterators
 *
 * @author Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "sources/Node.hpp"
using namespace std;

#include "sources/OrgChart.hpp"
using namespace ariel;

int main() {
  OrgChart organization;
  organization.add_root("CEO")
      .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
      .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
      .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
      .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
      .add_sub("COO", "VP_BI");      // Now the VP_BI is subordinate to the COO
      //organization.add_sub("CTO", "GGG").add_sub("GGG", "TTT").add_sub("GGG", "256");

//   cout << organization << endl; /* Prints the org chart in a reasonable format. For example:
// CEO
// |--------|--------|
// CTO      CFO      COO
// |                 |
// VP_SW             VP_BI
//  */

  for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
  {
    cout << (*it) << " " ;
  } // prints: CEO CTO CFO COO VP_SW VP_BI
  cout << endl;
  for (auto it = organization.begin_reverse_order(); it != organization.end_reverse_order(); ++it)
  {
    cout << (*it) << " " ;
  } // prints: VP_SW VP_BI CTO CFO COO CEO
  cout << endl;
  for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: CEO CTO VP_SW CFO COO VP_BI
  cout << endl;
  for (string element : organization)
  { // this should work like level order
    cout << element << " " ;
  } // prints: CEO CTO CFO COO VP_SW VP_BI
  cout << endl;
  // demonstrate the arrow operator:
  for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
  {
    cout << it->size() << " " ;
  } // prints: 3 3 3 3 5 5
  cout << endl;
  // Node a("hello");
  // Node b("World");
  // Node c("Yay");
  // a.addNext(b);
  // a.addNext(c);
  // add(a, "bb");
  // cout << a.getData() << endl;
  // for (unsigned int i = 0; i < a._children.size(); i++)
  // {
  //   cout << a._children[i]->getData() << endl;
  // }
  
  // auto ve = a.getNext();
  // for (unsigned int i = 0; i < ve.size(); i++)
  // {
  //   cout << (ve[i] == a._children[i] ? "true": "false") << endl;
  // }

  OrgChart org;
  org.add_root("CEO")
    .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
    .add_sub("CEO", "CFO");
  
  cout << count(organization.begin_level_order(), organization.end_level_order(), "CTO") << endl;

  std::ostream_iterator<string> out_it(std::cout, ", ");
  copy(organization.begin_level_order(), organization.end_level_order(), out_it);

// //   system("clear");
//   organization.add_root("jack");
    
//   organization.add_sub("jack", "vika")
//               .add_sub("jack", "tomer")
//               .add_sub("jack", "ami");
  
//   organization.add_sub("vika", "noam")
//               .add_sub("vika", "mor");

//   organization.add_sub("noam", "gilad")
//               .add_sub("noam", "daniel")
//               .add_sub("noam", "alex")
//               .add_sub("noam", "nir");
  
//   organization.add_sub("mor", "anton")
//               .add_sub("mor", "nikol")
//               .add_sub("mor", "arthur");
  
//   organization.add_sub("tomer", "hai")
//               .add_sub("tomer", "avia")
//               .add_sub("tomer", "hadar");

//   organization.add_sub("ami", "shir")
//               .add_sub("ami", "ariel");
//   cout << organization << endl;
//   // org.try_me();

}
