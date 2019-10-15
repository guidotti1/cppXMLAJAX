#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define XML_USE_STL
#include "xmlParser.h"

using namespace std;


int main (int argc, char ** argv) {

    string gameFile = "testGame.xml";

    // this opens and parses the correct XML file:
    XMLNode xMainNode=XMLNode::openFileHelper(gameFile.c_str(),"map");
    int i = 0;
    // get the first room node
    XMLNode roomNode=xMainNode.getChildNode(i++);

    do {
    XMLNode itemNode = roomNode.getChildNode("item", 0);

    XMLNode item2Node = roomNode.getChildNode("item", 1);

    string item1, item2 = "default";

    XMLNode item1NameNode = itemNode.getChildNode("name");
    item1 = item1NameNode.getText();

    XMLNode item2NameNode = item2Node.getChildNode("name");
    item2 = item2NameNode.getText();


    cout << "item1" << item1 << endl;
    cout << "item2" << item2 << endl;

    roomNode=xMainNode.getChildNode(i++);
    } while (!roomNode.isEmpty());

    cout << endl;
    return 0;
}
