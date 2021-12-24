#include "include.h"
#include "Sound.h"
#include "AudioRegistry.h"
#include "AudioEngine.h"

using namespace ic;

Sound::Sound(const std::string& buffername) {
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
