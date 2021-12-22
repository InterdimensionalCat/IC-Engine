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


		static AudioEngine* get() {
			if (instance.get() == nullptr) {
				instance = std::make_unique<AudioEngine>();
			}
			return instance.get();
		}

		void loadSound(const std::string& soundname) {

			fs::path filepath(fs::current_path());
			filepath /= "resources";
			filepath /= "sounds";
			filepath /= soundname;
			filepath += ".wav";

			std::shared_ptr<sf::SoundBuffer> buffer = std::make_shared<sf::SoundBuffer>();
			if (!buffer->loadFromFile(filepath.string())) {
				Logger::error("Sound file at path {} could not be loaded!", filepath.string());
				throw std::exception();
			}

			bufferMap.emplace(soundname, buffer);

			Logger::info("Sound file {} loaded.", soundname);
		}

		void loadMusic(const std::string& musicname) {

			fs::path filepath(fs::current_path());
			filepath /= "resources";
			filepath /= "music";
			filepath /= musicname;
			filepath += ".wav";

			std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
			if (!music->openFromFile(filepath.string())) {
				Logger::error("Music file at path {} could not be loaded!", filepath.string());
				throw std::exception();
			}

			musicMap.emplace(musicname, music);
			Logger::info("Music file {} loaded.", musicname);
		}

		std::shared_ptr<sf::Music> currentSong;
		std::map<std::string, Sound> currentSounds;
	private:

		std::shared_ptr<sf::SoundBuffer> getBufferFromName(const std::string& buffername) {
			auto found = bufferMap.find(buffername);
			if (found != bufferMap.end()) {

				std::shared_ptr<sf::SoundBuffer> ptr = std::make_shared<sf::SoundBuffer>();
				*ptr = *found->second;
				return std::shared_ptr<sf::SoundBuffer>(ptr);
			}
			else {
				Logger::critical("Sound file {} has no buffer! Was it not loaded?", buffername);
				throw std::exception();
				return found->second;
			}
		}

		std::shared_ptr<sf::Music> getMusicFromName(const std::string& musicname) {
			auto found = musicMap.find(musicname);
			if (found != musicMap.end()) {
				return found->second;
			}
			else {
				Logger::critical("Music file {} not found! Was it not loaded?", musicname);
				throw std::exception();
				return found->second;
			}
		}

		inline static std::unique_ptr<AudioEngine> instance;

		std::map<std::string, std::shared_ptr<sf::SoundBuffer>> bufferMap;
		std::map<std::string, std::shared_ptr<sf::Music>> musicMap;
	};

}

