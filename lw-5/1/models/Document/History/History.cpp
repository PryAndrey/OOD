#include "History.h"
#include <sstream>

bool History::CanUndo() const
{
	return m_nextCommandIndex != 0;
}

bool History::CanRedo() const
{
	return m_nextCommandIndex != m_commands.size();
}

void History::Undo()
{
	if (CanUndo())
	{
		m_commands[m_nextCommandIndex - 1]->Unexecute();
		--m_nextCommandIndex;
	}
}

void History::Redo()
{
	if (CanRedo())
	{
		m_commands[m_nextCommandIndex]->Execute();
		++m_nextCommandIndex;
	}
}

void History::AddAndExecuteCommand(ICommandPtr&& command)
{
	auto GlueOperation = [&]() {
		if (m_nextCommandIndex == 0)
		{
			return;
		}
		std::string lastCommandParams = m_commands.at(m_nextCommandIndex - 1)->GetParamsForGlue();
		std::string commandParams = command->GetParamsForGlue();
		if (lastCommandParams != commandParams)
		{
			return;
		}
		Undo();
	};

	if (command->IsGlueAble())
	{
		GlueOperation();
	}
	if (m_nextCommandIndex < m_commands.size())
	{
		command->Execute();
		++m_nextCommandIndex;
		m_commands.resize(m_nextCommandIndex);
		m_commands.back() = std::move(command);
	}
	else
	{
		m_commands.emplace_back(nullptr);
		try
		{
			command->Execute();
			m_commands.back() = std::move(command);
			++m_nextCommandIndex;
		}
		catch (...)
		{
			m_commands.pop_back();
			throw;
		}
	}

	while (m_commands.size() > 10)
	{
		m_commands.pop_front();
		--m_nextCommandIndex;
	}
}
