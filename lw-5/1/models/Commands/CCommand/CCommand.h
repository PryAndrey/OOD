#pragma once

#include "../ICommand.h"

class CCommand : public ICommand
{
public:
	void Execute() final;
	void Unexecute() final;
	virtual std::string GetParamsForGlue() = 0;

protected:
	virtual void DoExecute() = 0;
	virtual void DoUnexecute() = 0;

	virtual bool IsGlueAble() const = 0;
private:
	bool m_executed = false;
};
