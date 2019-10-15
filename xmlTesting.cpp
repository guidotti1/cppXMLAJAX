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


void getItems(XMLNode);
void getTriggers(XMLNode);
void getBorders (XMLNode);
void getCreatures(XMLNode);
void getContainers(XMLNode);


int main (int argc, char ** argv) {

    string gameFile = "testGame.xml";

    // this opens and parses the correct XML file:
    XMLNode xMainNode=XMLNode::openFileHelper(gameFile.c_str(),"map");
    int i = 0;
    // get the first room node
    XMLNode roomNode=xMainNode.getChildNode(i++);


    do {
    string roomType, name, description = "";

    //room information
    //room type
    XMLNode roomTypeNode = roomNode.getChildNode("type");
    if (!roomTypeNode.isEmpty())
        {
        roomType = roomTypeNode.getText();
        }

    // Get the room name
    XMLNode nameNode = roomNode.getChildNode("name");
    if (!nameNode.isEmpty())
        {
        name = nameNode.getText();
        }

    //Get the room description
    XMLNode descriptionNode = roomNode.getChildNode("description");
    if (!descriptionNode.isEmpty())
        {
        description = descriptionNode.getText();
        }

    cout << "(room information)" << endl;
    cout << "Name of the room is : " << name << endl;
    cout << "Description of the room is : " << description << endl;
    cout << "Type of the room is : " <<  roomType << endl;


    //get information for items in the room
    getItems(roomNode);
    //get information for triggers in the room
    getTriggers(roomNode);
    //get information for borders in the room
    getBorders(roomNode);

    //int numberContainers


    roomNode=xMainNode.getChildNode(i++);
    } while (!roomNode.isEmpty());

    cout << endl;
    return 0;
}


void getItems(XMLNode node)
{
    int numberItems = node.nChildNode("item");
    for (int nItems = 0; nItems < numberItems; nItems++)
        {
            XMLNode itemNode = node.getChildNode("item", nItems);
            string itemName, itemWriting, itemStatus = "";

            XMLNode itemNameNode = itemNode.getChildNode("name");
            if (!itemNameNode.isEmpty())
                {
                itemName = itemNameNode.getText();
                }

            XMLNode itemWritingNode = itemNode.getChildNode("writing");
            if(!itemWritingNode.isEmpty())
                {
                itemWriting = itemWritingNode.getText();
                }

            XMLNode itemStatusNode = itemNode.getChildNode("status");
            if (!itemStatusNode.isEmpty())
                {
                itemStatus = itemStatusNode.getText();
                }

            cout << "(item information)" << endl;
            cout << "Item name : " << itemName << endl;
            cout << "Item writing : " << itemWriting << endl;
            cout << "Item status : " << itemStatus << endl;

            //turnon information for the item
            XMLNode turnonNode = itemNode.getChildNode("turnon");
            if (!turnonNode.isEmpty())
                {
                string turnonPrint, turnonAction = "";

                XMLNode turnonPrintNode = turnonNode.getChildNode("print");
                if (!turnonPrintNode.isEmpty())
                    {
                    turnonPrint = turnonPrintNode.getText();
                    }

                XMLNode turnonActionNode = turnonNode.getChildNode("action");
                if(!turnonActionNode.isEmpty())
                    {
                    turnonAction = turnonActionNode.getText();
                    }

                cout << "(item turnon information)" << endl;
                cout << "Item turnon print : " << turnonPrint << endl;
                cout << "Item turnon action : " << turnonAction << endl;
                }
        }
}

void getTriggers(XMLNode node)
{
    int numberTriggers = node.nChildNode("trigger");
    for (int nTriggers = 0; nTriggers < numberTriggers; nTriggers++)
        {
            XMLNode triggerNode=node.getChildNode("trigger", nTriggers);
            string triggerType, command, triggerPrint = "";

            XMLNode typeNode = triggerNode.getChildNode("type");
            if (!typeNode.isEmpty())
                {
                triggerType = typeNode.getText();
                }

            XMLNode commandNode = triggerNode.getChildNode("command");
                if (!commandNode.isEmpty())
                {
                command = commandNode.getText();
                }

            XMLNode printNode = triggerNode.getChildNode("print");
                if (!printNode.isEmpty())
                {
                triggerPrint = printNode.getText();
                }

            cout << "(trigger information)" << endl;
            cout << "type : " << triggerType << endl;
            cout << "command : " << command << endl;
            cout << "print : " << triggerPrint << endl;

            XMLNode triggerConditionNode = triggerNode.getChildNode("condition");
            if (!triggerConditionNode.isEmpty())
                {
                    string hasCondition, objectCondition, ownerCondition = "";

                    XMLNode hasConditionNode = triggerConditionNode.getChildNode("has");
                    if (!hasConditionNode.isEmpty())
                        {
                        hasCondition = hasConditionNode.getText();
                        }

                    XMLNode objectConditionNode = triggerConditionNode.getChildNode("object");
                    if (!objectConditionNode.isEmpty())
                        {
                        objectCondition = objectConditionNode.getText();
                        }

                    XMLNode ownerConditionNode = triggerConditionNode.getChildNode("owner");
                    if (!ownerConditionNode.isEmpty())
                        {
                        ownerCondition = ownerConditionNode.getText();
                        }

                    cout << "(trigger condition information)" << endl;
                    cout << "has : " << hasCondition << endl;
                    cout << "object : " << objectCondition << endl;
                    cout << "owner : " << ownerCondition << endl;
                }
        }
}

void getBorders (XMLNode node)
{
    int numberBorders = node.nChildNode("border");
    for (int nBorders = 0; nBorders < numberBorders; nBorders++)
        {
        XMLNode borderNode = node.getChildNode("border", nBorders);
        string borderDirection, borderName = "";

        XMLNode borderDirectionNode = borderNode.getChildNode("direction");
        if (!borderDirectionNode.isEmpty())
            {
            borderDirection = borderDirectionNode.getText();
            }

        XMLNode borderNameNode = borderNode.getChildNode("name");
        if (!borderNameNode.isEmpty())
            {
            borderName = borderNameNode.getText();
            }

        cout << "(border information)"<<endl;
        cout << "direction : " << borderDirection << endl;
        cout << "name : " << borderName << endl;
        }
}
//void getCreatures(XMLNode);
//void getContainers(XMLNode);
