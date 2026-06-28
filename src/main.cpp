#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <cocos2d.h>

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorUI::init(editorLayer)) return false;

        auto menu = this->getChildByID("edit-menu");
        if (!menu) {
            menu = this->getChildByID("delete-menu");
        }
        if (!menu) {
            menu = m_buildModeMenu;
        }

        if (menu) {
            auto sprite = CCPositionBonusSprite::createWithSpriteFrameName("GJ_plusBtn_001.png", 0.8f);
            auto button = CCMenuItemSpriteExtra::create(
                sprite,
                this,
                menu_selector(MyEditorUI::onAutoDecorate)
            );
            button->setID("auto-decorate-button");
            menu->addChild(button);
            menu->updateLayout();
        }

        return true;
    }

    void onAutoDecorate(CCObject* sender) {
        auto editorLayer = m_editorLayer;
        if (!editorLayer) return;

        auto selectedObjects = this->getSelectedObjects();
        if (!selectedObjects || selectedObjects->count() == 0) {
            FLAlertLayer::create("AutoDecorator", "Выделите хотя бы один объект!", "OK")->show();
            return;
        }

        std::vector<GameObject*> objectsToDecorate;
        CCObject* obj;
        CCARRAY_FOREACH(selectedObjects, obj) {
            auto gameObj = static_cast<GameObject*>(obj);
            if (gameObj) {
                objectsToDecorate.push_back(gameObj);
            }
        }

        for (auto* baseObj : objectsToDecorate) {
            CCPoint basePos = baseObj->getPosition();
            int decorationID = 44; 
            
            auto decorObj = editorLayer->createObject(decorationID, basePos + CCPoint{0, 30.0f}, true);
            if (decorObj) {
                decorObj->m_editorLayer = editorLayer;
                editorLayer->m_objects->addObject(decorObj);
                decorObj->determineCheckColor();
                decorObj->setObjectColor(decorObj->m_baseColor);
            }
        }

        FLAlertLayer::create("AutoDecorator", "Декорирование успешно завершено!", "OK")->show();
    }
};
