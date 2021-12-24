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
		AudioEngine() : bufferMap(std::map<std::string, std::shared_ptr<sf::SoundBuffer>>()), 
			musicMap(std::map<std::string, std::shared_ptr<sf::Music>>()), currentSong(std::shared_ptr<sf::Music>(nullptr)),
		    currentSounds(std::map<std::string, Sound>()) {
		}

		~AudioEngine() {

		}

		void clearLoadedAudio() {
			bufferMap.clear();
			musicMap.clear();
		}
		void update();

		void playSound(const std::string& soundName, const float volume = 100.0f, const float pitch = 1.0f, const bool repeat = false);
		void playMusic(const std::string& musicName, const float volume = 100.0f, const float pitch = 1.0f, const bool repeat = true);
		sf::SoundSource::Status getStatusOfSound(const std::string& soundName);


		static inline AudioEngine* get() {
			if (instance.get() == nullptr) {
				instance = std::make_unique<AudioEngine>();
			}
			return instance.get();
		}

		void loadSound(const std::string& soundname);

		void loadMusic(const std::string& musicname);

		std::shared_ptr<sf::Music> currentSong;
		std::map<std::string, Sound> currentSounds;
	private:

		friend class ic::Sound;

		std::shared_ptr<sf::SoundBuffer> getBufferFromName(const std::string& buffername);

		std::shared_ptr<sf::Music> getMusicFromName(const std::string& musicname);

		inline static std::unique_ptr<AudioEngine> instance;

		std::map<std::string, std::shared_ptr<sf::SoundBuffer>> bufferMap;
		std::map<std::string, std::shared_ptr<sf::Music>> musicMap;
	};

}

