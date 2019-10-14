#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define XML_USE_STL
#include "xmlParser.h"

using namespace std;

class Room
{
public :
    Room();
    Room(string nameInit, string descriptionInit, string statusInit, string typeInit);

private :

};

class Item
{
public:
    Item();
    Item(string nameInit, string writingInit, string statusInit, string ownerInit);
    void drop();
    void take();
    void read();
    void turnOn();
    void putInContainer(); //probably should pass the current owner and new owner (e.g. user to container)


private:
    string name;
    string writing;
    string status;
    string owner;
    bool on;
    //trigger itemTrigger;
};


int main (int argc, char ** argv) {

  string gameFile = "testGame.xml";

  // this opens and parses the correct XML file:
  XMLNode xMainNode=XMLNode::openFileHelper(gameFile.c_str(),"map");
  int i = 0;
  // get the first room node
  XMLNode roomNode=xMainNode.getChildNode(i++);
  do {
    // Get the room name
    XMLNode nameNode = roomNode.getChildNode("name");
    string name = nameNode.getText();

    //Get the room description
    XMLNode descriptionNode = roomNode.getChildNode("description");
    string description = descriptionNode.getText();

    /*
    XMLNode itemNode = roomNode.getChildNode("item");
    string itemName = itemNode.getText();

    XMLNode item2Node = roomNode.getChildNode("item");
    string item2Name = item2Node.getText();
    */

    //XMLNode triggerNode = roomNode.getChildNode("trigger");
    int j = 0;
    XMLNode triggerNode=xMainNode.getChildNode("trigger");
    do
        {
        XMLNode typeNode = triggerNode.getChildNode("type");
        string type = typeNode.getText();

        XMLNode commandNode = triggerNode.getChildNode("command");
        string command = commandNode.getText();

        XMLNode printNode = triggerNode.getChildNode("print");
        string print = printNode.getText();

        cout << "type : " << type << endl;
        cout << "command : " << command << endl;
        cout << "print : " << print << endl;
        //triggerNode = roomNode.getChildNode(j++);
        } while (!triggerNode.isEmpty());


    /*
    string lname = authorNode.getAttribute("lname");
    // See if there is a partial match between the
    // search string and the author last name
    if (lname.find(author)!=string::npos) {
      // Get the ISBN
      string isbn10 = bookNode.getAttribute("isbn10");
      // Get the author name
      string author = authorNode.getText();
      // Get the title
      XMLNode titleNode = bookNode.getChildNode("title");
      string title = titleNode.getText();
      // Get the Publisher
      XMLNode pubNode = bookNode.getChildNode("publisher");
      string publisher = pubNode.getText();
      // Get the Price (in one line)
      string price = bookNode.getChildNode("price").getText();

      cout << "Title: " << title << endl;
      cout << "Author: " << author << endl;
      cout << "Publisher: " << publisher << endl;
      cout << "ISBN10: " << isbn10 << endl;
      cout << "Price: " << price << endl << endl;
    }
    */
    cout << "Name of the room is : " << name << endl;
    cout << "Description of the room is : " << description << endl;
    //cout << "Item in the room : " << itemName << endl;
    //cout << "Item2 name : " << item2Name << endl;
    roomNode=xMainNode.getChildNode(i++);
  } while (!roomNode.isEmpty());

  cout << endl;
  return 0;
}
