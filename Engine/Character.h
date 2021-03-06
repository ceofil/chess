#pragma once
#include "Vec2.h"
#include "Animation.h"

class Character
{
private:
	enum class Sequence
	{
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		WalkingDown,
		StandingLeft,
		StandingRight,
		StandingUp,
		StandingDown,
		Count
	};

public:
	Character(const Vec2& pos);
	void Draw(Graphics& gfx) const;
	void SetDir(const Vec2& dir);
	void Update(float dt);

private:
	Surface sprite;
	Vec2 pos;
	Vec2 vel = { 0.0f,0.0f };
	std::vector<Animation> animations;
	Sequence iCurSequence = Sequence::StandingDown;
	float speed = 150.0f;
};