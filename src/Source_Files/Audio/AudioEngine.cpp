#include "include.h"
#include "AudioEngine.h"


using namespace ic;


AudioEngine::AudioEngine() : 
	soundRequests(),musicRequests(), 
	playingSounds(), playingMusic(), 
	bufferMap(), musicMap()
{}

AudioEngine::~AudioEngine() {

}

void AudioEngine::playSound(SoundRequest r) {
	soundRequests.push_back(r);
}

void AudioEngine::playMusic(MusicRequest r) {
	musicRequests.push_back(r);
}

void AudioEngine::flush() {
	bufferMap.clear();
	musicMap.clear();
}

void AudioEngine::update() {

	//do not process if no sounds
	if (soundRequests.empty() && musicRequests.empty()) return;

	processSoundRequests();
	processMusicRequests();


	//remove sounds/music that are not playing
	for (auto& v : playingSounds) {
		std::erase_if(*v.second, [](const auto& elt) {
			return elt->getStatus() != sf::SoundSource::Status::Playing;
			}
		);
	}

	std::erase_if(playingMusic, [](const auto& elt) {
		auto const& [key, value] = elt;
		return value->getStatus() != sf::SoundSource::Status::Playing;
		}
	);
}

bool AudioEngine::loadSound(const std::string& soundname, 
	std::shared_ptr<sf::SoundBuffer>& bufferOut)
{

	Logger::info("Loading Sound with name {}...", soundname);

	fs::path filepath(fs::current_path());
	if (!searchForSoundFile(soundname, filepath)) {
		Logger::error("Sound file with name {} "
			"could not be loaded!", soundname);
		return false;
	}

	std::shared_ptr<sf::SoundBuffer> buffer = std::make_shared<sf::SoundBuffer>();
	if (!buffer->loadFromFile(filepath.string())) {
		Logger::error("Sound file with name {} "
			"could not be loaded!", soundname);
		return false;
	}

	bufferMap.emplace(soundname, buffer);
	bufferOut = buffer;

	Logger::info("Sound file {} loaded sucessfully!", soundname);
}

bool AudioEngine::loadMusic(const std::string& musicname,
	std::shared_ptr<sf::Music>& musicOut) {

	Logger::info("Loading Music with name {}...", musicname);

	fs::path filepath(fs::current_path());
	if (!searchForMusicFile(musicname, filepath)) {
		Logger::error("Music file with name {} "
			"could not be loaded!", musicname);
		return false;
	}

	std::shared_ptr<sf::Music> song = std::make_shared<sf::Music>();

	if (!song->openFromFile(filepath.string())) {
		Logger::error("Music file with name {} "
			"could not be opened!", musicname);
		return false;
	}

	musicMap.emplace(musicname, song);
	musicOut = song;

	Logger::info("Mound file {} opened sucessfully!", musicname);
}

void AudioEngine::processSoundRequests() {
	//process sounds
	Logger::info("Processing Sound requests...");
	for (auto& s : soundRequests) {
		Logger::info("Processing Request: {}", s.toString());

		if (s.start) {
			Logger::info("Playing sound {}", s.name);
			std::shared_ptr<sf::Sound> soundToPlay = std::make_unique<sf::Sound>();

			auto buffer = bufferMap.find(s.name);
			if (buffer == bufferMap.end()) {
				Logger::warn("Sound with name {} "
					"not loaded! Loading now...", s.name);
				std::shared_ptr<sf::SoundBuffer> loadBuffer;
				if (loadSound(s.name, loadBuffer)) {
					//soundToPlay.setBuffer(*loadBuffer);
					buffer = bufferMap.find(s.name);
					soundToPlay->setBuffer(*buffer->second);
				}
				else {
					Logger::error("Sound with name {} not found!"
						" Skipping request", s.name);
					continue;
				}
			}
			else {
				soundToPlay->setBuffer(*buffer->second);
			}


			auto soundMapEntry = playingSounds.find(s.name);
			if (soundMapEntry == playingSounds.end()) {
				auto emplace_val = std::make_shared<
					std::vector<std::shared_ptr<sf::Sound>>>();
				emplace_val->push_back(soundToPlay);
				playingSounds.emplace(s.name, emplace_val);
			}
			else {
				soundMapEntry->second->push_back(soundToPlay);
			}

			soundToPlay->setVolume(s.volume);
			soundToPlay->setPitch(s.pitch);
			soundToPlay->setLoop(s.repeat);
			soundToPlay->play();

			Logger::info("Sound {} started successfully!", s.name);
		}
		else {
			Logger::info("Stopping sound {}", s.name);

			auto soundMapEntry = playingSounds.find(s.name);
			if (soundMapEntry == playingSounds.end()) {
				Logger::warn("Sound {} was not playing!", s.name);
				continue;
			}
			else {
				auto vec = soundMapEntry->second;
				if (vec->empty()) {
					Logger::warn("Sound {} was not playing!", s.name);
					continue;
				}
				else {
					for (auto& s : *vec) {
						s->stop();
					}
				}
			}

			Logger::info("All instances of sound "
				"{} stopped successfully!", s.name);
		}
	}

	soundRequests.clear();
}

void AudioEngine::processMusicRequests() {
	//process music
	Logger::info("Processing Music requests...");
	for (auto& s : musicRequests) {
		Logger::info("Processing Request: {}", s.toString());

		if (s.start) {
			Logger::info("Playing Song {}", s.name);

			auto song_found = musicMap.find(s.name);
			std::shared_ptr<sf::Music> songToPlay;
			if (song_found == musicMap.end()) {
				Logger::warn("Song with name {} "
					"not loaded! Loading now...", s.name);
				std::shared_ptr<sf::Music> loadSong;
				if (loadMusic(s.name, loadSong)) {
					songToPlay = loadSong;
				}
				else {
					Logger::error("Song with name {} not found!"
						" Skipping request", s.name);
					continue;
				}
			}
			else {
				songToPlay = song_found->second;
			}




			auto musicMapEntry = playingMusic.find(s.name);
			if (musicMapEntry == playingMusic.end()) {
				playingMusic.emplace(s.name, songToPlay);

				songToPlay->setVolume(s.volume);
				songToPlay->setPitch(s.pitch);
				songToPlay->setLoop(s.repeat);
				songToPlay->play();
				Logger::info("Sound {} started successfully!", s.name);
			}
			else {
				songToPlay->setVolume(s.volume);
				songToPlay->setPitch(s.pitch);
				songToPlay->setLoop(s.repeat);
				Logger::warn("Song {} is already playing!", s.name);
			}


		}
		else {
			Logger::info("Stopping Song {}", s.name);

			auto songMapEntry = playingMusic.find(s.name);
			if (songMapEntry == playingMusic.end()) {
				Logger::warn("Music {} was not playing!", s.name);
				continue;
			}
			else {
				songMapEntry->second->stop();
			}

			Logger::info("Song {} stopped successfully!", s.name);
		}
	}

	musicRequests.clear();
}

bool AudioEngine::searchForSoundFile(const std::string& soundname, 
	fs::path& filepath) {
	
	//try wav, vorbis, and flac
	Logger::info("Searching for sound" 
		"file with name {}", soundname);

	filepath /= "resources";
	filepath /= "sounds";

	Logger::info("Searching in directory {}", filepath.string());

	filepath /= soundname;

	std::array<std::string, 3> extensions{ ".wav", ".ogg", ".flac" };
	for (auto& extension : extensions) {
		Logger::info("Searching for {} file...", extension);
		auto trypath = filepath;
		trypath += extension;
		if (fs::exists(trypath)) {
			filepath = trypath;
			Logger::info("sound file with name {} found at path {}",
				soundname, filepath.string());
			return true;
		}
		else {
			Logger::info("{} file not found, directory {} "
				"does not exist...", extension, trypath.string());
		}
	}

	Logger::warn("sound file with name {} not found!", 
		soundname);

	return false;
}

bool AudioEngine::searchForMusicFile(const std::string& musicname, 
	fs::path& filepath) {

	//try wav, vorbis, and flac
	Logger::info("Searching for music"
		"file with name {}...", musicname);

	filepath /= "resources";
	filepath /= "music";

	Logger::info("Searching in directory {}", filepath.string());

	filepath /= musicname;



	std::array<std::string, 3> extensions{ ".wav", ".ogg", ".flac" };
	for (auto& extension : extensions) {
		Logger::info("Searching for {} file...", extension);
		auto trypath = filepath;
		trypath += extension;
		if (fs::exists(trypath)) {
			filepath = trypath;
			Logger::info("Music file with name {} found at path {}",
				musicname, filepath.string());
			return true;
		}
		else {
			Logger::info("{} file not found, directory {} "
				"does not exist...", extension, trypath.string());
		}
	}

	Logger::warn("music file with name {} not found!",
		musicname);

	return false;
}
