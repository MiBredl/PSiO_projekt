#include "UpgradeMenu.h"
#include "GameManager.h"


UpgradeMenu::UpgradeMenu(GameManager& _GameManager) : m_GameManager(_GameManager)
{
	if (!m_Font.loadFromFile("Fonts/Roboto-BlackItalic.ttf")) {
		cerr << "UpgradeMenu font loading error\n";
	}


	m_ButtonSprites.resize(4);
	m_ButtonTextures.resize(m_SpriteQuantity);
	m_UpgradeTexts.resize(m_UpgradeStrings.size());

	for (int i = 0; i < m_SpriteQuantity; i++) {
		m_ButtonTextures[i].loadFromFile(m_TexturePaths[i]); 
	}
	for (int i = 0; i < 4; i++) {
		m_ButtonSprites[i].setTexture(m_ButtonTextures[i % m_ButtonTextures.size()]);
		m_ButtonSprites[i].setScale(0.15, 0.15);
		m_ButtonSprites[i].setOrigin(m_ButtonSprites[i].getLocalBounds().width / 2.0f, m_ButtonSprites[i].getLocalBounds().height / 2.0f);
		if (i % 2 != 0) { 
			m_ButtonSprites[i].rotate(180);
		}
	}

}

void UpgradeMenu::handleInput()
{
	Player& _player = *m_GameManager.getPlayer();
	sf::Vector2i _mousePos = sf::Mouse::getPosition();
	sf::Vector2f worldMousePos = m_GameManager.getWindow()->mapPixelToCoords(_mousePos);
	
	for (int i = 0; i < m_ButtonSprites.size(); i++) {
		FloatRect _buttonBounds = m_ButtonSprites[i].getGlobalBounds();
		if (_buttonBounds.left <= worldMousePos.x
			&& _buttonBounds.left + _buttonBounds.width >= worldMousePos.x
			&& _buttonBounds.top <= worldMousePos.y - 10
			&& _buttonBounds.top + _buttonBounds.height >= worldMousePos.y - 30) {
			m_ButtonSprites[i].setColor(sf::Color(0, 0, 0, 130));
			if (Mouse::isButtonPressed(Mouse::Left)) {
				switch (i) {
					
				case GAME_ENUMS::UPGRADE_BUTTONS::HP_UP:
					if (_player.m_Exp > 0 && !m_isOnCoolDown) {
						_player.m_Exp--;
						_player.m_HP++; 
						m_isOnCoolDown = true;
						m_CoolDown = 30;
					}
				}
			}
		}
		else {
			m_ButtonSprites[i].setColor(sf::Color::White);
		}
	}
	if (m_CoolDown == 0) m_isOnCoolDown = false;
	else m_CoolDown--;
}

void UpgradeMenu::viewUpdate()
{
	

	float yPosition = WINDOW_HEIGHT / 2.0f;

	for (int i = 0; i < m_ButtonSprites.size(); i++) {
		sf::Vector2i pixelPos;
		if (i == 0 || i == 1)
			pixelPos = { static_cast<int>(yPosition) + i * m_BetweenWidth, static_cast<int>(yPosition) };
		else
			pixelPos = { static_cast<int>(yPosition) + (i - 2) * m_BetweenWidth, static_cast<int>(yPosition) - 40 };
		sf::Vector2f worldPos = m_GameManager.getWindow()->mapPixelToCoords(pixelPos);
		m_ButtonSprites[i].setPosition(worldPos);
	}



}

void UpgradeMenu::render()
{
	
	
	viewUpdate();
	handleInput();
	for (auto& button : m_ButtonSprites) {
		m_GameManager.getWindow()->draw(button);
	}
	
}
