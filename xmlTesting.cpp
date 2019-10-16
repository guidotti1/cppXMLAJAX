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

class condition
{
public:
    condition();
    condition(XMLNode node);

private:
    string object;
    string status;
    string has;
    string owner;
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
    condition triggerCondition;

};

class border
{
public:
    border();
    border(XMLNode node);

private :
    string direction;
    string name;

};

class container
{
public:
    container();
    container(XMLNode node);

private :
    string name;
    string status;
    string accept;
    vector<item> items;
    vector<trigger> triggers;

};


class attack
{
public:
    attack();
    attack(XMLNode node);

private:
    condition attackCondition;
    string print;
    vector<string> actions;

};

class creature
{
public :
    creature();
    creature(XMLNode node);
    void getAttack(XMLNode node);

private :
    string name;
    string vulnerability;
    attack creatureAttack;
    trigger creatureTrigger;

};

class room
{
public :
    room();
    room(XMLNode node);
    void getBorders(XMLNode node);
    void getContainers(XMLNode node);
    void getCreatures(XMLNode node);


private :
    string name;
    string description;
    string type;
    vector<item> items;
    vector<trigger> triggers;
    vector<border> borders;
    vector<container> containers;
    vector<creature> creatures;
};

void getItems(XMLNode node, vector<item> & items);
void getTriggers(XMLNode node, vector<trigger> & triggers);


int main (int argc, char ** argv) {

    string gameFile = "testGame.xml";

    // this opens and parses the correct XML file:
    XMLNode xMainNode=XMLNode::openFileHelper(gameFile.c_str(),"map");
    int i = 0;
    // get the first room node
    XMLNode roomNode=xMainNode.getChildNode(i++);


    do {

    //room initializer
    room newRoom(roomNode);
    //get information for containers in the room
    //getContainers(roomNode);
    //get information for creatures in the room
    //getCreatures(roomNode);

    roomNode=xMainNode.getChildNode(i++);
    } while (!roomNode.isEmpty());

    cout << endl;
    return 0;
}

turnon::turnon()
{
    print, action = "";

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

condition::condition()
{
    object, status, owner, has = "";
}

condition::condition(XMLNode node)
{
    object, status, owner, has = "";

    XMLNode hasNode = node.getChildNode("has");
    if (!hasNode.isEmpty())
        {
        has = hasNode.getText();
        }

    XMLNode ownerNode = node.getChildNode("owner");
    if (!ownerNode.isEmpty())
        {
        owner = ownerNode.getText();
        }

    XMLNode objectNode = node.getChildNode("object");
    if (!objectNode.isEmpty())
        {
        object = objectNode.getText();
        }

    XMLNode statusNode = node.getChildNode("status");
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
    turnon tempTurnon(turnonNode);
    itemTurnon = tempTurnon;
}

trigger::trigger()
{
    type, command, action, print = "";

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
    cout << "type : " << type << endl;
    cout << "command : " << command << endl;
    cout << "print : " << print << endl;
    cout << "action : " << action << endl;

    cout << "condition information for trigger" << endl;
    XMLNode conditionNode = node.getChildNode("condition");
    condition tempCondition(conditionNode);
    triggerCondition = tempCondition;
}

border::border(XMLNode node)
{
    direction, name = "";

    XMLNode borderDirectionNode = node.getChildNode("direction");
    if (!borderDirectionNode.isEmpty())
        {
        direction = borderDirectionNode.getText();
        }

    XMLNode borderNameNode = node.getChildNode("name");
    if (!borderNameNode.isEmpty())
        {
        name = borderNameNode.getText();
        }

    cout << "(border information)"<<endl;
    cout << "direction : " << direction << endl;
    cout << "name : " << name << endl;
}

container::container(XMLNode node)
{
    string name, status, accept = "";

    XMLNode containerNameNode = node.getChildNode("name");
    if (!containerNameNode.isEmpty())
        {
        name = containerNameNode.getText();
        }

    XMLNode containerStatusNode = node.getChildNode("status");
    if (!containerStatusNode.isEmpty())
        {
        status = containerStatusNode.getText();
        }

    XMLNode containerAcceptNode = node.getChildNode("accept");
    if (!containerAcceptNode.isEmpty())
        {
        accept = containerAcceptNode.getText();
        }

    cout << "(container information)"<<endl;
    cout << "container name : " << name << endl;
    cout << "container status : " << status << endl;
    cout << "container accept :" << accept << endl;

    cout << "(items in container)" << endl;
    getItems(node, items);

    cout << "(triggers for container)" << endl;
    getTriggers(node, triggers);

}

attack::attack()
{
    print = "";
}

attack::attack(XMLNode node)
{

    print ="";
    XMLNode printNode = node.getChildNode("print");
    if (!printNode.isEmpty())
        {
        print = printNode.getText();
        }
    int numberActions = node.nChildNode("action");
    cout << "actions for attack " << endl;
    for (int nActions = 0; nActions < numberActions; nActions ++)
        {
        XMLNode actionNode = node.getChildNode("action", nActions);
        string actionInfo = actionNode.getText();
        actions.push_back(actionInfo);
        cout << "actionInfo " << actionInfo << endl;
        }

    cout << "condition for attack " <<endl;
    XMLNode conditionNode = node.getChildNode("condition");
    condition tempCondition(conditionNode);
    attackCondition = tempCondition;

}

creature::creature(XMLNode node)
{
    string name, vulnerability ="";

    XMLNode creatureNameNode = node.getChildNode("name");
    if (!creatureNameNode.isEmpty())
        {
        name = creatureNameNode.getText();
        }

    XMLNode creatureVulnerabilityNode = node.getChildNode("vulnerability");
    if (!creatureVulnerabilityNode.isEmpty())
        {
        vulnerability = creatureVulnerabilityNode.getText();
        }

    cout << "(creature information)"<<endl;
    cout << "creature name : "<< name << endl;
    cout << "creature vulnerability : " << vulnerability << endl;
    cout << "attack for creature : " << endl;
    XMLNode attackNode = node.getChildNode("attack");
    attack tempAttack(attackNode);
    creatureAttack = tempAttack;
    cout << "trigger for creature : " << endl;
    XMLNode triggerNode = node.getChildNode("trigger");
    trigger tempTrigger(triggerNode);
    creatureTrigger = tempTrigger;


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

    getItems(node, items);
    getTriggers(node, triggers);
    getBorders(node);
    getContainers(node);
    getCreatures(node);

}

void getItems(XMLNode node, vector<item> & items)
{
    int numberItems = node.nChildNode("item");
    for (int nItems = 0; nItems < numberItems; nItems++)
        {
        XMLNode itemNode = node.getChildNode("item", nItems);
        item newItem(itemNode);
        items.push_back(newItem);
        }
}

void getTriggers(XMLNode node, vector<trigger> & triggers)
{
    int numberTriggers = node.nChildNode("trigger");
    for (int nTriggers = 0; nTriggers < numberTriggers; nTriggers++)
        {
            XMLNode triggerNode=node.getChildNode("trigger", nTriggers);
            trigger newTrigger(triggerNode);
            triggers.push_back(newTrigger);
        }
}


void room::getBorders (XMLNode node)
{
    int numberBorders = node.nChildNode("border");
    for (int nBorders = 0; nBorders < numberBorders; nBorders++)
        {
            XMLNode borderNode = node.getChildNode("border", nBorders);
            border newBorder(borderNode);
            borders.push_back(newBorder);
        }
}


void room::getContainers(XMLNode node)
{
    int numberContainers = node.nChildNode("container");
    for (int nContainers = 0; nContainers < numberContainers; nContainers++)
        {
        XMLNode containerNode = node.getChildNode("container", nContainers);
        container newContainer(containerNode);
        containers.push_back(newContainer);
        }
}


void room::getCreatures(XMLNode node)
{
    int numberCreatures = node.nChildNode("creature");
    for (int nCreatures = 0; nCreatures < numberCreatures; nCreatures++)
        {
        XMLNode creatureNode = node.getChildNode("creature", nCreatures);
        creature newCreature(creatureNode);
        creatures.push_back(newCreature);

        }
}


