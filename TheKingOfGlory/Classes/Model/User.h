#pragma once
#include <string>

class User
{
public:
    User(User const &) = delete;
    void operator=(User const &) = delete;
    
    static User* getInstance()
    {
        static User INSTANCE;
        return &INSTANCE;
    }

	void setRole(int role) { this->role = role; }
	int getRole() { return role; }

    void setName(const std::string& name) { this->name = name; };
    std::string getName() const { return name; };

	void setColor(int color) { this->color = color; }
	int getColor() { return color; }

private:
    User() {};

	int role;
	int color;
    std::string name;
};

