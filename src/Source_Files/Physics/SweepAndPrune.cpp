#include "include.h"
#include "SweepAndPrune.h"
#include "RigidBody.h"
#include "StaticBody.h"


void SweepAndPrune::updateBody(PhysicsBody* body) {
	for (size_t i = 0; i < bodies.size(); i++) {
		if (bodies.at(i).second == body) {
			//update already existing body
			auto &interval = bodies.at(i).first;
			interval.min = numeric_limits<float>().infinity();
			interval.max = -numeric_limits<float>().infinity();
			for (auto &e : body->getBody().edges) {
				auto xpt = e.start.x;
				if (xpt > interval.max) {
					interval.max = xpt;
				}

				if (xpt < interval.min) {
					interval.min = xpt;
				}
			}
			return;
		}
	}
	//else add a new body

	bodies.emplace_back(SweepInterval(), body);
	auto &interval = bodies.at(bodies.size() - 1).first;
	for (auto &e : body->getBody().edges) {
		auto xpt = e.start.x;
		if (xpt > interval.max) {
			interval.max = xpt;
		}

		if (xpt < interval.min) {
			interval.min = xpt;
		}
	}

	if (interval.min == numeric_limits<float>().infinity()) {
#ifdef _DEBUG
		throw BadInfinityException<float>(interval.min);
#endif
	}

	if (interval.max == -numeric_limits<float>().infinity()) {
#ifdef _DEBUG
		throw BadInfinityException<float>(interval.max);
#endif
	}
}

void SweepAndPrune::sort() {
	IntervalComp cmp;
	std::sort(bodies.begin(), bodies.end(), cmp);
}