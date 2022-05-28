#include "Mouse.h"
#include "VMath.h"

Mouse::Mouse()
{
}

//Mouse::Mouse(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_)
//{
//	pos.x = pos_.x;
//	pos.y = pos_.y;
//	pos.z = pos_.z;
//
//	vel.x = vel_.x;
//	vel.y = vel_.y;
//	vel.z = vel_.z;
//
//	accel.x = accel_.x;
//	accel.y = accel_.y;
//	accel.z = accel_.z;
//
//	mass = mass_;
//}

Mouse::Mouse(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_, 
float orientation_, float rotation_, float maxSpeed_, float maxAccel_,
float maxRotation_)
{
	pos = pos_;
	vel = vel_;
	accel = accel_;
	mass = mass_;
	orientation = orientation_;
	rotation = rotation_;
	maxSpeed = maxSpeed_;
	maxAccel = maxAccel_;
	maxRotation = maxRotation_;
	health = 0;
}

Mouse::~Mouse()
{
}

void Mouse::HandleEvents(const SDL_Event& c)
{

}


void Mouse::UpdateMouse(float deltaTime_, SteeringOutput* steering_)
{
	if (steering_->linear.x == steering_->linear.y == steering_->linear.z == 0.0f) {
		vel = Vec3();
	}

	if (steering_->angular == 0.0f) {
		rotation = 0.0f;
	}

	// Update orientation
	orientation += rotation * deltaTime_;
	pos += vel * deltaTime_;

	vel += steering_->linear * deltaTime_;
	rotation += steering_->angular * deltaTime_;

	// Clip to maxspeed, if speed exceeds max
	if (VMath::mag(vel) > maxSpeed)
	{
		vel = VMath::normalize(vel) * maxSpeed;
	}

	// Clip to maxrotation, if needed
	if (rotation > maxRotation)
	{
		rotation = maxRotation;
	}
}

int Mouse::GetHealth()
{
	return health;
}
