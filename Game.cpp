#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game(int width, int height) :
mWindow(sf::VideoMode(width, height, 32), "AIGames")
, mWorld(width, height)
, inputState(InputState::NONE)
, previousEnt(NULL)
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
        if(event.type == sf::Event::Closed)
            mWindow.close();

        if(event.type == sf::Event::Resized) {
            mWindow.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
            mWorld.deleteWorld();
            mWorld.createWorld(event.size.width, event.size.height);
        }

        handleInput(event);
    }
}

void Game::handleInput(sf::Event event)
{
    // Keyboard Input Stuff
    

    // Mouse Input Stuff
    sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
    Entity* ent = mWorld.getEntityAtPosition(mousePosition.x, mousePosition.y);

    if(ent != NULL) {
        //ent->setColor(sf::Color::Green);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            switch(inputState) {
                case InputState::NONE:
                    if(ent->isWall())
                        inputState = InputState::REMOVE;
                    else
                        inputState = InputState::ADD;

                    if(ent->isStart())
                        inputState = InputState::MOVE_START;
                    if(ent->isEnd())
                        inputState = InputState::MOVE_GOAL;
                    break;

                case InputState::ADD:
                    if(!ent->isWall() && !ent->isStart() && !ent->isEnd()) {
                        ent->setWall(true);
                        ent->setColor(NODE_BLOCKED);
                    }
                    break;

                case InputState::REMOVE:
                    if(ent->isWall() && !ent->isStart() && !ent->isEnd()) {
                        ent->setWall(false);
                        ent->setColor(NODE_FREE);
                    }
                    break;

                case InputState::MOVE_START:
                    if(previousEnt == NULL) {
                        previousEnt = ent;
                    }

                    if(previousEnt != ent && !ent->isEnd()) {
                        previousEnt->setStart(false);
                        if(previousEnt->isWall()) {
                            previousEnt->setColor(NODE_BLOCKED);
                        } else {
                            previousEnt->setColor(NODE_FREE);
                        }

                        ent->setStart(true);
                        ent->setColor(NODE_START);
                        previousEnt = ent;
                    }
                    break;

                case InputState::MOVE_GOAL:
                    if(previousEnt == NULL) {
                        previousEnt = ent;
                    }

                    if(previousEnt != ent && !ent->isStart()) {
                        previousEnt->setEnd(false);
                        if(previousEnt->isWall()) {
                            previousEnt->setColor(NODE_BLOCKED);
                        } else {
                            previousEnt->setColor(NODE_FREE);
                        }

                        ent->setEnd(true);
                        ent->setColor(NODE_GOAL);
                        previousEnt = ent;
                    }
                    break;

                default:
                    inputState = InputState::NONE;
                    break;
            }
        } else {
            inputState = InputState::NONE;
            previousEnt = NULL;
        }
    }
}
