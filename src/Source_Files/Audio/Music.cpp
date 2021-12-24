#include "include.h"
#include "Music.h"
#include "AudioEngine.h"

using namespace ic;

Music::Music(const std::string& buffername) {
	auto engine = AudioEngine::get();
	buffer = std::shared_ptr<sf::SoundBuffer>(engine->getBufferFromName(buffername));
	sound.setBuffer(*buffer);
}

void Sound::setPitch(const float pitch) {
	sound.setPitch(pitch);
}

void Sound::setVolume(const float volume) {
	sound.setVolume(volume);
}

void Sound::play() {
	sound.play();
}

sf::SoundSource::Status Sound::getStatus() const {
	return sound.getStatus();
}

void Sound::setLoop(const bool loop) {
	sound.setLoop(loop);
}