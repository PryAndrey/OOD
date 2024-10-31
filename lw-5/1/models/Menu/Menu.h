#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <utility>

class IMenu
{
public:
	typedef std::function<void(std::istream& iss)> Command;
	virtual void AddItem(const std::string& shortcut, const std::string& description, const Command& command) = 0;
	virtual void Run() = 0;
	virtual void ShowInstructions() const = 0;
	virtual void Exit() = 0;

private:
	virtual void ExecuteCommand(const std::string& command) = 0;

protected:
	struct Item
	{
		Item(std::string shortcut, std::string description, Command command)
			: shortcut(std::move(shortcut))
			, description(std::move(description))
			, command(std::move(command))
		{
		}

		std::string shortcut;
		std::string description;
		Command command;
	};
};

class Menu : public IMenu
{
public:
	void AddItem(const std::string& shortcut, const std::string& description, const Command& command) override;
	void Run() override;
	void ShowInstructions() const override;
	void Exit() override;

private:
	void ExecuteCommand(const std::string& command) override;

	std::vector<Item> m_items;
	bool m_exit = false;
};