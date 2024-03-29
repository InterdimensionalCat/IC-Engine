#include "include.h"
#include "AudioEngine.h"
#include "AudioRegistry.h"


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