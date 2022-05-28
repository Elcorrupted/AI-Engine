#ifndef COMPONENT_H
#define COMPONENT_H

class Body;

class Component {
public:
	inline Component() : parent(nullptr) {}
	virtual ~Component() { parent = nullptr; }
	virtual bool OnCreate(Body* parent_) = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() const = 0;

protected:
	Body* parent;
};

#endif
