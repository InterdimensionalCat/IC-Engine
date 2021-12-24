#pragma once

namespace ic {
	class Music {
	public:
		Music(const std::string& soundname);
		~Music();
		void setPitch(const float pitch);
		void setVolume(const float volume);
		void play();
		sf::SoundSource::Status getStatus() const;

	private:
		sf::Music music;
	};
}