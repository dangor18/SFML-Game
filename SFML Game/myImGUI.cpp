#include "myImGUI.h"

// default constructor
myImGUI::myImGUI() {}

// Constructor using std::shared_ptr
void myImGUI::init(sf::RenderWindow* window, int spawnInterval)
{
    m_window = window;
    ImGui::SFML::Init(*m_window);
}

void myImGUI::update(sf::Clock& deltaClock)
{
    ImGui::SFML::Update(*m_window, deltaClock.restart());
    ImGui::Begin("Debug Tool");
    

    ImGui::End();
}

void myImGUI::processEvent(sf::Event & event) 
{
    ImGui::SFML::ProcessEvent(*m_window, event);
}

void myImGUI::render()
{
    ImGui::SFML::Render(*m_window);
}