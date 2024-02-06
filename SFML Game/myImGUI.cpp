#include "myImGUI.h"

myImGUI::myImGUI()
{}

void myImGUI::init(sf::RenderWindow& window, int spawnInterval)
{
	m_window = std::make_shared<sf::RenderWindow>(window);
	m_spawnInterval = spawnInterval;
}

void myImGUI::update(sf::Clock & deltaClock)
{
	// update imgui for this freame with the time that the last frame took
	ImGui::SFML::Update(*m_window.get(), deltaClock.restart());
	ImGui::Begin("Debug Panel");
	ImGui::End();
}

void myImGUI::processEvent(sf::Event event)
{

}
void myImGUI::render()
{

}