#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

// Классификация объекта по ID
std::string classifyObject(int id) {
    // Solid blocks (основные платформы)
    if (id == 1 || id == 2 || id == 3 || id == 4 ||
        id == 6 || id == 7 || id == 21 || id == 22 ||
        id == 23 || id == 24 || id == 25 ||
        (id >= 211 && id <= 214)) return "solid";

    // Spikes
    if (id == 8 || id == 39 || id == 103 ||
        id == 242 || id == 243 || id == 291) return "spike";

    // Hazards / gameplay
    if (id == 9 || id == 10 || id == 11 || id == 12 ||
        id == 13 || id == 35 || id == 36 ||
        id == 67 || id == 99 || id == 101) return "gameplay";

    // Decor (широкий диапазон)
    if ((id >= 40 && id <= 50) ||
        (id >= 114 && id <= 140) ||
        (id >= 186 && id <= 210) ||
        (id >= 497 && id <= 744) ||
        (id >= 1000 && id <= 1300)) return "decor";

    return "other";
}

class $modify(MyEditorUI, EditorUI) {
    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel)) return false;

        // Главное меню мода
        auto modMenu = CCMenu::create();
        modMenu->setPosition(35.f, 80.f);
        modMenu->setLayout(
            ColumnLayout::create()
                ->setGap(5.f)
                ->setAxisReverse(true)
        );

        // Кнопка анализа
        auto analyzeBtn = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSpriteFrameName(
                "GJ_plainBtn_001.png",
                1.f,
                CircleBaseColor::Blue,
                CircleBaseSize::Small
            ),
            this,
            menu_selector(MyEditorUI::onAnalyzeBtn)
        );

        // Кнопка декора
        auto decorBtn = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSpriteFrameName(
                "GJ_plainBtn_001.png",
                1.f,
                CircleBaseColor::Green,
                CircleBaseSize::Small
            ),
            this,
            menu_selector(MyEditorUI::onDecorBtn)
        );

        // Лейблы на кнопках
        auto analyzeLabel = CCLabelBMFont::create("A", "bigFont.fnt");
        analyzeLabel->setScale(0.5f);
        analyzeBtn->addChild(analyzeLabel);
        analyzeLabel->setPosition(analyzeBtn->getContentSize() / 2);

        auto decorLabel = CCLabelBMFont::create("D", "bigFont.fnt");
        decorLabel->setScale(0.5f);
        decorBtn->addChild(decorLabel);
        decorLabel->setPosition(decorBtn->getContentSize() / 2);

        modMenu->addChild(analyzeBtn);
        modMenu->addChild(decorBtn);
        modMenu->updateLayout();

        this->addChild(modMenu, 999);

        return true;
    }

    void onAnalyzeBtn(CCObject*) {
        auto selectedObjs = this->getSelectedObjects();
        if (!selectedObjs || selectedObjs->count() == 0) {
            FLAlertLayer::create(
                "Auto Decorator",
                "No objects selected.",
                "OK"
            )->show();
            return;
        }

        int solidCount = 0, spikeCount = 0;
        int decorCount = 0, gameplayCount = 0, otherCount = 0;

        for (int i = 0; i < (int)selectedObjs->count(); i++) {
            auto obj = static_cast<GameObject*>(selectedObjs->objectAtIndex(i));
            std::string type = classifyObject(obj->m_objectID);
            if (type == "solid") solidCount++;
            else if (type == "spike") spikeCount++;
            else if (type == "decor") decorCount++;
            else if (type == "gameplay") gameplayCount++;
            else otherCount++;
        }

        std::string result =
            "Total: " + std::to_string(selectedObjs->count()) +
            "\nSolid: " + std::to_string(solidCount) +
            "\nSpikes: " + std::to_string(spikeCount) +
            "\nGameplay: " + std::to_string(gameplayCount) +
            "\nDecor: " + std::to_string(decorCount) +
            "\nOther: " + std::to_string(otherCount);

        FLAlertLayer::create("Auto Decorator", result.c_str(), "OK")->show();
    }

    void onDecorBtn(CCObject*) {
        auto selectedObjs = this->getSelectedObjects();
        if (!selectedObjs || selectedObjs->count() == 0) {
            FLAlertLayer::create(
                "Auto Decorator",
                "Select solid blocks first,\nthen press Decor.",
                "OK"
            )->show();
            return;
        }

        auto editorLayer = LevelEditorLayer::get();
        if (!editorLayer) return;

        int placed = 0;

        for (int i = 0; i < (int)selectedObjs->count(); i++) {
            auto obj = static_cast<GameObject*>(selectedObjs->objectAtIndex(i));
            if (classifyObject(obj->m_objectID) != "solid") continue;

            // Ставим декор над каждым solid блоком
            // ID 114 = простой декор-блок (bush/rock style)
            CCPoint pos = obj->getPosition();
            pos.y += 30.f;

            auto decorObj = editorLayer->createObject(114, pos, false);
            if (decorObj) placed++;
        }

        FLAlertLayer::create(
            "Auto Decorator",
            ("Placed " + std::to_string(placed) + " decor objects!").c_str(),
            "OK"
        )->show();
    }
};