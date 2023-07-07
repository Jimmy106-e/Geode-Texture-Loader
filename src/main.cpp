
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class MyLayer : public CCLayer {
public:
    // Class member that stores how many times 
    // the button has been clicked
    size_t m_clicked = 0;

    bool init() {
        if (!CCLayer::init())
            return false;

        auto menu = CCMenu::create();

        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Click me!"),
            this,
            menu_selector(MyLayer::onClick)
        );

		auto exitbtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("exit"),
            this,
            menu_selector(MyLayer::onClickExit)
        );
		exitbtn->setPosition(0.f,50.f);
        menu->addChild(btn);
		menu->addChild(exitbtn);

        this->addChild(menu);

        return true;
    }

    void onClick(CCObject* sender) {
        // Increment click count
        m_clicked++;

        auto btn = static_cast<CCMenuItemSpriteExtra*>(sender);

        // getNormalImage returns the sprite of the button
        auto spr = static_cast<ButtonSprite*>(btn->getNormalImage());
        spr->setString(CCString::createWithFormat(
            "Clicked %d times", m_clicked
        )->getCString());
    }

	void onClickExit(CCObject* sender) {
        geode::createQuickPopup(
			"Exit",            // title
			"Do you want to exit",   // content
			"No", "Yes",      // buttons
			[](auto, bool btn2) {
				if (btn2) {
					//open MenuLayer
					//CCDirector::sharedDirector()->popToRootScene();
                    MenuLayer::scene(1);
				}
			}
		);
    }

	static MyLayer* create() {
    auto ret = new MyLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
	}

};

class $modify(MenuLayer) {

	void onMoreGames(CCObject*) {
		auto scene = CCScene::create();
		auto layer = MyLayer::create();
		scene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(.5f, scene));
		//FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show(); 
	} 
};