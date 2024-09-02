#include "assetManager.hpp"

Engine::assetMan::assetMan()
{
}

Engine::assetMan::~assetMan()
{
}

void Engine::assetMan::loadTexture(int id, const std::string &filePath, bool wantRepeated)
{
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(filePath)) //if successfully loaded texture move ownership of the unique_ptr
    {
        texture->setRepeated(wantRepeated); //This only works if your sprite is configured to show a rectangle which is larger than the texture, otherwise this property has no effect
        m_textures[id] = std::move(texture); 
    }
}

void Engine::assetMan::loadFont(int id, const std::string &filePath)
{
    auto font = std::make_unique<sf::Font>();

    if (font->loadFromFile(filePath))
    {
        m_fonts[id] = std::move(font);
    }
}

void Engine::assetMan::loadAudio(bool type, int id, const std::string &filePath) //types: 0 = music, 1 = soundeffect //SFML supports .wav but not .mp3
{
    if(type) //for  sound
    {
        sf::SoundBuffer soundBuffer; //because only SoundBuffer has loadFromFile method
        if (soundBuffer.loadFromFile(filePath))
        {
            auto soundEffect = std::make_unique<sf::Sound>();
            soundEffect->setBuffer(soundBuffer);
            m_soundEffects[id] = std::move(soundEffect); //Before destroying, we move the ownership to the map, which destroys it 
        } //else error
    }
    else //for music
    {
        auto music = std::make_unique<sf::Music>();
        if (music->openFromFile(filePath))
        {
            m_music[id] = std::move(music);
        }
    }

}


//these return the blocks where the assets are stored
const sf::Texture &Engine::assetMan::getTexture(int id) const
{
    return *(m_textures.at(id).get());
}

const sf::Font &Engine::assetMan::getFont(int id) const
{
    return *(m_fonts.at(id).get());
}

const sf::Sound &Engine::assetMan::getSoundEffect(int id) const
{
    return *(m_soundEffects.at(id).get()); //sf::Sound sound; sound.setBuffer(soundBuffer); sound.play(); //see music
}

const sf::Music &Engine::assetMan::getMusic(int id) const
{
    return *(m_music.at(id).get()); //sf::Music music; music.play(); music.stop(); music.setVolume(0-100); //same for sound
}   //music is a mass noun