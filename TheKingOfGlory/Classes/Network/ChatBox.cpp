#include "ChatBox.h"
#include "cocos-ext.h"
#include "Model/User.h"
USING_NS_CC;
using namespace extension;

ChatBox* ChatBox::create(const std::string& filename, Client* client)
{
	auto box = new (std::nothrow) ChatBox();
	if (box&&box->initWithFile(filename)&&box->init(client))
	{
		box->autorelease();
		return box;
	}
	CC_SAFE_DELETE(box);
	return nullptr;
}

bool ChatBox::init(Client* client)
{
	_client = client;
	Size boxSize = this->getContentSize();

	//创建文本输入框
	auto inputBG = Sprite::create("Pictures/UI/textInput.png");
	inputBG->setOpacity(200);

	textInput = ui::TextField::create("Input message", "fonts/arial.ttf",15 );
	textInput->setColor(Color3B::WHITE);
	textInput->setMaxLength(16);
	textInput->setMaxLengthEnabled(true);
	textInput->setCursorChar('|');
	textInput->setCursorEnabled(true);
	textInput->setPosition(inputBG->getContentSize() / 2); 
	textInput->setTouchSize(inputBG->getContentSize());
	textInput->setTouchAreaEnabled(true);

	inputBG->addChild(textInput);
	auto inputSize = inputBG->getContentSize();

	inputBG->setPosition(boxSize.width*0.4,boxSize.height*0.1);

	this->addChild(inputBG);
	
	auto sendButton = ui::Button::create("Pictures/UI/sendButton_normal.png", "Pictures/UI/sendButton_selected.png");
	sendButton->setTitleText("Send");
	sendButton->setTitleFontSize(18);
	sendButton->setPosition(Vec2(boxSize.width*0.855,boxSize.height*0.1));
	sendButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		auto text = textInput->getString();
		if (text.size())
		{
			textInput->setString(std::string());
			flatbuffers::FlatBufferBuilder builder(1024);
			using namespace GameMsg;
			auto name = builder.CreateString(User::getInstance()->getName());
			auto chat = builder.CreateString(text);
			auto chatMsg = CreateChatMsg(builder, name, chat);
			auto msg = CreateMsg(builder, MsgType::MsgType_MsgType_ChatMsg, Date::Date_chatMsg, chatMsg.Union());
			builder.Finish(msg);
			uint8_t* buff = builder.GetBufferPointer();
			size_t size = builder.GetSize();
			socket_message message((const char*)buff, size);
			_client->sendMessage(message);
			
		}

	});
	this->addChild(sendButton);

	auto upButton = ui::Button::create("Pictures/UI/previous_button.png");
	upButton->setPosition(Vec2(boxSize.width*0.2, boxSize.height*0.9));
	upButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		this->up();
		updateLayout();
	});
	this->addChild(upButton);

	auto downButton = ui::Button::create("Pictures/UI/next_button.png");
	downButton->setPosition(Vec2(boxSize.width*0.4, boxSize.height*0.9));
	downButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		this->down();
		updateLayout();
	});
	this->addChild(downButton);

	auto pgUpButton = ui::Button::create("Pictures/UI/pgUp_button.png");
	pgUpButton->setPosition(Vec2(boxSize.width*0.6, boxSize.height*0.9));
	pgUpButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		this->pgUp();
		updateLayout();
	});
	this->addChild(pgUpButton);

	auto pgDownButton = ui::Button::create("Pictures/UI/pgDown_button.png");
	pgDownButton->setPosition(Vec2(boxSize.width*0.8, boxSize.height*0.9));
	pgDownButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		this->pgdown();
		updateLayout();
	});
	this->addChild(pgDownButton);

	_buttonList.pushBack(sendButton);
	_buttonList.pushBack(upButton);
	_buttonList.pushBack(downButton);
	_buttonList.pushBack(pgUpButton);
	_buttonList.pushBack(pgDownButton);

	_isOpen = false;
	close();

	return true;
}

void ChatBox::updateLayout()
{
	for (auto text : _chatTextList)
	{
		if (text->getParent())
			this->removeChild(text,false);
	}
	Size boxSize = this->getContentSize();
	int textNum = _chatTextList.size()-1-_index;
	for (int i = textNum; i>=0&&i> textNum - maxNum; --i)
	{
		auto text = _chatTextList.at(i);
		float x;
		if (text->isLocal())
			x = boxSize.width*0.92 - text->getContentSize().width*text->getScaleX() / 2;
		else
			x = boxSize.width*0.08 + text->getContentSize().width*text->getScaleX() / 2;
		text->setPosition(x,boxSize.height*(0.2+(textNum-i)*0.04));
		this->addChild(text);
	}
}

void ChatBox::open()
{
	for (auto button : _buttonList)
		button->setEnabled(true);
	this->setVisible(true);
	_index = 0;
	updateLayout();
}

void ChatBox::close()
{
	for (auto button : _buttonList)
		button->setEnabled(false);
	this->setVisible(false);
}

ChatText * ChatText::create(const std::string & filename, const std::string& text, bool isLocal)
{
	auto chatText = new (std::nothrow) ChatText();
	if (chatText&&chatText->initWithFile(filename) && chatText->init(text,isLocal))
	{
		chatText->autorelease();
		return chatText;
	}
	CC_SAFE_DELETE(chatText);
	return nullptr;
}

bool ChatText::init(const std::string& text, bool isLocal)
{
	_isLocal = isLocal;

	Size textSize = this->getContentSize();

	_text = ui::Text::create(text, "fonts/Quicksand-Bold.ttf", 15);
	_text->setPosition(Vec2(textSize.width / 2, textSize.height/2));
	_text->setColor(Color3B::BLACK);
	float scale = (_text->getContentSize().width+10)/ textSize.width;
	this->setScaleX(scale);
	_text->setScaleX(1.0 / scale);
	this->addChild(_text);

	return true;
}
