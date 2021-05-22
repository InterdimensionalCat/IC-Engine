#include "include.h"
#include "SweepAndPrune.h"
#include "PhysicsBody.h"


void SweepAndPrune::updateBody(PhysicsBody* body, const size_t& polyInd) {
	for (size_t i = 0; i < bodies.size(); i++) {
		if (bodies[i].body == body && bodies[i].polyInd == polyInd) {
			//update already existing body
			auto &interval = bodies[i].interval;
			interval.min = numeric_limits<float>().infinity();
			interval.max = -numeric_limits<float>().infinity();
			auto poly = body->getBodies()[polyInd];
			for (size_t i = 0; i < poly.size(); i++) {

				auto& point = poly[i];

				float testPt;
				if (direction == SweeperDir::Horizontal) {
					testPt = point.x;
				}
				else {
					testPt = point.y;
				}

				if (testPt > interval.max) {
					interval.max = testPt;
				}

				if (testPt < interval.min) {
					interval.min = testPt;
				}
			}

#ifdef _DEBUG
			if (interval.min == numeric_limits<float>().infinity()) {
				//throw BadInfinityException();
			}

			if (interval.max == -numeric_limits<float>().infinity()) {
				//throw BadInfinityException();
			}
#endif

			return;
		}
	}
	//else add a new body
	addBody(body, polyInd);
}

void SweepAndPrune::addBody(PhysicsBody* body, const size_t& polyInd) {
	bodies.emplace_back(SweepInterval(), body, polyInd);
	auto& interval = bodies[bodies.size() - 1].interval;
	auto poly = body->getBodies()[polyInd];
	for (size_t i = 0; i < poly.size(); i++) {

		auto& point = poly[i];

		float testPt;
		if (direction == SweeperDir::Horizontal) {
			testPt = point.x;
		}
		else {
			testPt = point.y;
		}

		if (testPt > interval.max) {
			interval.max = testPt;
		}

		if (testPt < interval.min) {
			interval.min = testPt;
		}
	}
#ifdef _DEBUG
	if (interval.min == numeric_limits<float>().infinity()) {
		//throw BadInfinityException();
	}

	if (interval.max == -numeric_limits<float>().infinity()) {
		//throw BadInfinityException();
	}
#endif
}

void SweepAndPrune::sort() {
	IntervalComp cmp;
	std::sort(bodies.begin(), bodies.end(), cmp);
}