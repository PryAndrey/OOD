#include "CCommand.h"

void CCommand::Execute()
{
    if (!m_executed)
    {
        DoExecute();
        m_executed = true;
    }
}

void CCommand::Unexecute()
{
    if (m_executed)
    {
        DoUnexecute();
        m_executed = false;
    }
}

//std::string CCommand::GetGluedAble() const
//{
//	return m_gluedAble ? "1" : "0";
//}
