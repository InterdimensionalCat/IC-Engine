#pragma once
#include <any>

namespace ic {


    class EventBus
    {
    public:

        template<typename T>
        class Subscription
        {
        public:
            Subscription(void (*callback)(T)) : callback_fn(callback) {}

            ~Subscription()
            {
                EventBus::Unsubscribe(this);
            }

            void operator()(T arg) override {
                callback_fn(arg);
            }

        private:
            void (*callback_fn)(T);
        };

        static std::map<std::type_info, std::vector<std::any>> topics;

        template<typename T>
        static void publish(T published_event)
        {
            auto t = typeid(T);

            auto it = topics.find(t);

            if (it != topics.end()) {
                auto subscribers = std::any_cast<std::vector<Subscription<T>>>(it->second);

                for (auto& subscription : subscribers) {
                    subscription(published_event);
                }
            }
        }

        template<typename T>
        static std::shared_ptr<Subscription<T>> subscribe(void (*callback)(T))
        {
            /* Determine event type so we can find the correct subscriber list */
            auto t = typeid(T);
            std::shared_ptr<Subscription<T>> newSub = std::make_shared<Subscription<T>>(callback);
            
            auto it = topics.find(t);

            if (it == topics.end()) {
                std::vector<std::any> newVec;
                newVec.push_back(newSub);
                topics.emplace(t, newVec);
            }
            else {
                it->second.push_back(newSub);
            }

            return newSub;
        }

        template<typename T>
        static void Unsubscribe(Subscription<T> subscription)
        {
            auto t = typeid(T);

            auto it = topics.find(t);

            if (it != topics.end()) {
                if (it->second.size > 0) {
                    std::erase(
                        std::remove_if(it->second.begin(), it->second.end(), subscription), 
                        it->second.end()
                    );
                }
            }
        }
    };
}