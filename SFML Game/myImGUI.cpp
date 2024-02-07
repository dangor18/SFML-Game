#include "myImGUI.h"

// default constructor
myImGUI::myImGUI() {}

// Constructor using std::shared_ptr
void myImGUI::init(sf::RenderWindow* window, int spawnInterval)
{
    m_window = window;
    ImGui::SFML::Init(*m_window);
    ImGui::GetStyle().ScaleAllSizes(1.0f);
}

void myImGUI::update(sf::Clock& deltaClock)
{
    ImGui::SFML::Update(*m_window, deltaClock.restart());
    ImGui::Begin("Debug Tool");

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("Systems"))
        {
            ImGui::Checkbox("Movement", &isMovementActive);
            ImGui::Checkbox("LifeSpan", &isLifeSpanActive);
            ImGui::Checkbox("Collision", &isCollisionActive);
            ImGui::Checkbox("Spawning", &isSpawnerActive);
            ImGui::Indent();
            ImGui::SliderInt("Spawn Rate", &m_spawnInterval, 10, 240);
            //spawnFlag = ImGui::Button("Spawn", ImVec2(120, 30));
            ImGui::Unindent();
            ImGui::Checkbox("Special Weapon", &isSpecialShootActive);

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Broccoli"))
        {
            ImGui::Text("This is the Broccoli tab!\nblah blah blah blah blah");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Cucumber"))
        {
            ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

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