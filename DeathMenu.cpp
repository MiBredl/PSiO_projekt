#include "DeathMenu.h"
#include"GameManager.h"
DeathMenu::DeathMenu(GameManager& _GameManager) : m_GameManager(_GameManager),alpha(0)
{
	if (!font.loadFromFile("Fonts/doomed.ttf")) {}
	for (int i = 0; i < 2; i++) {
		texts[i].setFont(font);
		texts[i].setString(m_OptionText[i]);
	}
	
	
	texts[0].setCharacterSize(250);
	//texts[0].setPosition(WINDOW_WIDTH/2-texts[0].getGlobalBounds().width/2,WINDOW_HEIGHT/6);
	texts[0].setFillColor(Color::Red);
	texts[1].setCharacterSize(50);
	//texts[1].setPosition(WINDOW_WIDTH / 2 - texts[1].getGlobalBounds().width, WINDOW_HEIGHT/2 - texts[1].getGlobalBounds().height);
}

void DeathMenu::handleInput()
{
	sf::Vector2i _mousePos = sf::Mouse::getPosition();
	sf::Vector2f worldMousePos = m_GameManager.getWindow()->mapPixelToCoords(_mousePos);
	cout << "handle\n";
	if (texts[1].getGlobalBounds().left <= worldMousePos.x
		&& texts[1].getGlobalBounds().left + texts[1].getGlobalBounds().width >= worldMousePos.x
		&& texts[1].getGlobalBounds().top <= worldMousePos.y - 10
		&& texts[1].getGlobalBounds().top + texts[1].getGlobalBounds().height >= worldMousePos.y - 30) {
		texts[1].setFillColor(Color::Magenta);
		texts[1].setScale(2,2);
		isOver = true;
		if (Mouse::isButtonPressed(Mouse::Left)) {
			m_GameManager.getMainMenu()->overrideChosen(GAME_ENUMS::GAMESTATE::RESTART);
		}
	}
	else {
		isOver = false;
		//texts[1].setFillColor(Color::White);
		texts[1].setScale(1,1);
	}
}

void DeathMenu::render()
{
	viewUpdate();
	handleInput();
	for (auto& text : texts) {
		if (alpha <= 254) alpha++;
		 text.setFillColor(Color(0,0,0,alpha));
		m_GameManager.getWindow()->draw(text);
	}
}

void DeathMenu::viewUpdate()
{
	
	sf::Vector2i pixelPos0(WINDOW_WIDTH / 2 - texts[0].getGlobalBounds().width / 2, WINDOW_HEIGHT / 6);
	sf::Vector2i pixelPos1(WINDOW_WIDTH / 2 - texts[1].getGlobalBounds().width/2, WINDOW_HEIGHT / 2 - texts[1].getGlobalBounds().height);
	sf::Vector2f worldPos0= m_GameManager.getWindow()->mapPixelToCoords(pixelPos0);
	sf::Vector2f worldPos1 = m_GameManager.getWindow()->mapPixelToCoords(pixelPos1);
	texts[0].setPosition(worldPos0);
	texts[1].setPosition(worldPos1);
	
	
}
