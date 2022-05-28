#ifndef BODY_H
#define BODY_H

#include "Vector.h"
#include "Component.h"
#include <vector>

using namespace MATH;

class Body {
	friend class PhysicsComponent;
	friend class ReadCharacterFile;
protected:
	Vec3 pos;
	float orientation;
	std::vector<Component*> components;

public:
	Body();
	Body(Vec3 pos_, float orientation_);
	~Body();
	
	inline Vec3 GetPos() const { return pos; }
	inline void SetPos(Vec3 pos_) { pos = pos_; }

	inline float GetOrientation() const { return orientation; }
	inline void SetOrientation(float orientation_) { orientation = orientation_; }

	//The AddComponent function will have a class of ? (ComponentTemplate) and a series of arguments (...Args)
	template<typename ComponentTemplate, typename ... Args>
	//Args is the address of an rvalue passed in at function call
	void AddComponent(Args&& ... args_) {
		//Makes args_ into an l or rvalue depending on Args
		ComponentTemplate* temp = new ComponentTemplate(std::forward<Args>(args_)...);

		//Prevents creation of a non Component based class
		if (!dynamic_cast<Component*>(temp)) {
			delete temp;
			temp = nullptr;
			return;
		}
		//Prevents adding duplicate components
		if (GetComponent<ComponentTemplate>()) {
			delete temp;
			temp = nullptr;
			return;
		}
		components.push_back(temp);
		temp->OnCreate(this);
	}

	template<typename ComponentTemplate>
	ComponentTemplate* GetComponent() {
		for (auto comp : components) {
			if (dynamic_cast<ComponentTemplate*>(comp)) {
				return dynamic_cast<ComponentTemplate*>(comp);
			}
		}
		return nullptr;
	}
};

#endif // !BODY_H