#include "header/MapEditorState.h"

MapEditorState::MapEditorState(std::shared_ptr<sf::RenderWindow> gameWindow, std::shared_ptr<std::stack<std::unique_ptr<State>>> states) :
    State(gameWindow, states),
    map("res/map/level1")
{
    this->initInterface();

    this->mapView.setCenter(
        this->window->getSize().x / 2,
        this->window->getSize().y * 0.84 / 2
    );

	this->mapView.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y * 0.84));
	this->mapView.setViewport(sf::FloatRect(0, 0.16, 1, 0.84));
}

void MapEditorState::initInterface()
{
    this->interfaceView.setCenter(sf::Vector2f(
        this->window->getSize().x / 2,
        this->window->getSize().y * 0.16 / 2
    ));

    this->interfaceView.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y * 0.16));
    this->interfaceView.setViewport(sf::FloatRect(0, 0, 1, 0.16));

    this->exitButton.initButton(sf::Vector2f(0, 0), "Exit", 32);
    this->saveButton.initButton(sf::Vector2f(0, 40), "Save", 32);
}

void MapEditorState::update()
{
    this->updateKeyboardInputs();
    this->updateMouse();
    this->updateInterface();
}

void MapEditorState::updateInterface()
{
    this->window->setView(this->interfaceView);

    this->updateButtons();
}

void MapEditorState::updateButtons()
{
    sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    this->exitButton.update();

    if(this->exitButton.isClicked(mousePosition))
    {
        this->deleteState();
    }

    this->saveButton.update();

    if(this->saveButton.isClicked(mousePosition))
    {
        this->map.save();
    }
}

void MapEditorState::updateKeyboardInputs()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->mapView.move(0, -10);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->mapView.move(-10, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->mapView.move(0, 10);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->mapView.move(10, 0);
}

void MapEditorState::updateMouse()
{
    this->window->setView(this->mapView);
    sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->map.changeCell(
            floor(mousePosition.x / this->map.getCellsize()),
            floor(mousePosition.y / this->map.getCellsize()),
            CellType::WALL
        );
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        this->map.changeCell(
            floor(mousePosition.x / this->map.getCellsize()),
            floor(mousePosition.y / this->map.getCellsize()),
            CellType::EMPTY
        );
    }
}

void MapEditorState::render()
{
    this->renderInterface();

    this->window->setView(this->mapView);

    this->map.render(*this->window, this->mapView);

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

void MapEditorState::renderInterface()
{
    this->window->setView(this->interfaceView);

    this->exitButton.render(*this->window);

    this->saveButton.render(*this->window);
}