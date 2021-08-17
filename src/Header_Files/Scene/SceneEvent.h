#pragma once
#include "StringableEnum.h"
#include "ActorEntry.h"

namespace ic {
    class Scene;
    //class ActorEntry;

    enum class SceneEventType {
        Pre,
        Post
    };

    class SceneEvent
    {
    public:
        virtual ~SceneEvent() {}
        virtual void excecute(Scene* scene) = 0;
        virtual std::string getName() const = 0;
    };

#ifndef _Scene_Event
#define _Scene_Event(x, type) class x : public SceneEvent {\
public:\
	void excecute(Scene* scene) override;\
    std::string getName() const override {\
        return #x;\
    }\
    static SceneEventType getStaticType() {return type; }\
};
#endif

#ifndef _Scene_Event_NonTrivial
#define _Scene_Event_NonTrivial(x, entryname, type) class x : public SceneEvent {\
public:\
    x(std::shared_ptr<ActorEntry> entryname) : entryname(entryname) {}\
	void excecute(Scene* scene) override;\
    std::string getName() const override {\
        std::string name(#x);\
        return name + ":" + std::to_string(x::entryname->getIndex());\
    }\
    static SceneEventType getStaticType() {return type; }\
private:\
	std::shared_ptr<ActorEntry> entryname;\
};
#endif

    _Scene_Event(ResetLevelEvent, SceneEventType::Pre);
    _Scene_Event(ChangeLevelEvent, SceneEventType::Pre);
    _Scene_Event_NonTrivial(DespawnActorEvent, actortodespawn, SceneEventType::Pre);


    class SceneEventManager {
    public:

        SceneEventManager(Scene* scene);

        ~SceneEventManager();

        void handlePreEvents();

        void handlePostEvents();

        template<typename T, typename... Args>
        void pushEvent(const Args... args) {
            switch (T::getStaticType()) {
            case SceneEventType::Pre:
                preevents.push(std::make_unique<T>((args)...));
                break;
            case SceneEventType::Post:
                postevents.push(std::make_unique<T>((args)...));
            }

        }
    private:
        Scene* scene;

        std::queue<std::unique_ptr<SceneEvent>> preevents;
        std::queue<std::unique_ptr<SceneEvent>> postevents;
    };
}


