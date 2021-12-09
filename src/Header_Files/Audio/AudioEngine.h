#pragma once
#include "Sound.h"

namespace ic {

	/**
	 * @brief central audio engine class
	 * @todo audio needs to be more fleshed out in
	 * general before proper documentation is advantageous
	*/
	class AudioEngine {

	public:
		AudioEngine() {}
		void update();

		void playSound(const std::string& soundName, const float volume = 100.0f, const float pitch = 1.0f, const bool repeat = false);
		void playMusic(const std::string& musicName, const float volume = 100.0f, const float pitch = 1.0f, const bool repeat = true);
		sf::SoundSource::Status getStatusOfSound(const std::string& soundName);


		static AudioEngine* get() {
			if (instance.get() == nullptr) {
				instance = std::make_unique<AudioEngine>();
			}
			return instance.get();
		}

		std::shared_ptr<sf::Music> currentSong = std::shared_ptr<sf::Music>(nullptr);
		std::map<std::string, Sound> currentSounds = std::map<std::string, Sound>();
	private:
		inline static std::unique_ptr<AudioEngine> instance;
	};

}

