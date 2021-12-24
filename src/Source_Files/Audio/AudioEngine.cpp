#include "include.h"
#include "AudioEngine.h"


using namespace ic;

void AudioEngine::update() {
	std::erase_if(currentSounds, [](const auto& elt) {
		auto const& [key, value] = elt;
		return value.getStatus() != sf::SoundSource::Status::Playing;
		}
	);
}

sf::SoundSource::Status AudioEngine::getStatusOfSound(const std::string& soundName) {
	auto found = currentSounds.find(soundName);
	if (found != currentSounds.end()) {
		return found->second.getStatus();
	}
	else {
		return sf::SoundSource::Status::Stopped;
	}
}

void AudioEngine::playSound(const std::string& soundName, const float volume, const float pitch, const bool repeat) {
	currentSounds.emplace(soundName, Sound(soundName));
	Sound& soundToPlay = currentSounds.find(soundName)->second;
	soundToPlay.setVolume(volume);
	soundToPlay.setPitch(pitch);
	soundToPlay.setLoop(repeat);
	soundToPlay.play();
}

void AudioEngine::playMusic(const std::string& musicName, const float volume, const float pitch, const bool repeat) {
	if (currentSong.get() != nullptr) {
		currentSong->stop();
	}

	currentSong = getMusicFromName(musicName);

	currentSong->setVolume(volume);
	currentSong->setPitch(pitch);
	currentSong->setLoop(repeat);
	currentSong->play();
}


AudioEngine::AudioEngine() : bufferMap(std::map<std::string, std::shared_ptr<sf::SoundBuffer>>()),
    musicMap(std::map<std::string, std::shared_ptr<sf::Music>>()), currentSong(std::shared_ptr<sf::Music>(nullptr)),
    currentSounds(std::map<std::string, Sound>()) {
}

AudioEngine::~AudioEngine() {

}

void AudioEngine::clearLoadedAudio() {
	bufferMap.clear();
	musicMap.clear();
}

void AudioEngine::loadSound(const std::string& soundname) {

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

void AudioEngine::loadMusic(const std::string& musicname) {

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


		
std::shared_ptr<sf::SoundBuffer> AudioEngine::getBufferFromName(const std::string& buffername) {
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

std::shared_ptr<sf::Music> AudioEngine::getMusicFromName(const std::string& musicname) {
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