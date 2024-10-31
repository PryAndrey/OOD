#pragma once

#include <memory>

class ICommand
{
public:
	virtual void Execute() = 0;
	virtual void Unexecute() = 0;

	virtual std::string GetParamsForGlue() = 0;
	virtual bool IsGlueAble() const = 0;

	virtual ~ICommand() = default;
};

typedef std::unique_ptr<ICommand> ICommandPtr;
