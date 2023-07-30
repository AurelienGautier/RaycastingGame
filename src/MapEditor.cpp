#include "header/MapEditorState.h"
#include <iostream>

MapEditorState::MapEditorState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::map<States, std::unique_ptr<State>>> states) :
    State(gameWindow, states),
    map("res/map/level1")
{
    sf::Vector2f windowCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);

    this->view.setCenter(windowCenter);
	this->view.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->view.setViewport(sf::FloatRect(0, 0, 1, 1));
}

void MapEditorState::update()
{
    this->updateKeyboardInputs();
    this->updateMouse();
}

void MapEditorState::updateKeyboardInputs()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->view.move(-10, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->view.move(10, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->view.move(0, -10);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->view.move(0, 10);
}

void MapEditorState::updateMouse()
{
}

void MapEditorState::render()
{
    this->map.render(*this->window, this->view);

    sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    int cellSize = this->map.getCellsize();

    sf::RectangleShape tileSelected(sf::Vector2f(cellSize, cellSize));
    tileSelected.setFillColor(sf::Color::White);
    tileSelected.setPosition(
        floor(mousePosition.x / cellSize) * cellSize , 
        floor(mousePosition.y / cellSize) * cellSize
    );

    this->window->draw(tileSelected);
}