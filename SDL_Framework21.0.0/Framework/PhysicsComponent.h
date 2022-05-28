#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_h

#include "Mouse.h"
#include "Component.h"
#include "Vector.h"

using namespace MATH;
struct LinearMotion {
	Vec3 vel, accel;
	float maxSpeed, maxAccel;
};

struct AngularMotion {
	float rotation, maxRotation;
};

class PhysicsComponent : public Component {
private:
	float mass;
	SteeringOutput* steering;
	LinearMotion linearValues;
	AngularMotion angularValues;

public:
	PhysicsComponent(LinearMotion linearValues_, AngularMotion angularValues_, float mass_, SteeringOutput* steering_);
	~PhysicsComponent();

	bool OnCreate(Body* parent_);
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;

	inline Vec3 GetVel() { return linearValues.vel; }
	inline float GetMaxSpeed() { return linearValues.maxSpeed; }
	inline float GetMaxAccel() { return linearValues.maxAccel; }

	inline float GetRot() { return angularValues.rotation; }
	inline float GetMaxRot() { return angularValues.maxRotation; }
};
#endif
