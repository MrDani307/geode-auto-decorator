#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuHook, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto btn = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSpriteFrameName(
                "edit_ePlusBtn_001.png",
                1.f,
                CircleBaseColor::Green,
                CircleBaseSize::Small
            ),
            this,
            menu_selector(MyMenuHook::onFloatBtn)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);
        menu->setPosition(35.f, 35.f);
        this->addChild(menu, 10);

        return true;
    }

    void onFloatBtn(CCObject*) {
        FLAlertLayer::create(
            "Моё меню",
            "Здесь пока пусто.",
            "Закрыть"
        )->show();
    }
};