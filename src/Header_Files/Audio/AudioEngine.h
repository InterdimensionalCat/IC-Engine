#pragma once

namespace ic {

	/**
	 * @brief central audio engine class
	 * @todo audio needs to be more fleshed out in
	 * general before proper documentation is advantageous
	*/
	class AudioEngine {

	public:


		///new engine
		class SoundRequest {
		public:
			SoundRequest(const std::string& soundName,
				const float volume = 100.0f,
				const float pitch = 1.0f,
				const bool repeat = false,
				const bool start = true) :
				name(soundName), volume(volume),
				pitch(pitch), repeat(repeat),
				start(start) 
			{}

			std::string toString() {
				return "Request for Sound " + name + " with"
					" volume " + std::to_string(volume) + 
					", pitch " + std::to_string(pitch) + 
					", repeat "+ std::to_string(repeat) +
					", start " + std::to_string(start);
			}

		private:

			friend class AudioEngine;

			std::string name;
			float volume;
			float pitch;
			bool repeat;
			bool start;
		};

		class MusicRequest {
		public:
			MusicRequest(const std::string& musicName,
				const float volume = 100.0f,
				const float pitch = 1.0f,
				const bool repeat = false,
				const bool start = true) :
				name(musicName), volume(volume),
				pitch(pitch), repeat(repeat),
				start(start)
			{}

			std::string toString() {
				return "Request for Music " + name + " with"
					" volume " + std::to_string(volume) +
					", pitch " + std::to_string(pitch) +
					", repeat " + std::to_string(repeat) +
					", start " + std::to_string(start);
			}

		private:

			friend class AudioEngine;

			std::string name;
			float volume;
			float pitch;
			bool repeat;
			bool start;
		};

		AudioEngine();

		~AudioEngine();

		void playSound(SoundRequest r);

		void playMusic(MusicRequest r);

		void flush();

		void update();


		static inline AudioEngine* get() {
			if (instance.get() == nullptr) {
				instance = std::make_unique<AudioEngine>();
			}
			return instance.get();
		}

		bool loadSound(const std::string& soundname, 
			std::shared_ptr<sf::SoundBuffer>& bufferOut);

		bool loadMusic(const std::string& musicname, 
			std::shared_ptr<sf::Music>& musicOut);

	private:

		void processSoundRequests();

		void processMusicRequests();

		bool searchForSoundFile(const std::string& name, fs::path& filepath);

		bool searchForMusicFile(const std::string& name, fs::path& filepath);

		inline static std::unique_ptr<AudioEngine> instance;

		std::vector<SoundRequest> soundRequests;
		std::vector<MusicRequest> musicRequests;

		std::map<std::string, 
			std::shared_ptr<std::vector<
			std::shared_ptr<sf::Sound>>>> playingSounds;

		std::map<std::string, std::shared_ptr<sf::Music>> playingMusic;

		std::map<std::string, std::shared_ptr<sf::SoundBuffer>> bufferMap;
		std::map<std::string, std::shared_ptr<sf::Music>> musicMap;
	};
}

