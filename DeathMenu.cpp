#include "DeathMenu.h"
#include"GameManager.h"
DeathMenu::DeathMenu(GameManager& _GameManager) : m_GameManager(_GameManager)
{
	if (!font.loadFromFile("Fonts/doomed.ttf")) {}
	for (int i = 0; i < 2; i++) {
		texts[i].setFont(font);
		texts[i].setString(m_OptionText[i]);
	}
	
	
	texts[0].setCharacterSize(200);
	texts[0].setPosition(WINDOW_WIDTH/2-texts[0].getGlobalBounds().width/2,WINDOW_HEIGHT/6);
	texts[0].setFillColor(Color::Red);
	texts[1].setCharacterSize(50);
	texts[1].setPosition(WINDOW_WIDTH / 2 - texts[1].getGlobalBounds().width, WINDOW_HEIGHT/2 - texts[1].getGlobalBounds().height);
}

void DeathMenu::handleInput()
{
	Vector2i _mousePos = Mouse::getPosition();
	cout << "handle\n";
	if (texts[1].getGlobalBounds().left <= _mousePos.x
		&& texts[1].getGlobalBounds().left + texts[1].getGlobalBounds().width >= _mousePos.x
		&& texts[1].getGlobalBounds().top <= _mousePos.y - 10
		&& texts[1].getGlobalBounds().top + texts[1].getGlobalBounds().height >= _mousePos.y - 30) {
		texts[1].setFillColor(Color::Magenta);
		texts[1].setScale(2,2);
		if (Mouse::isButtonPressed(Mouse::Left)) {
			//m_GameManager.getMainMenu()->overrideChosen(GAME_ENUMS::GAMESTATE::RESTART);
		}
	}
	else {
		texts[1].setFillColor(Color::White);
		texts[1].setScale(1,1);
	}
}

void DeathMenu::render()
{
	
	for (auto& text : texts) {
		m_GameManager.getWindow()->draw(text);
	}
}
