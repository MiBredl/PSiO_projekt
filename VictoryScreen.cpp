#include "VictoryScreen.h"
#include "GameManager.h"

VictoryScreen::VictoryScreen(GameManager& _gameManager):MainMenu(_gameManager)
{
	m_GameManager = _gameManager;
	m_Texts.resize(m_Options.size());
	for (int i = 0; i < m_Options.size(); i++) {
		m_Texts[i].setFont(m_Font);
		m_Texts[i].setString(m_Options[i]);
	}
	m_Texts[0].setCharacterSize(200);
	m_Texts[1].setCharacterSize(75);

}

void VictoryScreen::handleInput()
{
	if (collider(m_Texts[1])) {
		m_Texts[1].setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left)) {
			m_GameManager.setCurrentWorld(1);
			m_GameManager.getMainMenu()->overrideChosen(GAME_ENUMS::GAMESTATE::RESTART);
		}
	}
	else m_Texts[1].setFillColor(Color::White);
}

void VictoryScreen::render()
{
	update();
	for (auto& text : m_Texts) {
		m_GameManager.getWindow()->draw(text);
	}
}

void VictoryScreen::update()
{
	Vector2i pixelPosMainText = {WINDOW_WIDTH/2-static_cast<int>(m_Texts[0].getGlobalBounds().width/2.f),50};
	Vector2i pixelPosText = { WINDOW_WIDTH /2- static_cast<int>(m_Texts[1].getGlobalBounds().width / 2),static_cast<int>(pixelPosMainText.y+m_Texts[0].getGlobalBounds().height+50) };
	Vector2f worldMain = m_GameManager.getWindow()->mapPixelToCoords(pixelPosMainText);
	Vector2f world2=m_GameManager.getWindow()->mapPixelToCoords(pixelPosText);
	

	m_Texts[0].setPosition(worldMain);
	m_Texts[1].setPosition(world2);
}
