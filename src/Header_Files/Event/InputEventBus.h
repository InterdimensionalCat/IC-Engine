#pragma once
#include "EventBus.h"
#include <map>

namespace ic {
    class InputEventBus : public EventBus
    {
    public:
        std::map<std::type_info, std::vector<std::any>>& getTopics() override {
            return topics;
        }

        std::string getName() const override {
            return "InputEventBus";
        }

        static InputEventBus* get() {
            if (instance.get() == nullptr) {
                instance = std::make_unique<InputEventBus>();
            }
            return instance.get();
        }
    private:
        std::map<std::type_info, std::vector<std::any>> topics;
        inline static std::unique_ptr<InputEventBus> instance;
    };
}