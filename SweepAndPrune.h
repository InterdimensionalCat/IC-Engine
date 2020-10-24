#pragma once

class PhysicsBody;
class RigidBody;
class StaticBody;

//interval used for the sweep
struct SweepInterval {
	float min = numeric_limits<float>().infinity();
	float max = -numeric_limits<float>().infinity();

	bool operator==(const SweepInterval &other) const {
		return max == other.max && min == other.min;
	}
};

//comparator used to sort the bodylist map
class IntervalComp {
public:
	bool operator() (const pair<SweepInterval, PhysicsBody*> &lhs, const pair<SweepInterval, PhysicsBody*> &rhs) const {
		return lhs.first.min < rhs.first.min;
	}
};

//class used for a more efficient broad phase
class SweepAndPrune
{
public:
	//adds a new body to the sweep and prune check
	//or updates the body if it already exists
	void updateBody(PhysicsBody* body);

	//sort all the intervals
	void sort();

	vector<pair<SweepInterval, PhysicsBody*>> bodies;


};