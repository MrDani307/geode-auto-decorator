#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/Popup.hpp>

using namespace geode::prelude;

// === Popup меню ===
class MyPopup : public Popup<> {
protected:
    bool setup() override {
        this->setTitle("Моё меню");
        return true;
    }
public:
    static MyPopup* create() {
        auto ret = new MyPopup();
        if (ret->initAnchored(280.f, 180.f)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

// === Хук на MenuLayer ===
class $modify(MyMenuLayer, MenuLayer) {
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
            menu_selector(MyMenuLayer::onFloatBtn)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);
        menu->setPosition(35.f, 35.f);
        this->addChild(menu, 10);

        return true;
    }

    void onFloatBtn(CCObject*) {
        MyPopup::create()->show();
    }
};