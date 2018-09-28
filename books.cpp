#include <iostream>
// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

//#include "pstream.h"
#include <string>
#include <iostream>
#include <algorithm>

#define XML_USE_STL
#include "xmlParser.h"

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

ofstream logFile;

int main() {
  Cgicc cgi;    // Ajax object    
  string bookFile = "/home/class/SoftDev/cppXMLAJAX/books.xml";

  // Create AJAX objects to recieve information from web page.
  form_iterator authorIt = cgi.getElement("author");
  string author = **authorIt;
  // Normalize string to lower case
  transform(author.begin(), author.end(), author.begin(), ::tolower);
  
  // Debug to file example
  logFile.open("/tmp/skon.log",ios::out | ios::app);
  logFile << "Got: " + author;;
  logFile.close();  
  
  // this opens and parses the correct XML file:
  XMLNode xMainNode=XMLNode::openFileHelper(bookFile.c_str(),"library");
  int i = 0;

  // output required message for AJAX
  cout << "Content-Type: text/plain\n\n";

  // get the first book node
  XMLNode bookNode=xMainNode.getChildNode(i++);
  do {
    // Get the author node
    XMLNode authorNode = bookNode.getChildNode("author");
    // get the author last name
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
      
      cout << "<p><br />Title: " << title;
      cout << "<br />Author: " << author;
      cout << "<br >Publisher: " << publisher;
      cout << "<br />ISBN10: " << isbn10;
      cout << "<br />Price: " << price << "</p>" << endl;
    }
    bookNode=xMainNode.getChildNode(i++);
  } while (!bookNode.isEmpty());
  
return 0;
}


