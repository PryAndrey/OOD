#include "Menu.h"

void Menu::AddItem(const std::string& shortcut, const std::string& description, const Command& command)
{
	if (m_exit)
	{
		return;
	}

	auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
		return item.shortcut == shortcut;
	});
	if (it != m_items.end())
	{
		std::cout << "This name already used\n";
	}
	else
	{
		m_items.emplace_back(shortcut, description, command);
	}
}

void Menu::Run()
{
	if (m_exit)
	{
		return;
	}

	ShowInstructions();

	std::string command;

	while (getline(std::cin, command)
		&& command != "!")
	{
		try
		{
			if (!command.empty())
			{
				ExecuteCommand(command);
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

void Menu::Exit()
{
	m_exit = true;
}

void Menu::ShowInstructions() const
{
	if (m_exit)
	{
		return;
	}
	std::cout << "Commands list:\n";
	for (auto& item : m_items)
	{
		std::cout << "  " << item.shortcut << ": " << item.description << "\n";
	}
}

void Menu::ExecuteCommand(const std::string& command)
{
	std::istringstream iss(command);
	std::string name;
	iss >> name;

	auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
		return item.shortcut == name;
	});
	if (it != m_items.end())
	{
		it->command(iss);
	}
	else
	{
		std::cout << "Unknown command\n";
	}
}
