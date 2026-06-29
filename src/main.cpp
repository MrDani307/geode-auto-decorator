#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

// === Popup с анализом блоков ===
class AnalyzePopup : public FLAlertLayer {
public:
    static AnalyzePopup* create(std::string text) {
        auto ret = FLAlertLayer::create(
            "Анализ блоков",
            text.c_str(),
            "Закрыть"
        );
        return ret;
    }
};

// === Хук на EditorUI — добавляем плавающую кнопку ===
class $modify(MyEditorUI, EditorUI) {
    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel)) return false;

        auto btn = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSpriteFrameName(
                "edit_ePlusBtn_001.png",
                1.f,
                CircleBaseColor::Green,
                CircleBaseSize::Small
            ),
            this,
            menu_selector(MyEditorUI::onAnalyzeBtn)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);
        menu->setPosition(35.f, 35.f);
        // Высокий z-order чтобы быть поверх всего
        this->addChild(menu, 999);

        return true;
    }

    void onAnalyzeBtn(CCObject*) {
        auto editorLayer = LevelEditorLayer::get();
        if (!editorLayer) {
            FLAlertLayer::create("Ошибка", "Редактор не найден.", "Ок")->show();
            return;
        }

        auto selectedObjs = this->getSelectedObjects();
        if (!selectedObjs || selectedObjs->count() == 0) {
            FLAlertLayer::create(
                "Анализ блоков",
                "Нет выделенных блоков.\nВыдели блоки и нажми снова.",
                "Закрыть"
            )->show();
            return;
        }

        // Считаем типы блоков
        int solidCount = 0;
        int spikeCount = 0;
        int decorCount = 0;
        int otherCount = 0;

        for (int i = 0; i < selectedObjs->count(); i++) {
            auto obj = static_cast<GameObject*>(selectedObjs->objectAtIndex(i));
            int id = obj->m_objectID;

            // Простая классификация по ID
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

        std::string result = "Найдено объектов: " + 
            std::to_string(selectedObjs->count()) + "\n\n" +
            "Платформы: " + std::to_string(solidCount) + "\n" +
            "Шипы: " + std::to_string(spikeCount) + "\n" +
            "Декорации: " + std::to_string(decorCount) + "\n" +
            "Другое: " + std::to_string(otherCount);

        FLAlertLayer::create(
            "Анализ блоков",
            result.c_str(),
            "Закрыть"
        )->show();
    }
};