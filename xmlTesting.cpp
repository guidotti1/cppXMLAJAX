#include <string>
#include <iostream>
#include <sstream>

#define XML_USE_STL
#include "xmlParser.h"

using namespace std;

int main (int argc, char ** argv) {

  string gameFile = "testGame.xml";
/*
  if (argc != 2) {
    cout << "Usage: " << argv[0] << "author" << endl;
    exit(2);
  }
  string author = argv[1];

  cout << "Author: " << author << endl;
*/
  // this opens and parses the correct XML file:
  XMLNode xMainNode=XMLNode::openFileHelper(bookFile.c_str(),"map");
  int i = 0;
  // get the first book node
  XMLNode roomNode=xMainNode.getChildNode(i++);
  do {
    // Get the author node
    XMLNode nameNode = roomNode.getChildNode("name");
    // get the author last names
    string name = nameNode.getText();
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
    cout << "name is : " << name << endl;
    roomNode=xMainNode.getChildNode(i++);
  } while (!roomNode.isEmpty());

  cout << endl;
  return 0;
}
