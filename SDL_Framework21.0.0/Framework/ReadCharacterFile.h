#ifndef READCHARACTERFILE_H
#define READCHARACTERFILE_H

#include "tinyxml2.h"
#include "AICharacter.h"
#include "Cheese.h"
#include "Trap.h"
#include <vector>

using namespace tinyxml2;

class ReadCharacterFile {
public:
	static bool ReadXML(const char* xmlDoc) {
		XMLDocument doc;
		doc.LoadFile(xmlDoc);
		bool status = doc.Error();
		if (status) {
			std::cout << doc.ErrorIDToName(doc.ErrorID()) << std::endl;
			return false;
		}

		//Repeat a loop until file has reached end
		
		XMLElement* CharacterElement = doc.FirstChildElement("CharacterData");
		//XMLAttribute* 

		//Will only load one character at a time for now. Need to modify the scene to hold multiple objects
		//std::vector<BodyType> loadedCharacters;
		//See if we are looking for the cheese character type. If we are find it's elements
		/*if (dynamic_cast<Cheese*>(loadedCharacter)) {
			XMLElement* ClassElement = doc.FirstChildElement("CheeseData");
			XMLElement* BaseClassElement = ClassElement->FirstChildElement("BodyData");

			loadedCharacter->pos = Vec3(BaseClassElement->FloatAttribute("pos.x"), BaseClassElement->FloatAttribute("pos.y"), BaseClassElement->FloatAttribute("pos.z"));
			loadedCharacter->orientation = BaseClassElement->FloatAttribute("orientation");
			return true;
		}

		//Ignoring mouse for now. Currently not in use needs member variables cleaned up.
		//See if we are looking for the trap character type. If we are find it's elements
		if (dynamic_cast<Trap*>(loadedCharacter)) {
			XMLElement* ClassElement = doc.FirstChildElement("TrapData");
			XMLElement* BaseClassElement = ClassElement->FirstChildElement("BodyData");

			loadedCharacter->pos = Vec3(BaseClassElement->FloatAttribute("pos.x"), BaseClassElement->FloatAttribute("pos.y"), BaseClassElement->FloatAttribute("pos.z"));
			loadedCharacter->orientation = BaseClassElement->FloatAttribute("orientation");
			return true;
		}

		//See if we are looking for the AICharacter character type.If we are find it's elements
		if (dynamic_cast<AICharacter*>(loadedCharacter)) {
			XMLElement* ClassElement = doc.FirstChildElement("AICharacterData");
			XMLElement* BaseClassElement = ClassElement->FirstChildElement("BodyData");
			loadedCharacter->pos = Vec3(BaseClassElement->FloatAttribute("pos.x"), BaseClassElement->FloatAttribute("pos.y"), BaseClassElement->FloatAttribute("pos.z"));
			loadedCharacter->orientation = BaseClassElement->FloatAttribute("orientation");

			XMLElement* AICharElement = BaseClassElement->FirstChildElement("CharData");
			loadedCharacter->health = AICharElement->IntAttribute("health");

			//Create another architecture like this if/if else statements to find what components are being added to the character at startup
			//For now will just have a physics component
			XMLElement* ComponentElement = AICharElement->FirstChildElement("Components");
			Component* componentData;

			XMLElement* PhysicsElement = ComponentElement->FirstChildElement("Physics");
			float mass = PhysicsElement->FloatAttribute("mass");

			XMLElement* LinearElement = PhysicsElement->FirstChildElement("Linear");
			LinearMotion linearData;
			linearData.vel = Vec3(LinearElement->FloatAttribute("vel.x"), LinearElement->FloatAttribute("vel.y"), LinearElement->FloatAttribute("vel.z"));
			linearData.accel = Vec3(LinearElement->FloatAttribute("accel.x"), LinearElement->FloatAttribute("accel.y"), LinearElement->FloatAttribute("accel.z"));
			linearData.maxSpeed = LinearElement->FloatAttribute("maxVel");
			linearData.maxAccel = LinearElement->FloatAttribute("maxAccel");

			XMLElement* AngularElement = PhysicsElement->FirstChildElement("Angular");
			AngularMotion angularData;
			angularData.rotation = AngularElement->FloatAttribute("rotation");
			angularData.maxRotation = AngularElement->FloatAttribute("maxRotation");

			componentData = new PhysicsComponent(linearData, angularData, mass, loadedCharacter->GiveSteeringOutput());
			loadedCharacter->AddComponent<PhysicsComponent>(componentData);

			return true;
		}

		//Makes sure we are actually look for a character object
		else if (dynamic_cast<Body*>(loadedCharacter)) {
			printf("The character class entered has not been added to the file: %s\n", xmlDoc);
			return false;
		}

		printf("The class type entered is not inherited from base character\n");
		return false;*/
	}
};

#endif
