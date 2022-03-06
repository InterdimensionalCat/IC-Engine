#pragma once
#include <any>
#include <queue>
#include <string>
#include <vector>

namespace ic {

    template<typename T>
    class Subscription
    {
    public:
        Subscription(std::function<void(T)> callback) : callback_fn(callback) {}

        void operator()(T arg) override {
            callback_fn(arg);
        }

    private:
        std::function<void(T)> callback_fn;
    };

    class EventBus
    {
    public:

        template<typename T>
        void publish(T published_event)
        {
            auto t = typeid(T);
            Logger::debug("Publishing event of type {}", t.name());
            //eventQueue.push(std::pair(t, published_event));

            auto it = getTopics().find(t);

            if (it != getTopics().end()) {
                auto subscribers = std::any_cast<std::vector<Subscription<T>>>(it->second);

                for (auto& subscription : subscribers) {
                    subscription(published_event);
                }
            }
        }

        void handleEvents() {
            //while (!eventQueue.empty()) {
            //    auto& [t, published_event] = eventQueue.front();

            //    Logger::debug("Handling event of type {}", t.name());

            //}
        }

        template<typename T>
        std::shared_ptr<Subscription<T>> subscribe(std::function<void(T)> callback)
        {
            auto t = typeid(T);
            std::shared_ptr<Subscription<T>> newSub = std::make_shared<Subscription<T>>(callback);

            auto it = getTopics().find(t);

            if (it == getTopics().end()) {
                std::vector<std::any> newVec;
                newVec.push_back(newSub);
                getTopics().emplace(t, newVec);
            }
            else {
                it->second.push_back(newSub);
            }

            return newSub;
        }

        template<typename T>
        void unsubscribe(Subscription<T> subscription)
        {
            auto t = typeid(T);

            auto it = getTopics().find(t);

            if (it != getTopics().end()) {
                if (it->second.size > 0) {
                    std::erase(
                        std::remove_if(it->second.begin(), it->second.end(), subscription),
                        it->second.end()
                    );
                }
            }
        }

        virtual std::map<std::type_info, std::vector<std::any>>& getTopics() = 0;
        virtual std::string getName() const = 0;

    private:
        //std::queue<std::pair<std::type_info, std::any>> eventQueue;
    };

    class GlobalEventBus : public EventBus
    {
    public:
        std::map<std::type_info, std::vector<std::any>>& getTopics() override {
            return topics;
        }

        std::string getName() const override {
            return "GlobalEventBus";
        }

        static GlobalEventBus* get() {
            if (instance.get() == nullptr) {
                instance = std::make_unique<GlobalEventBus>();
            }
            return instance.get();
        }
    private:
        std::map<std::type_info, std::vector<std::any>> topics;
        inline static std::unique_ptr<GlobalEventBus> instance;
    };
}