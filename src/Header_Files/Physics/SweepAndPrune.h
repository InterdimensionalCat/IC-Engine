#pragma once
#include "PhysicsBody.h"
#include <numeric>

enum class SweeperDir {
	Horizontal = 0,
	Vertical
};

//interval used for the sweep
struct SweepInterval {
	float min = std::numeric_limits<float>().infinity();
	float max = -std::numeric_limits<float>().infinity();

	bool operator==(const SweepInterval& other) const {
		return max == other.max && min == other.min;
	}
};

struct SweepEntry {
	SweepEntry(SweepInterval interval,
		PhysicsBody* body,
		size_t polyInd) : interval(interval), body(body),
		polyInd(polyInd) {}
	SweepInterval interval;
	PhysicsBody* body;
	size_t polyInd;
};

//comparator used to sort the bodylist map
class IntervalComp {
public:
	bool operator() (const SweepEntry &lhs, 
		const SweepEntry &rhs) const {
		return lhs.interval.min < rhs.interval.min;
	}
};

//class used for a more efficient broad phase
class SweepAndPrune
{
public:
	//adds a new body to the sweep and prune check
	//or updates the body if it already exists
	void updateBody(PhysicsBody* body, const size_t& polyInd);

	//strictly adds a new body
	void addBody(PhysicsBody* body, const size_t& polyInd);

	//sort all the intervals
	void sort();

	//TODO: make a seperate data structure "Sweeper Entry" that contains this info
	std::vector<SweepEntry> bodies;
	SweeperDir direction = SweeperDir::Horizontal;


};