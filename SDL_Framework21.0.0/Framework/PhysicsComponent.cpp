#include "PhysicsComponent.h"
#include "VMath.h"

PhysicsComponent::PhysicsComponent(LinearMotion linearValues_, AngularMotion angularValues_, float mass_, SteeringOutput* steering_) : Component() {
	steering = steering_;
	linearValues = linearValues_;
	angularValues = angularValues_;
	mass = mass_;
}

PhysicsComponent::~PhysicsComponent() {
}

bool PhysicsComponent::OnCreate(Body* parent_) {
	parent = parent_;
	if (parent == nullptr) {
		return false;
	}
	return true;
}

void PhysicsComponent::OnDestroy() {
	if (parent) parent = nullptr;
	if (steering) steering = nullptr;
}

void PhysicsComponent::Update(const float deltaTime) {
	if (steering->linear.x == steering->linear.y == steering->linear.z == 0.0f) {
		linearValues.vel = Vec3();
	}
	if (steering->angular == 0.0f) {
		angularValues.rotation = 0.0f;
	}

	parent->orientation += angularValues.rotation * deltaTime;
	parent->pos += linearValues.vel * deltaTime;

	linearValues.vel += steering->linear * deltaTime;
	angularValues.rotation += steering->angular * deltaTime;

	if (VMath::mag(linearValues.vel) > linearValues.maxSpeed) {
		linearValues.vel = VMath::normalize(linearValues.vel) * linearValues.maxSpeed;
	}

	if (angularValues.rotation > angularValues.maxRotation) {
		angularValues.rotation = angularValues.maxRotation;
	}
}

void PhysicsComponent::Render() const {
	printf("3D rendering would go here");
}