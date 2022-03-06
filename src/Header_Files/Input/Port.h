#pragma once
#include <vector>
#include <memory>

namespace ic {
	class Port {
    public:
        static std::shared_ptr<Port> createPort() {
            return std::make_shared<Port>();
        }

        ~Port() {
            releasePort(port_id);
        }

        uint32_t value() const {
            return port_id;
        }
	private:

        Port() : port_id(getUnusedPort()) {

        }

        static uint32_t getUnusedPort() {
            if (!unused_ids.empty()) {
                uint32_t unused_port = unused_ids.back();
                unused_ids.pop_back();
                return unused_port;
            }
            else {
                return max_port++;
            }
        }

        static void releasePort(const uint32_t freeport) {
            unused_ids.push_back(freeport);
        }

		uint32_t port_id;
        inline static std::vector<uint32_t> unused_ids;
        inline static uint32_t max_port = 1;
	};
}