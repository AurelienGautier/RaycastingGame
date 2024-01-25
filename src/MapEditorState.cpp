#include "header/MapEditorState.h"

MapEditorState::MapEditorState(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game, std::string mapName) :
    State(gameWindow, game),
    map("res/map/" + mapName)
{
    this->initInterface();

    this->mapView.setCenter(
        this->window->getSize().x / 2,
        this->window->getSize().y * 0.84 / 2
    );

	this->mapView.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y * 0.84));
	this->mapView.setViewport(sf::FloatRect(0, 0.16, 1, 0.84));
}

/*-------------------------------------------------------------------------------*/

MapEditorState* MapEditorState::instance = nullptr;

MapEditorState* MapEditorState::getInstance(std::shared_ptr<sf::RenderWindow> gameWindow, Game* game, std::string mapName)
{
    if(instance == nullptr)
	{
		instance = new MapEditorState(gameWindow, game, mapName);
	}

	return instance;
}

/*-------------------------------------------------------------------------------*/

MapEditorState::~MapEditorState()
{
    delete this->saveButton;
    delete this->exitButton;
    delete this->changeSizeButton;
}

/*-------------------------------------------------------------------------------*/

void MapEditorState::initInterface()
{
    this->interfaceView.setCenter(sf::Vector2f(
        this->window->getSize().x / 2,
        this->window->getSize().y * 0.16 / 2
    ));

    this->interfaceView.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y * 0.16));
    this->interfaceView.setViewport(sf::FloatRect(0, 0, 1, 0.16));

    this->exitButton = new Button(sf::Vector2f(0, 0), "Exit", 32);
    this->saveButton = new Button(sf::Vector2f(0, 40), "Save", 32);
    this->changeSizeButton = new Button(sf::Vector2f(100, 0), "Change dimensions", 32);
}

/*-------------------------------------------------------------------------------*/

void MapEditorState::update()
{
    this->updateKeyboardInputs();
    this->updateMouse();
    this->updateInterface();
}

/*-------------------------------------------------------------------------------*/

void MapEditorState::updateInterface()
{
    this->window->setView(this->interfaceView);

    sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    this->updateButtons();
}

/*-------------------------------------------------------------------------------*/

void MapEditorState::updateButtons()
{
    sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    this->exitButton->update();

    if(this->exitButton->isClicked(mousePosition))
    {
        this->window->setView(this->window->getDefaultView());
        this->game->setState(MainMenuState::getInstance(this->window, this->game));
    }

    this->saveButton->update();

    if(this->saveButton->isClicked(mousePosition))
    {
        this->map.save();
    }

    this->changeSizeButton->update();
}

/*-------------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------------*/

void MapEditorState::render()
{
    this->renderInterface();

    this->window->setView(this->mapView);

    this->map.render(*this->window);

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

/*-------------------------------------------------------------------------------*/

void MapEditorState::renderInterface()
{
    this->window->setView(this->interfaceView);

    this->exitButton->render(*this->window);

    this->saveButton->render(*this->window);

    this->changeSizeButton->render(*this->window);
}

/*-------------------------------------------------------------------------------*/

