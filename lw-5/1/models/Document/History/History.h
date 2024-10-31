#pragma once

#include "../../Commands/ICommand.h"
#include <deque>

class History
{
public:
    History() = default;
    ~History() = default;

    [[nodiscard]] bool CanUndo() const;
    [[nodiscard]] bool CanRedo() const;

    void Undo();
    void Redo();

    void AddAndExecuteCommand(ICommandPtr && command);

private:

    std::deque<ICommandPtr> m_commands;
    size_t m_nextCommandIndex = 0;
};
