#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

namespace Engine
{
    class assetMan
    {
    public:
        assetMan();
        ~assetMan();

        void loadTexture(int id, const std::string &filePath, bool wantRepeated = false); //id can be replaced by string to represent make it easier to represent in code
        void loadFont(int id, const std::string &filePath);
        void loadAudio(bool type, int id, const std::string &filePath); //types: 0 = music, 1 = soundeffect //music is much bigger than sound effects
        

        const sf::Texture &getTexture(int id) const;
        const sf::Font &getFont(int id) const;
        const sf::Sound &getSoundEffect(int id) const;
        const sf::Music &getMusic(int id) const;

    private:
        //we make it a unique ptr because the size of the texture may vary
        std::map<int, std::unique_ptr<sf::Texture>> m_textures;
        std::map<int, std::unique_ptr<sf::Font>> m_fonts;
        std::map<int, std::unique_ptr<sf::Sound>> m_soundEffects; //sound effects map
        std::map<int, std::unique_ptr<sf::Music>> m_music; //music map
    };
}
