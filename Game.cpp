#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game() :
mWindow(sf::VideoMode(640, 380, 32), "AIGames")
, mWorld()
, mPlayer()
{
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();       
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::update(sf::Time dt)
{
    mWorld.update(dt);
}

void Game::render()
{
    mWindow.clear(sf::Color::Blue);
    mWorld.draw(mWindow);
    mWindow.display();
}

void Game::processInput()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        mPlayer.handleEvent(event);

        if(event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::W && isPressed)
    {
    }
}
