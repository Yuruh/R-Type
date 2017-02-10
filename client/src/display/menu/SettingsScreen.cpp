//
// Created by babou on 17/12/16.
//

#include "display/menu/SettingsScreen.hpp"
#ifdef __linux__
#include <unistd.h>
#endif
#include <thread>
#include <display/IDisplay.hpp>

SettingsScreen::SettingsScreen(WindowSfml *window) :
        AScene(SoundManager::MENU),
        background(TextureManager::get(TextureManager::BACKGROUND_MENU)),
        box(TextureManager::get(TextureManager::BOX_SETTINGS)),
        background_gauge(TextureManager::get(TextureManager::BACKGROUND_GAUGE))
{
    this->window = window;

    for (size_t pos = 0; pos < 3; pos += 1)
        buttons[0].push_back(new Button(TextureManager::get(TextureManager::TEXT_BOX), TextureManager::get(TextureManager::TEXT_BOX_HV)));
    buttons[0].push_back(new Button(TextureManager::get(TextureManager::BACK_NM), TextureManager::get(TextureManager::BACK_HV)));

    const std::string   text[3] = { "Music", "Mute music", "Resolution"};
    const int           sizeText[3] = {33, 25, 24};
    const float         posButton[4][4] = { {0.265f, 0.504f},     // Music
                                            {0.265f, 0.550f},     // Mute music
                                            {0.265f, 0.754f},     // Resolution
                                            {0.255f, 0.824f} };   // Back

    for (size_t i = 0; i < buttons[0].size(); i += 1)
    {
        buttons[0][i]->move(WIN_X * posButton[i][0], WIN_Y * posButton[i][1]);
        if (i < buttons[0].size() - 1)
            buttons[0][i]->setText(text[i], sizeText[i]);
    }
    buttons[0][0]->setSelected(true);

    buttons[1].push_back(new Button(TextureManager::get(TextureManager::FILLED_GAUGE), TextureManager::get(TextureManager::FILLED_GAUGE)));
    buttons[1].push_back(new Button(TextureManager::get(TextureManager::UNCHECKED_BOX), TextureManager::get(TextureManager::CHECKED_BOX)));
    //buttons[1].push_back(new Button(TextureManager::get(TextureManager::UNCHECKED_BOX), TextureManager::get(TextureManager::CHECKED_BOX)));

    const float posCheckedBox[2] = { 0.557f,     // CheckedBox Mute music {0.395, 0.557}
                                     0.761f };   // CheckedBox Fullscreen {0.395, 0.761}

    for (size_t i = 1; i < buttons[1].size(); i += 1)
        buttons[1][i]->move(WIN_X * 0.395f, WIN_Y * posCheckedBox[i - 1]);

    const std::string   key[5] = {"Z / UP", "Q / LEFT", "S / DOWN", "D / RIGHT", "SPACE"};
    const float         posKey[5][5] = { {0.385f, 0.233f},    // Up
                                         {0.385f, 0.289f},    // Left
                                         {0.640f, 0.233f},    // Down
                                         {0.640f, 0.289f},    // Right
                                         {0.385f, 0.344f} };  // Space

    font.loadFromFile("assets/rtype_font.ttf");
    for (size_t i = 0; i < 5; i += 1)
    {
        keyboard.push_back(sf::Text(key[i], font, 35));
        keyboard[i].setPosition(WIN_X * posKey[i][0], WIN_Y * posKey[i][1]);
    }

    pos_res = 3;
    window->setSize(sf::Vector2u(size_res[pos_res][0], size_res[pos_res][1]));
    resolution = sf::Text("< " + std::to_string(window->getSize().x) + " x " + std::to_string(window->getSize().y) + " >", font, 30);
    resolution.setPosition(WIN_X * 0.395f, WIN_Y * 0.749f);

    background_gauge.setPosition(WIN_X * 0.393f, WIN_Y * 0.514f);
    count = 0;
    music_gauge = 20.0;
    old_music = 0.0;
    music_text = sf::Text(std::to_string(int(music_gauge)), font, 22);
    music_text.setPosition(WIN_X * 0.504f, WIN_Y * 0.506f);
}

SettingsScreen::~SettingsScreen()
{
}

void  SettingsScreen::update(float deltaTime)
{
    for (size_t j = 0; j < 2; j += 1)
        for (size_t i = 0; i < buttons[j].size(); i++)
            buttons[j][i]->addTime(deltaTime);
}

void  SettingsScreen::useButtonEvent(const ButtonEvent &buttonEvent)
{
    if (count == 0 && music_gauge != -1)
    {
        // Upper/Lower sound
        if (buttonEvent.getButtonType() == RIGHT && music_gauge < 100)
            SoundManager::Instance().setVolumeMusic(++music_gauge);
        if (buttonEvent.getButtonType() == LEFT && music_gauge > 0)
            SoundManager::Instance().setVolumeMusic(--music_gauge);
        music_text.setString(std::to_string(int(music_gauge)));
    }

    if (count == 1 && buttonEvent.getButtonType() == RETURN && buttons[1][count]->isReady())
    {
        // Mute sound
        if (buttons[1][count]->isActive() == false)
        {
            old_music = music_gauge;
            music_gauge = -1;
            music_text.setString("0");
            SoundManager::Instance().setVolumeMusic(0);
            buttons[1][count]->setSelected(true);
        }

        else if (buttons[1][count]->isActive() == true)
        {
            music_gauge = old_music;
            music_text.setString(std::to_string(int(music_gauge)));
            SoundManager::Instance().setVolumeMusic(music_gauge);
            buttons[1][count]->setSelected(false);
        }
    }

    if (count == 2)
    {
        // Resolution screen
        // TODO: Essayer de voir pour pouvoir ON/OFF l'écran en fullscreen
        if (buttonEvent.getButtonType() == LEFT && pos_res > 0)
        {
            this->window->setSize(sf::Vector2u(size_res[pos_res][0], size_res[--pos_res][1]));
            resolution.setString("< " + std::to_string(window->getSize().x) + " x " + std::to_string(window->getSize().y) + " >");
        }
        if (buttonEvent.getButtonType() == RIGHT && pos_res < 4)
        {
            this->window->setSize(sf::Vector2u(size_res[pos_res][0], size_res[++pos_res][1]));
            resolution.setString("< " + std::to_string(window->getSize().x) + " x " + std::to_string(window->getSize().y) + " >");
        }
		std::this_thread::sleep_for(std::chrono::microseconds(100000));
        //usleep(100000);
    }

    if (count == 3 && buttonEvent.getButtonType() == RETURN && buttons[0][count]->isReady())
    {
        // Go to old screen
        buttons[0][count]->setSelected(true);
        setActive(false);
        if (links.find(CHOOSE_GAME) != links.end())
            links[CHOOSE_GAME]->setActive(true);
    }

    if (buttonEvent.getButtonType() == UP && count > 0 && buttons[0][count]->isReady())
    {
        buttons[0][count--]->setSelected(false);
        buttons[0][count]->setSelected(true);
    }
    if (buttonEvent.getButtonType() == DOWN && count < this->buttons[0].size() - 1 && buttons[0][count]->isReady())
    {
        buttons[0][count++]->setSelected(false);
        buttons[0][count]->setSelected(true);
    }
}

void  SettingsScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(background);
    target.draw(box);
    for (size_t i = 0; i < buttons[0].size(); i++)
        target.draw(*buttons[0][i]);
    target.draw(resolution);
    target.draw(music_text);

    // Keyboard settings
    for (size_t i = 0; i < keyboard.size(); i += 1)
        target.draw(keyboard[i]);

    // Sound settings
    target.draw(background_gauge);
    for (size_t i = 1; i < buttons[1].size(); i++)
        target.draw(*buttons[1][i]);
    if (music_gauge != -1)
        for (int pos = 0; pos < music_gauge; pos += 1)
        {
            buttons[1][0]->setPosition((WIN_X * 0.395f) + (pos * 1.85f), WIN_Y * 0.5162f);
            target.draw(*buttons[1][0]);
        }
}
