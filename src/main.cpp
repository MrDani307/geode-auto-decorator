#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel)) return false;

        auto btn = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSpriteFrameName(
                "GJ_plainBtn_001.png",
                1.f,
                CircleBaseColor::Blue,
                CircleBaseSize::Small
            ),
            this,
            menu_selector(MyEditorUI::onAnalyzeBtn)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);
        menu->setPosition(35.f, 35.f);
        this->addChild(menu, 999);

        return true;
    }

    void onAnalyzeBtn(CCObject*) {
        auto selectedObjs = this->getSelectedObjects();
        if (!selectedObjs || selectedObjs->count() == 0) {
            FLAlertLayer::create(
                "Auto Decorator",
                "No objects selected.\nSelect objects and try again.",
                "OK"
            )->show();
            return;
        }

        int solidCount = 0;
        int spikeCount = 0;
        int decorCount = 0;
        int otherCount = 0;

        for (int i = 0; i < (int)selectedObjs->count(); i++) {
            auto obj = static_cast<GameObject*>(selectedObjs->objectAtIndex(i));
            int id = obj->m_objectID;

            if (id == 1 || id == 2 || id == 3 || id == 4) {
                solidCount++;
            } else if (id == 8 || id == 39 || id == 103) {
                spikeCount++;
            } else if (id >= 497 && id <= 999) {
                decorCount++;
            } else {
                otherCount++;
            }
        }

        std::string result =
            "Objects: " + std::to_string(selectedObjs->count()) +
            "\nSolid: " + std::to_string(solidCount) +
            "\nSpikes: " + std::to_string(spikeCount) +
            "\nDecor: " + std::to_string(decorCount) +
            "\nOther: " + std::to_string(otherCount);

        FLAlertLayer::create(
            "Auto Decorator",
            result.c_str(),
            "OK"
        )->show();
    }
};