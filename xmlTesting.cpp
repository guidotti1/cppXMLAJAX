#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define XML_USE_STL
#include "xmlParser.h"

using namespace std;



class turnon
{
public :
    turnon();
    turnon(XMLNode node);

private:
    string print;
    string action;
};


class item
{
public:
    item();
    item(XMLNode node);
    //void drop();
    //void take();
    //void read();
    //void turnOn();
    //void putInContainer(); //probably should pass the current owner and new owner (e.g. user to container)
private:
    string name;
    string writing;
    string status;
    string owner;
    turnon itemTurnon;
    //bool on;
    //trigger itemTrigger;
};

class trigger
{
public:
    trigger();
    trigger(XMLNode node);

private :
    string type;
    string command;
    string print;
    string action;

};

class room
{
public :
    room();
    room(XMLNode node);
    getItems(XMLNode node);
    getTriggers(XMLNode node);


private :
    string name;
    string description;
    string type;
    vector<item> items;
    vector<trigger> triggers;
};




//room getRoomInformation(XMLNode);
//void getItems(XMLNode, vector<item> & items);
//void getTriggers(XMLNode);
void getBorders (XMLNode);
void getContainers(XMLNode);
void getCreatures(XMLNode);
void getCondition(XMLNode node);
void getAttack(XMLNode node);


int main (int argc, char ** argv) {

    string gameFile = "testGame.xml";

    // this opens and parses the correct XML file:
    XMLNode xMainNode=XMLNode::openFileHelper(gameFile.c_str(),"map");
    int i = 0;
    // get the first room node
    XMLNode roomNode=xMainNode.getChildNode(i++);


    do {


    room newRoom(roomNode);
    //get information for room
    //newRoom = getRoomInformation(roomNode);
    //get information for items in the room
    newRoom.getItems(roomNode);
    //get information for triggers in the room
    getTriggers(roomNode);
    //get information for borders in the room
    getBorders(roomNode);
    //get information for containers in the room
    getContainers(roomNode);
    //get information for creatures in the room
    getCreatures(roomNode);

    roomNode=xMainNode.getChildNode(i++);
    } while (!roomNode.isEmpty());

    cout << endl;
    return 0;
}

room::room(XMLNode node)
{
    name, description, type = "";
    //room information
    //room type
    XMLNode roomTypeNode = node.getChildNode("type");
    if (!roomTypeNode.isEmpty())
        {
        type = roomTypeNode.getText();
        }

    // Get the room name
    XMLNode nameNode = node.getChildNode("name");
    if (!nameNode.isEmpty())
        {
        name = nameNode.getText();
        }

    //Get the room description
    XMLNode descriptionNode = node.getChildNode("description");
    if (!descriptionNode.isEmpty())
        {
        description = descriptionNode.getText();
        }

    cout << "(room information)" << endl;
    cout << "Name of the room is : " << name << endl;
    cout << "Description of the room is : " << description << endl;
    cout << "Type of the room is : " <<  type << endl;

    getItems(node);
    getTriggers(node);

}

item::item(XMLNode node)
{
    name, writing, status, owner = "";

    XMLNode itemNameNode = node.getChildNode("name");
    if (!itemNameNode.isEmpty())
        {
        name = itemNameNode.getText();
        }

    XMLNode itemWritingNode = node.getChildNode("writing");
    if(!itemWritingNode.isEmpty())
        {
        writing = itemWritingNode.getText();
        }

    XMLNode itemStatusNode = node.getChildNode("status");
    if (!itemStatusNode.isEmpty())
        {
        status = itemStatusNode.getText();
        }

    cout << "(item information)" << endl;
    cout << "Item name : " << name<< endl;
    cout << "Item writing : " << writing << endl;
    cout << "Item status : " << status  << endl;
    cout << "Item owner : " << owner << endl;

    //turnon information for the item
    XMLNode turnonNode = node.getChildNode("turnon");
    turnon itemTurnon(turnonNode);
}

turnon::turnon(XMLNode node)
{
    if (!node.isEmpty())
        {
        string print, action = "";

        XMLNode turnonPrintNode = node.getChildNode("print");
        if (!turnonPrintNode.isEmpty())
            {
            print  = turnonPrintNode.getText();
            }

        XMLNode turnonActionNode = node.getChildNode("action");
        if(!turnonActionNode.isEmpty())
            {
            action = turnonActionNode.getText();
            }

        cout << "(item turnon information)" << endl;
        cout << "Item turnon print : " << print << endl;
        cout << "Item turnon action : " << action << endl;
        }
}

room::getItems(XMLNode node)
{
    int numberItems = node.nChildNode("item");
    for (int nItems = 0; nItems < numberItems; nItems++)
        {
        XMLNode itemNode = node.getChildNode("item", nItems);
        item newItem(itemNode);
        items.push_back(newItem);
        }
}


trigger::trigger(XMLNode node)
{
    type, command, action, print = "";

    XMLNode typeNode = node.getChildNode("type");
    if (!typeNode.isEmpty())
        {
        type = typeNode.getText();
        }

    XMLNode commandNode = node.getChildNode("command");
    if (!commandNode.isEmpty())
        {
        command = commandNode.getText();
        }

    XMLNode printNode = node.getChildNode("print");
    if (!printNode.isEmpty())
        {
        print = printNode.getText();
        }

    XMLNode actionNode = node.getChildNode("action");
    if (!actionNode.isEmpty())
        {
        action = actionNode.getText();
        }

    cout << "(trigger information)" << endl;
    cout << "type : " << triggerType << endl;
    cout << "command : " << command << endl;
    cout << "print : " << triggerPrint << endl;
    cout << "action : " << action << endl;

    cout << "condition information for trigger" << endl;
    getCondition(triggerNode);
}

room::getTriggers(XMLNode node)
{
    int numberTriggers = node.nChildNode("trigger");
    for (int nTriggers = 0; nTriggers < numberTriggers; nTriggers++)
        {
            XMLNode triggerNode=node.getChildNode("trigger", nTriggers);
            trigger newTrigger(triggerNode);
            triggers.push_back(newTrigger);
        }
}

/*
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

void getContainers(XMLNode node)
{
    int numberContainers = node.nChildNode("container");
    for (int nContainers = 0; nContainers < numberContainers; nContainers++)
        {
        XMLNode containerNode = node.getChildNode("container", nContainers);
        string containerName, containerStatus, containerAccept= "";

        XMLNode containerNameNode = containerNode.getChildNode("name");
        if (!containerNameNode.isEmpty())
            {
            containerName = containerNameNode.getText();
            }

        XMLNode containerStatusNode = containerNode.getChildNode("status");
        if (!containerStatusNode.isEmpty())
            {
            containerStatus = containerStatusNode.getText();
            }

        XMLNode containerAcceptNode = containerNode.getChildNode("accept");
        if (!containerAcceptNode.isEmpty())
            {
            containerAccept = containerAcceptNode.getText();
            }

        cout << "(container information)"<<endl;
        cout << "container name : " << containerName << endl;
        cout << "container status : " << containerStatus << endl;
        cout << "container accept :" << containerAccept << endl;

        cout << "(items in container)" << endl;
        getItems(containerNode);

        cout << "(triggers for container)" << endl;
        getTriggers(containerNode);
        }

}

void getCreatures(XMLNode node)
{
    int numberCreatures = node.nChildNode("creature");
    for (int nCreatures = 0; nCreatures < numberCreatures; nCreatures++)
        {
        XMLNode creatureNode = node.getChildNode("creature", nCreatures);
        string creatureName, creatureVulnerability ="";

        XMLNode creatureNameNode = creatureNode.getChildNode("name");
        if (!creatureNameNode.isEmpty())
            {
            creatureName = creatureNameNode.getText();
            }

        XMLNode creatureVulnerabilityNode = creatureNode.getChildNode("vulnerability");
        if (!creatureVulnerabilityNode.isEmpty())
            {
            creatureVulnerability = creatureVulnerabilityNode.getText();
            }

        cout << "(creature information)"<<endl;
        cout << "creature name : "<< creatureName << endl;
        cout << "creature vulnerability : " << creatureVulnerability << endl;
        cout << "attack for creature : " << endl;
        getAttack(creatureNode);
        cout << "trigger for creature : " << endl;
        getTriggers(creatureNode);
        }
}

void getCondition(XMLNode node)
{
    int numberConditions = node.nChildNode("condition");
    for (int nConditions = 0; nConditions < numberConditions; nConditions++)
        {
            XMLNode conditionNode = node.getChildNode("condition", nConditions);
            string object, status, has, owner = "";


            XMLNode hasNode = conditionNode.getChildNode("has");
            if (!hasNode.isEmpty())
                {
                has = hasNode.getText();
                }

            XMLNode ownerNode = conditionNode.getChildNode("owner");
            if (!ownerNode.isEmpty())
                {
                owner = ownerNode.getText();
                }

            XMLNode objectNode = conditionNode.getChildNode("object");
            if (!objectNode.isEmpty())
                {
                object = objectNode.getText();
                }

            XMLNode statusNode = conditionNode.getChildNode("status");
            if (!statusNode.isEmpty())
                {
                status = statusNode.getText();
                }

            cout << "(condition information)"<<endl;
            cout << "owner : " << owner << endl;
            cout << "has : " << has << endl;
            cout << "object : " << object << endl;
            cout << "status : " << status << endl;
            }
}

void getAttack(XMLNode node)
{
        XMLNode attackNode = node.getChildNode("attack");
        cout << "condition for attack " <<endl;
        getCondition(attackNode);

        string print ="";
        XMLNode printNode = attackNode.getChildNode("print");
        if (!printNode.isEmpty())
            {
            print = printNode.getText();
            }
        int numberActions = attackNode.nChildNode("attack");
        cout << "actions for attack " << endl;
        for (int nActions = 0; nActions < numberActions; nActions ++)
            {
            XMLNode actionNode = node.getChildNode("action", nActions);
            string actionInfo = actionNode.getText();
            cout << "actionInfo " << actionInfo << endl;
            }



}

*/
