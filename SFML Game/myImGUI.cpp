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
            ImGui::SliderInt("Spawn Rate", &m_spawnInterval, 5, 200);
            ImGui::Unindent();
            ImGui::Checkbox("Special Weapon", &isSpecialActive);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Entity Manager"))
        {
            if (ImGui::TreeNode("Entities by tag"))
            {
                if (ImGui::CollapsingHeader("Bullet Entity", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("IsItemHovered: %d", ImGui::IsItemHovered());
                    for (int i = 0; i < 5; i++)
                        ImGui::Text("Some content %d", i);
                }

                if (ImGui::CollapsingHeader("Enemy Entity", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("IsItemHovered: %d", ImGui::IsItemHovered());
                    for (int i = 0; i < 5; i++)
                        ImGui::Text("Some content %d", i);
                }

                if (ImGui::CollapsingHeader("Smallenemy Entity", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("IsItemHovered: %d", ImGui::IsItemHovered());
                    for (int i = 0; i < 5; i++)
                        ImGui::Text("Some content %d", i);
                }

                if (ImGui::CollapsingHeader("Player Entity", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("IsItemHovered: %d", ImGui::IsItemHovered());
                    for (int i = 0; i < 5; i++)
                        ImGui::Text("Some content %d", i);
                }

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("All Entities"))
            {
                if (ImGui::CollapsingHeader("Header", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("IsItemHovered: %d", ImGui::IsItemHovered());
                    for (int i = 0; i < 5; i++)
                        ImGui::Text("Some content %d", i);
                }
                

                ImGui::TreePop();
            }
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