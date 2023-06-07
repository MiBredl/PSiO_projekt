#include "UpgradeMenu.h"
#include "GameManager.h"


UpgradeMenu::UpgradeMenu(GameManager& _GameManager) : m_GameManager(_GameManager)
{
	if (!m_Font.loadFromFile("Fonts/Roboto-BlackItalic.ttf")) {
		cerr << "UpgradeMenu font loading error\n";
	}


	m_ButtonSprites.resize(buttonQuantity);
	m_ButtonTextures.resize(m_SpriteQuantity);
	m_UpgradeTexts.resize(m_UpgradeStrings.size());
	
	m_ScrollTextures.resize(m_ScrollsQuantity);
	
	textSetUp();



	for (int i = 0; i < m_ScrollsQuantity; i++) {
		m_ScrollTextures[i].loadFromFile(m_ScrollTexturePaths[i]);
		
	}
	for (int i = 0; i < m_SpriteQuantity; i++) {
		m_ButtonTextures[i].loadFromFile(m_TexturePaths[i]); 
	}


	for (int i = 0; i < buttonQuantity-1; i++) {
		m_ButtonSprites[i].setTexture(m_ButtonTextures[i % (m_ButtonTextures.size()-1)]);
		m_ButtonSprites[i].setScale(0.15, 0.15);
		m_ButtonSprites[i].setOrigin(m_ButtonSprites[i].getLocalBounds().width / 2.0f, m_ButtonSprites[i].getLocalBounds().height / 2.0f);
		if (i % 2 != 0) { 
			m_ButtonSprites[i].rotate(180);
		}
		
	}
	m_ButtonSprites[4].setTexture(m_ButtonTextures[2]);
	m_ButtonSprites[4].setScale(0.15, 0.15);
}

void UpgradeMenu::handleInput()
{
	
	FloatRect _scrollBounds = m_Scroll->getGlobalBounds();
	
	if (collider(_scrollBounds)) {
		//cout << "SCROLLLLLL\n";
		if (Mouse::isButtonPressed(Mouse::Left) && Closed) {
			m_isOpen = true;
			//previousOpen = m_isOpen;
		}
	}
	
}

void UpgradeMenu::buttonsUpdate()
{
	

	float yPosition = WINDOW_HEIGHT / 2.75f;
	float xPosition = WINDOW_WIDTH / 2.0f;
	Vector2f _BackButtonPos = {(scrollBounds.left+scrollBounds.width)/2.f-m_ButtonSprites[GAME_ENUMS::UPGRADE_BUTTONS::BACK].getGlobalBounds().width/4
		,scrollBounds.top+540};
	for (int i = 0; i < m_ButtonSprites.size()-1; i++) {
		sf::Vector2i pixelPos;
		if (i<2)
			pixelPos = { static_cast<int>(xPosition) + i * m_BetweenWidth, static_cast<int>(yPosition) };
		else if(i<4)
			pixelPos = { static_cast<int>(xPosition) + (i - 2) * m_BetweenWidth, static_cast<int>(yPosition) - 40 };
		sf::Vector2f worldPos = mapToCords(pixelPos);
		m_ButtonSprites[i].setPosition(worldPos);

		
	}
	m_ButtonSprites[GAME_ENUMS::UPGRADE_BUTTONS::BACK].setPosition(_BackButtonPos);

	

}

void UpgradeMenu::textSetUp()
{

	
	for (int i = 0; i < m_UpgradeTexts.size();i++) {
		m_UpgradeTexts[i].setString(m_UpgradeStrings[i]);
		m_UpgradeTexts[i].setFont(m_Font);
		m_UpgradeTexts[i].setFillColor(Color::Black);
	}

	m_UpgradeTexts[UPGRADE_TEXT::EXP].setCharacterSize(30);
	m_UpgradeTexts[UPGRADE_TEXT::OPTIONS].setCharacterSize(40);
	m_UpgradeTexts[UPGRADE_TEXT::STRENGHT].setCharacterSize(20);
	m_UpgradeTexts[UPGRADE_TEXT::HP].setCharacterSize(20);
}

void UpgradeMenu::viewUpdateTexts()
{
	 
	FloatRect optionsTextBounds = m_UpgradeTexts[UPGRADE_TEXT::OPTIONS].getGlobalBounds();
	FloatRect EXPTextBounds = m_UpgradeTexts[UPGRADE_TEXT::EXP].getGlobalBounds();
	
	Vector2f Str_textPos = { m_ButtonSprites[BUTTONS::RED_STR].getPosition().x-150, m_ButtonSprites[BUTTONS::RED_STR].getPosition().y-10 };
	Vector2f HP_textPos = { m_ButtonSprites[BUTTONS::RED_HP].getPosition().x-150, m_ButtonSprites[BUTTONS::RED_HP].getPosition().y-10 };
	Vector2f optionsTextPos = { scrollBounds.left + scrollBounds.width / 2.0f - optionsTextBounds.width / 2.0f, scrollBounds.top + 180.0f };
	Vector2f EXPTextPos = { scrollBounds.left + 120.0f, optionsTextPos.y + optionsTextBounds.height + 30.0f };
	

	m_UpgradeTexts[UPGRADE_TEXT::STRENGHT].setPosition(Str_textPos);
	m_UpgradeTexts[UPGRADE_TEXT::HP].setPosition(HP_textPos);
	m_UpgradeTexts[UPGRADE_TEXT::OPTIONS].setPosition(optionsTextPos);
	m_UpgradeTexts[UPGRADE_TEXT::EXP].setPosition(EXPTextPos);
}

void UpgradeMenu::scrollOpen()
{
	m_Scroll = std::make_unique<Sprite>();
	m_Scroll->setTexture(m_ScrollTextures[1]);
	m_Scroll->setScale(0.5, 0.5);

	sf::Vector2i pixelPos = { WINDOW_WIDTH / 2 - static_cast<int>(m_Scroll->getGlobalBounds().width/2),0 };
	sf::Vector2f worldPos = mapToCords(pixelPos);

	
	m_Scroll->setPosition(worldPos);
	Closed = false;
}

void UpgradeMenu::scrollCloed()
{
	m_Scroll = std::make_unique<Sprite>(); // ¿eby nie powielaæ 
	Closed = true;
	m_Scroll->setTexture(m_ScrollTextures[0]);
	m_Scroll->setScale(0.2, 0.2);
	sf::Vector2i pixelPos = { WINDOW_WIDTH - static_cast<int>(m_Scroll->getGlobalBounds().width+10),10 };
	sf::Vector2f worldPos = mapToCords(pixelPos);
	
	
	m_Scroll->setPosition(worldPos);
	
}

void UpgradeMenu::handleInnerInput()
{
	Player& _player = *m_GameManager.getPlayer();

	for (int i = 0; i < m_ButtonSprites.size(); i++) {
		FloatRect _buttonBounds = m_ButtonSprites[i].getGlobalBounds();
		if (collider(_buttonBounds)) {
			m_ButtonSprites[i].setColor(sf::Color(0, 0, 0, 130));
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (!m_isOnCoolDown && _player.m_Exp>0) {
					switch (i) {
						
					case GAME_ENUMS::UPGRADE_BUTTONS::HP_UP:

						_player.m_HP++;
						_player.m_Exp--;
						break;

					case GAME_ENUMS::UPGRADE_BUTTONS::STRENGHT_UP:
						_player.m_outputDamage++;
						_player.m_Exp--;
						break;

					
					}
					
					
				}
				if (i == GAME_ENUMS::UPGRADE_BUTTONS::BACK ) {

					m_isOpen = false;
				}
				m_isOnCoolDown = true;
				m_CoolDown = 15;
			}
		}
		else {
			m_ButtonSprites[i].setColor(sf::Color::White);
		}
	}
	if (m_CoolDown == 0) m_isOnCoolDown = false;
	else m_CoolDown--;
}

void UpgradeMenu::update()
{
	scrollBounds = m_Scroll->getGlobalBounds();
	string ExpUpdateStr = m_UpgradeStrings[UPGRADE_TEXT::EXP] + std::to_string(m_GameManager.getPlayer()->m_Exp);
	m_UpgradeTexts[UPGRADE_TEXT::EXP].setString(ExpUpdateStr);
	
}

bool UpgradeMenu::collider(FloatRect _bounds)
{
	sf::Vector2i _mousePos = sf::Mouse::getPosition();
	sf::Vector2f worldMousePos = mapToCords(_mousePos);
	if (_bounds.left <= worldMousePos.x
		&& _bounds.left + _bounds.width >= worldMousePos.x
		&& _bounds.top <= worldMousePos.y - 10
		&& _bounds.top + _bounds.height >= worldMousePos.y -30) {
		return true;
	}
	else return false;
}

Vector2f UpgradeMenu::mapToCords(Vector2i pixelPos)
{
	Vector2f worldPos = m_GameManager.getWindow()->mapPixelToCoords(pixelPos);
	return worldPos;
}

void UpgradeMenu::render()
{
	RenderWindow* _window = m_GameManager.getWindow();

	//cout << m_ButtonSprites[BUTTONS::RED_STR].getPosition().x<<endl;
	cout << m_isOpen << endl;
	if(m_Scroll!=nullptr) _window->draw(*m_Scroll);
	if (m_isOpen) {
		update();	
		scrollOpen();
		buttonsUpdate();
		viewUpdateTexts();
		handleInnerInput();
		
		for (auto& button : m_ButtonSprites) {
			_window->draw(button);
		}
		for (auto& text : m_UpgradeTexts) {
			_window->draw(text);
		}
		
	}
	else scrollCloed();
	handleInput();
	
}
