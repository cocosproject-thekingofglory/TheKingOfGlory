#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Network/Client.h"


class ChatText :public cocos2d::Sprite
{
private:
	cocos2d::ui::Text* _text;
	bool _isLocal;
public:
	static ChatText* create(const std::string& filename, const std::string& text, bool isLocal);
	bool init(const std::string& text, bool isLocal);
	bool isLocal() { return _isLocal; }
};

class ChatBox :public cocos2d::Sprite
{
private:
	Client* _client;
	int _index;
	bool _isOpen;
	const int maxNum = 17;
	cocos2d::ui::TextField* textInput;
	cocos2d::Vector<ChatText*>_chatTextList;
	cocos2d::Vector<cocos2d::ui::Button*> _buttonList;
public:
	static ChatBox* create(const std::string& filename, Client* client);
	bool init(Client* client);
	void addChatText(ChatText* text) { _chatTextList.pushBack(text); }
	void setIndex(int index) { _index = index; }
	void updateLayout();
	void open();
	void close();
	void update() { if (_isOpen)close(); else open(); _isOpen = !_isOpen; }
	void up() { if (_index < _chatTextList.size() - 1)	++_index; }
	void down() { if (_index > 0)	--_index; }
	void pgUp() { if (_index < _chatTextList.size() - maxNum)	_index += maxNum; }
	void pgdown() { _index -= maxNum; if (_index < 0) _index = 0; }

};
