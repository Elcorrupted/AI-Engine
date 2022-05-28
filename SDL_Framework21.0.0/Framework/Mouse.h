#ifndef MOUSE_H
#define MOUSE_H

#include "Body.h"
#include <SDL.h>
#include "SteeringOutput.h"
#include "KinematicSteeringOutPut.h"
const bool DEBUG = true;
class Mouse : public Body
{
public:
	Mouse();
	//Mouse(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_);
	Mouse(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_,
		float orientation_, float rotation_, float maxSpeed_, 
		float maxAccel_, float maxRotation_);
	~Mouse();
	void HandleEvents(const SDL_Event& c);

	inline float GetMaxSpeed() const { return maxSpeed; }
	inline float GetOrientation() const { return orientation; }
	
	inline Vec3 GetVel() const { return vel; }
	inline float GetRotation() const { return rotation; }

	inline float GetMaxAccel() const { return maxAccel; }
	inline float GetMaxRot() const { return maxRotation; }

	void UpdateMouse(float deltaTime_, SteeringOutput *steering_);
	int GetHealth();
	int health;
private:
	Vec3 vel, accel;
	float mass;
	float rotation;		// rotating at this speed (radians per second?)
	float maxSpeed, maxAccel, maxRotation;
};

#endif // !MOUSE_H
