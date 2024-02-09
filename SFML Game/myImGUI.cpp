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

void myImGUI::update(sf::Clock& deltaClock, EntityManager & m_entities)
{
    ImGui::SFML::Update(*m_window, deltaClock.restart());
    ImGui::Begin("Debug Tool");

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
    {
        // Systems table
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

        const char* types[] = {"enemy", "smallenemy", "bullet", "player"};
        // Entity Manager table
        if (ImGui::BeginTabItem("Entity Manager"))
        {
            // group by tag node
            if (ImGui::TreeNode("Entities by tag"))
            {
                // for each entity type...
                for (const char* type : types)
                {
                    if (ImGui::CollapsingHeader(type, ImGuiTreeNodeFlags_None))
                    {
                        if (ImGui::BeginTable("asdf", 4))
                        {
                            for (auto& e : m_entities.getEntities(type))
                            {
                                ImGui::TableNextColumn();
                                ImGui::Text("ID: %zu", e->getID());
                                ImGui::TableNextColumn();
                                ImGui::Text("pos: (%.2f , %.2f)", e->cTransform->pos.x, e->cTransform->pos.y);
                                ImGui::TableNextColumn();
                                ImGui::Text("velocity: (%.2f , %.2f)", e->cTransform->velocity.x, e->cTransform->velocity.y);
                                ImGui::TableNextRow();
                            }
                        }
                        ImGui::EndTable();
                    }
                }

                ImGui::TreePop();
            }

            // all node
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