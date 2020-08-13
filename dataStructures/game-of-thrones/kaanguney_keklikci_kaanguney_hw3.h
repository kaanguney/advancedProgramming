
#include <string>
using namespace std;

/* Begin: code taken and updated from homework3pdf */

struct neighborNode
{
    string neighborName;
    neighborNode * next;
};

struct houseNode
{
    string houseName;
    neighborNode * neighborListHead = NULL;
    houseNode * next;
};

class linkedlist {
    
public:
    
    linkedlist();
    void addHouseNode(string hname);
    void addNeighborNode (string hname, string nname);
    void printAll();
    bool hnExists(string hname);
    bool nnExists(string hname, string nname);
    void deleteAll(); // to deallocate all dynamic data...
    void annexation_add(string annexer, string annexed);
    void delete_annexed(string annexer, string annexed);
    void remove(string annexer, string annexed);
    void change(string annexer, string annexed);
    void removedup();

private:
    
    houseNode * head;
};

/* End: code taken and updated from homework3pdf */
