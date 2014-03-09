/*#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Music;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		PlayerRun,
		PlayerIdle,
		PlayerSStep,
		WarriorRun,
		WarriorAttack,
		WarriorIdle,
		Player_Glove_Empty,
		Ranged_Needle,
		Ranged_Crossbow,
		Shadow,
		Shadow_Bump,
		Ground,
		Pause_BG,
		Prompt_BG,
		Button_1_Center,
		Button_1_End,
		Grain,
		Walls,
		Part_Star_01,
		Rope,
		Hidden_Wall,
	};
}

namespace Fonts
{
	enum ID
	{
		LITTLELO,
	};
}

namespace Music
{
	enum ID
	{
		MenuTheme,
		InGameTheme,
	};
}

namespace SFX
{
	enum ID
	{
		Cymbal_Hit_01,
		Cymbal_Hit_02,
		Cymbal_Hit_03,
		Button_Hover,
		Button_Click,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SFX::ID> SoundBufferHolder;

#endif // RESOURCEIDENTIFIERS_HPP
*/