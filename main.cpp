#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorUI::init(editorLayer)) return false;

        auto sprite = ButtonSprite::create("AutoDec", "goldFont.fnt", "GJ_button_01.png", 0.6f);
        auto btn = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(MyEditorUI::onAutoDecorate)
        );

        if (auto menu = this->getChildByID("left-menu")) {
            menu->addChild(btn);
            menu->updateLayout();
        }

        return true;
    }

    void onAutoDecorate(CCObject* sender) {
        auto editorLayer = m_editorLayer;
        if (!editorLayer) return;

        auto objects = editorLayer->m_objects;
        if (!objects) return;

        std::vector<std::pair<int, CCPoint>> objectsToSpawn;

        CCObject* obj = nullptr;
        CCARRAY_FOREACH(objects, obj) {
            auto gameObject = static_cast<GameObject*>(obj);
            if (!gameObject) continue;

            if (gameObject->m_objectID == 1) {
                CCPoint spawnPos = gameObject->getPosition();
                spawnPos.y += 30.0f; 

                objectsToSpawn.push_back({8, spawnPos});
            }
        }

        for (const auto& [decorID, pos] : objectsToSpawn) {
            editorLayer->createObject(decorID, pos, true);
        }

        this->updateObjectCount();
        FLAlertLayer::create("Готово", "Авто-декорирование успешно завершено!", "OK")->show();
    }
};
