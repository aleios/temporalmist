#ifndef GAMESETTINGS_HPP
#define GAMESETTINGS_HPP

#include <string>
#include <SFML/Window/VideoMode.hpp>

struct GameSettings
{
	GameSettings(const sf::VideoMode& inWindowSettings, const std::string& inTitle = "", float inFramerate = 60.0f, float inFrameskip = 5.0f)
		: windowSettings(inWindowSettings), title(inTitle), framerate(inFramerate), frameskip(inFrameskip)
	{
	}

	std::string title;
	float framerate, frameskip;
	sf::VideoMode windowSettings;
};

#endif