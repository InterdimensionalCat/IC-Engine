#pragma once
#include "Texture.h"
#include "TileCollisionEvent.h"
#include "Animation.h"
#include "Scene.h"
#include "MapBoundCollisionEvent.h"
#include <typeinfo>
#include "StringableEnum.h"
#include "ComponentManager.h"
#include "Input.h"
#include "ActorEntry.h"

#include <type_traits>

namespace ic {

	class Input;
	class Animation;

	typedef std::function<void(ic::Scene*, std::shared_ptr<ic::ActorEntry>, std::shared_ptr<json>)> Func;

#ifndef IC_COMP_OVERHEAD
#define IC_COMP_OVERHEAD
	void registerComponentsFunction();

	extern std::vector<Func> generateJsonFunctions;
	extern std::vector<Func> generateFromJsonFunctions;

	class RegisterComponentsClass {
	public:
		inline static std::vector<std::function<void()>> registerComponents;
	};

	template<typename T>
	void inline createJsonOf(Scene* scene, std::shared_ptr<ActorEntry> entry, std::shared_ptr<json> file) {
		auto comp = scene->compManager->getComponent<T>(entry);
		if (comp != nullptr) {
			comp->toJson(file);
		}
	}

	template<typename T>
	void inline createComponentFromJson(Scene* scene, std::shared_ptr<ActorEntry> entry, std::shared_ptr<json> file) {
		if (file->find(T::getNameStatic()) != file->end()) {
			auto comp = scene->compManager->assignComponent<T>(entry);
			comp->fromJson(file);
		}
	}

	template<typename T>
	void inline writeJsonArg(std::shared_ptr<json>& file, const std::string& name, const std::string& argname, const T& arg) {
		

		if constexpr (std::is_same<s2d::Percent, T>::value) {
			(*file)[name][argname] = (float)arg;
		}

		if constexpr (std::is_same<s2d::Meters, T>::value) {
			(*file)[name][argname] = (float)s2d::Pixels(arg);
		}

		if constexpr (!std::is_same<s2d::Percent, T>::value && !std::is_same<s2d::Meters, T>::value) {
			(*file)[name][argname] = arg;
		}
	}

	template<typename T>
	void inline readJsonArg(const std::shared_ptr<json>& file, const std::string& name, const std::string& argname, T& arg) {

		if constexpr (std::is_same<s2d::Meters, T>::value) {
			float argRaw = (*file)[name][argname];
			arg = (s2d::Meters)s2d::Pixels(argRaw);
		}
		
		if constexpr (std::is_same<s2d::Percent, T>::value) {
			float argRaw = (*file)[name][argname];
			arg = (T)argRaw;
		}

		if constexpr (!std::is_same<s2d::Percent, T>::value && !std::is_same<s2d::Meters, T>::value) {
			arg = (*file)[name][argname];
		}
	}

	template<typename... Args>
	void inline genericToJson(std::shared_ptr<json>& file, const std::string& name, const std::string argname, const Args&... args) {

		std::stringstream ss(argname);
		std::vector<std::string> result;

		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ',');

			substr.erase(std::remove_if(substr.begin(), substr.end(),
				[](char& c) {
					return std::isspace<char>(c, std::locale::classic());
				}),
				substr.end());

			result.push_back(substr);
		}

		int i = 0;
		int _[] = { 0, (writeJsonArg<Args>(file, name, result.at(i++), args), 0)... };
		(void)_;
	}

	template<typename... Args>
	void inline genericFromJson(const std::shared_ptr<json>& file, const std::string& name, const std::string& argname, Args&... args) {

		std::stringstream ss(argname);
		std::vector<std::string> result;

		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ',');

			substr.erase(std::remove_if(substr.begin(), substr.end(),
				[](char& c) {
					return std::isspace<char>(c, std::locale::classic());
				}),
				substr.end());

			result.push_back(substr);
		}

		int i = 0;
		int _[] = { 0, (readJsonArg<Args>(file, name, result.at(i++), args), 0)... };
		(void)_;
	}

#ifndef _JsonTrivial
#define _JsonTrivial(...)  void toJson(std::shared_ptr<json> file) const {\
genericToJson(file, getName(),   #__VA_ARGS__,   __VA_ARGS__);\
}\
void fromJson(const std::shared_ptr<json>& file) {\
genericFromJson(file, getName(), #__VA_ARGS__, __VA_ARGS__);\
}
#endif

#ifndef _JsonEnum
#define _JsonEnum(enumtype, enumval) \
  void toJson(std::shared_ptr<json> file) const {\
    (*file)[getName()][#enumval] = enumtype##ToString(enumval);\
}\
void fromJson(const std::shared_ptr<json>& file) {\
    enumval = enumtype##FromString((*file)[getName()][#enumval]); \
}
#endif

//components must be structs and call this macro where x is the type name
#ifndef _Component
#define _Component(x) std::string getName() const {\
    return #x;\
}\
static std::string getNameStatic() {\
	return #x;\
}\
private:\
class StartupObj {\
public:\
	StartupObj() {\
       RegisterComponentsClass::registerComponents.push_back(x::addJsonGenerator);\
	}\
};\
friend class StartupObj;\
static void addJsonGenerator() {\
		Func function = createJsonOf<x>;\
		Func fromjson = createComponentFromJson<x>;\
		if (!added) {\
				generateJsonFunctions.push_back(function);\
				generateFromJsonFunctions.push_back(fromjson);\
				added = true;\
		}\
}\
inline static StartupObj startup;\
inline static bool added = false;
#endif

#ifndef _Component_Trivial
#define _Component_Trivial(x, ...) _JsonTrivial(__VA_ARGS__) _Component(x)
#endif

#ifndef _Component_Enum
#define _Component_Enum(x, enumtype, enumval) _JsonEnum(enumtype, enumval) _Component(x)
#endif

	_CREATE_STRINGABLE_ENUM(ActionState, GroundStill, GroundMove, GroundTurn, Airborne);
	_CREATE_STRINGABLE_ENUM(PlatformType, Vertical, Horizontal, Falling, Still);

	enum class ConstrainedMovementEvent {
		OOB,
		OOBLeft,
		OOBRight,
		OOBTop,
		OOBBot
	};
#endif

	struct PlayerFlag {
		bool pflag = true;

		_Component_Trivial(PlayerFlag, pflag)
	};

	struct EnemyFlag {
		std::string enemyname = "";

		_Component_Trivial(EnemyFlag, enemyname)
	};

	struct StateController {
		ActionState state;
		_Component_Enum(StateController, ActionState, state)
	};

	struct AnimStateMap {
		std::shared_ptr<std::map<ActionState, AnimationEntry>> animations;
		ActionState prevstate;

		void toJson(std::shared_ptr<json> file) const {
			(*file)[getName()]["prevstate"] = ActionStateToString(prevstate);
			std::vector<json> arr;
			for (auto [state, val] : *animations) {
				std::shared_ptr<json> obj = std::make_shared<json>();
				val.toJson(obj);
				std::string jstr = "{ \"key\": \"" + ActionStateToString(state) + "\", \"value\": " + obj->dump() + "}";
				arr.push_back(json(
					json::parse(jstr)
				));
			}

			(*file)[getName()]["animations"] = arr;
		}

		void fromJson(const std::shared_ptr<json>& file) {
			prevstate = ActionStateFromString((*file)[getName()]["prevstate"]);
			animations = std::make_shared<std::map<ActionState, AnimationEntry>>();
			std::vector<json> entries = (*file)[getName()]["animations"];
			for (auto& entry : entries) {
				std::string key = entry["key"];
				AnimationEntry animentry;
				animentry.fromJson(entry["value"]);
				animations->emplace(ActionStateFromString(key), animentry);
			}
		}

		_Component(AnimStateMap)
	};

	struct InputController {
		std::shared_ptr<Input> input;

		//read/write a name that is a key into a map of input devices?


		void toJson(std::shared_ptr<json> file) const {
			(*file)[getName()]["input"] = input->getName();
		}

		void fromJson(const std::shared_ptr<json>& file) {
			input = Input::createInputDevice((*file)[getName()]["input"]);
		}

		_Component(InputController)
	};

	struct Animatable {
		std::shared_ptr<Animation> animation;

		void toJson(std::shared_ptr<json> file) const {
			std::shared_ptr<json> animEntryJson = std::make_shared<json>();
			animation->getAnimEntry().toJson(animEntryJson);
			(*file)[getName()]["animation"] = *animEntryJson;
		}

		void fromJson(const std::shared_ptr<json>& file) {
			AnimationEntry entry;
			std::shared_ptr<json> animEntryJson = std::make_shared<json>();
			*animEntryJson = (*file)[getName()]["animation"];
			entry.fromJson(animEntryJson);
			animation = std::make_shared<Animation>(entry);
		}


		_Component(Animatable)
	};

	struct Transform {
		//float x;
		//float y;

		s2d::Meters x;
		s2d::Meters y;

		_Component_Trivial(Transform, x, y)
	};

	struct Velocity {
		//float x;
		//float y;

		s2d::Meters x;
		s2d::Meters y;

		_Component_Trivial(Velocity, x, y)
	};

	struct BoundedVelocity {
		//float maxVelX;
		//float maxVelY;

		s2d::Meters maxVelX;
		s2d::Meters maxVelY;

		_Component_Trivial(BoundedVelocity, maxVelX, maxVelY)
	};

	struct PhysicsProperties {
		//float friction;
		//float gravity;

		s2d::Percent friction;
		s2d::Meters gravity;

		_Component_Trivial(PhysicsProperties, friction, gravity)
	};

	struct Jumpable {
		//float jumpForce;
		//float jumpReleaseMod;
		//float jumpFloat;

		s2d::Meters jumpForce;
		s2d::Percent jumpReleaseMod;
		s2d::Percent jumpFloat;

		bool jumpedflag = false;

		_Component_Trivial(Jumpable, jumpForce, jumpReleaseMod, jumpFloat)
	};

	struct Turnable {
		//float turnThreshold;

		s2d::Meters turnThreshold;

		_Component_Trivial(Turnable, turnThreshold)
	};

	struct AirborneState {
		int airborneTimer;
		int maxAirborneTimer;

		_Component_Trivial(AirborneState, airborneTimer, maxAirborneTimer)
	};

	struct HorzMovable {
		//float accelX;

		s2d::Meters accelX;

		_Component_Trivial(HorzMovable, accelX)
	};

	struct CircularMovable {
		//float accel;
		//float angleX;
		//float angleY;

		s2d::Meters accel;
		s2d::NormVec2m angle;

		void toJson(std::shared_ptr<json> file) const {
			(*file)[getName()]["accel"] = (float)accel;
			(*file)[getName()]["angleX"] = (float)angle.x;
			(*file)[getName()]["angleY"] = (float)angle.x;
		}

		void fromJson(const std::shared_ptr<json>& file) {
			float accelRaw = (*file)[getName()]["accel"];
			accel = (s2d::Meters)s2d::Pixels(accelRaw);
			s2d::Meters angleX = s2d::Meters((float)(*file)[getName()]["angleX"]);
			s2d::Meters angleY = s2d::Meters((float)(*file)[getName()]["angleY"]);
			angle = s2d::NormVec2m(angleX, angleY);
		}

		//_Component_Trivial(CircularMovable, accel, angleX, angleY);
		_Component(CircularMovable);
	};

	struct StateAccelerationValues {
		//float groundAccel;
		//float airAccel;
		//float stillAccel;
		//float turnAccel;

		s2d::Meters groundAccel;
		s2d::Meters airAccel;
		s2d::Meters stillAccel;
		s2d::Meters turnAccel;

		_Component_Trivial(StateAccelerationValues, groundAccel, airAccel, stillAccel, turnAccel)
	};

	struct StateFrictionValues {
		s2d::Percent groundFrc;
		s2d::Percent airFrc;
		s2d::Percent stillFrc;
		s2d::Percent turnFrc;

		_Component_Trivial(StateFrictionValues, groundFrc, airFrc, stillFrc, turnFrc)
	};

	struct ConstrainedMovement {
		s2d::Meters maxDisplacementLeft = -1.0f;
		s2d::Meters maxDisplacementRight = -1.0f;
		s2d::Meters maxDisplacementUp = -1.0f;
		s2d::Meters maxDisplacementDown = -1.0f;

		s2d::Meters originX;
		s2d::Meters originY;

		std::shared_ptr<std::queue<ConstrainedMovementEvent>> events
			= std::make_shared<std::queue<ConstrainedMovementEvent>>();

		void toJson(std::shared_ptr<json> file) const {

			(*file)[getName()]["maxDisplacementLeft"] = (float)maxDisplacementLeft;
			(*file)[getName()]["maxDisplacementRight"] = (float)maxDisplacementRight;
			(*file)[getName()]["maxDisplacementUp"] = (float)maxDisplacementUp;
			(*file)[getName()]["maxDisplacementDown"] = (float)maxDisplacementDown;

			(*file)[getName()]["originX"] = (float)originX;
			(*file)[getName()]["originY"] = (float)originY;

			(*file)[getName()]["events"] = nullptr;
		}

		void fromJson(const std::shared_ptr<json>& file) {
			maxDisplacementLeft = s2d::Meters((float)(*file)[getName()]["maxDisplacementLeft"]);
			maxDisplacementRight = s2d::Meters((float)(*file)[getName()]["maxDisplacementRight"]);
			maxDisplacementUp = s2d::Meters((float)(*file)[getName()]["maxDisplacementUp"]);
			maxDisplacementDown = s2d::Meters((float)(*file)[getName()]["maxDisplacementDown"]);

			originX = s2d::Meters((float)(*file)[getName()]["originX"]);
			originY = s2d::Meters((float)(*file)[getName()]["originY"]);
		}


		_Component(ConstrainedMovement)
	};

	struct ConstrainedMovementEventListener {
		std::shared_ptr<std::queue<ConstrainedMovementEvent>> events
			= std::make_shared<std::queue<ConstrainedMovementEvent>>();

		void toJson(std::shared_ptr<json> file) const {
			(*file)[getName()]["events"] = nullptr;
		}

		void fromJson(const std::shared_ptr<json>& file) {

		}


		_Component(ConstrainedMovementEventListener)
	};

	struct CircularConstrainedMovement {
		s2d::Meters radius;
		s2d::Meters originX;
		s2d::Meters originY;

		_Component_Trivial(CircularConstrainedMovement, radius, originX, originY);
	};

	struct JumpOn {
		s2d::Meters jumpTolerencePercent;
		s2d::Percent jumpVelMod;
		s2d::Meters jumpMin;

		_Component_Trivial(JumpOn, jumpTolerencePercent, jumpVelMod, jumpMin)
	};

	struct SpriteDrawable {

		SpriteDrawable() = default;
		SpriteDrawable(std::shared_ptr<sf::Sprite> spr, std::shared_ptr<Texture> tex) : spr(spr), tex(tex) {
			spr->setTexture(tex->getTexture());
		}

		std::shared_ptr<sf::Sprite> spr;
		std::shared_ptr<Texture> tex;

		void toJson(std::shared_ptr<json> file) const {
			(*file)[getName()]["spr"] = nullptr;
			(*file)[getName()]["tex"] = tex->getName();
		}

		void fromJson(const std::shared_ptr<json>& file) {
			spr = std::make_shared<sf::Sprite>();
			tex = std::make_shared<Texture>((*file)[getName()]["tex"]);
			spr->setTexture(tex->getTexture());
		}

		_Component(SpriteDrawable)
	};

	struct Hitbox {
		s2d::Rect2m rect;

		void toJson(std::shared_ptr<json> file) const {
			(*file)[getName()]["rect"]["left"] = (float)s2d::Pixels(rect.min.x);
			(*file)[getName()]["rect"]["top"] = (float)s2d::Pixels(rect.min.y);
			(*file)[getName()]["rect"]["width"] = (float)s2d::Pixels(rect.width());
			(*file)[getName()]["rect"]["height"] = (float)s2d::Pixels(rect.height());
		}

		void fromJson(const std::shared_ptr<json>& file) {

			auto x = s2d::Meters((float)(*file)[getName()]["rect"]["left"]);
			auto y = s2d::Meters((float)(*file)[getName()]["rect"]["top"]);
			auto width = s2d::Meters((float)(*file)[getName()]["rect"]["width"]);
			auto height = s2d::Meters((float)(*file)[getName()]["rect"]["height"]);
		}

		_Component(Hitbox)

		//_Component_Trivial(Hitbox, rect)
	};

	struct HitboxExtension {
		s2d::Rect2m rect;

		void toJson(std::shared_ptr<json> file) const {
			(*file)[getName()]["rect"]["left"] = (float)s2d::Pixels(rect.min.x);
			(*file)[getName()]["rect"]["top"] = (float)s2d::Pixels(rect.min.y);
			(*file)[getName()]["rect"]["width"] = (float)s2d::Pixels(rect.width());
			(*file)[getName()]["rect"]["height"] = (float)s2d::Pixels(rect.height());
		}

		void fromJson(const std::shared_ptr<json>& file) {

			auto x = s2d::Meters((float)(*file)[getName()]["rect"]["left"]);
			auto y = s2d::Meters((float)(*file)[getName()]["rect"]["top"]);
			auto width = s2d::Meters((float)(*file)[getName()]["rect"]["width"]);
			auto height = s2d::Meters((float)(*file)[getName()]["rect"]["height"]);
		}

		_Component(HitboxExtension)
	};

	struct TileCollidable {
		bool tileCollidable = true;

		_Component_Trivial(TileCollidable, tileCollidable)
	};

	struct PlatformTolerence {
		s2d::Meters up;
		s2d::Meters down;

		_Component_Trivial(PlatformTolerence, up, down);
	};

	struct TileCollisionEventListener {
		std::shared_ptr<std::deque<TileCollisionEvent>> events = std::make_shared<std::deque<TileCollisionEvent>>();
		~TileCollisionEventListener() {
			events->clear();
		}

		void toJson(std::shared_ptr<json> file) const {
			(*file)[getName()]["events"] = nullptr;
		}

		void fromJson(const std::shared_ptr<json>& file) {

		}

		_Component(TileCollisionEventListener)
	};

	struct BoundByMapBounds {
		bool boundUp = true;
		bool boundDown = true;
		bool boundLeft = true;
		bool boundRight = true;

		_Component_Trivial(BoundByMapBounds, boundUp, boundDown, boundLeft, boundRight)
	};

	struct MapBoundCollisionListener {

		std::shared_ptr<std::deque<MapBoundCollisionEvent>> events = std::make_shared<std::deque<MapBoundCollisionEvent>>();

		~MapBoundCollisionListener() {
			events->clear();
		}

		void toJson(std::shared_ptr<json> file) const {
			(*file)[getName()]["events"] = nullptr;
		}

		void fromJson(const std::shared_ptr<json>& file) {

		}

		_Component(MapBoundCollisionListener)
	};

	struct ActorCollidable {
		std::string collisiontype;

		_Component_Trivial(ActorCollidable, collisiontype);
	};

	struct PlatformTypeable {
		PlatformType type;

		_Component_Enum(PlatformTypeable, PlatformType, type);
	};

	struct FallingPlatform {
		bool falling = false;

		//s2d::Meters grv = s2d::Meters(0.5f);
		s2d::Meters grv = 0.5_mtr;
		//float grv = s2d::toMeters(0.5f);
		_Component_Trivial(FallingPlatform, falling, grv);
	};
}

