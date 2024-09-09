#pragma once

#include "CDucks.h"
#include "models/delegated_classes/CFlyNoWay.cpp"
#include "models/delegated_classes/CFlyWithWings.cpp"
#include "models/delegated_classes/CMuteQuack.cpp"
#include "models/delegated_classes/CQuack.cpp"
#include "models/delegated_classes/CSqueak.cpp"
#include "models/delegated_classes/CNoDance.cpp"
#include "models/delegated_classes/CWaltzDance.cpp"
#include "models/delegated_classes/CMinuetDance.cpp"

using namespace std;

/// CMallardDuck
void CMallardDuck::Display()
{
	cout << "MallardDuck" << endl;
}

CMallardDuck::CMallardDuck()
{
	m_quackBehavior = std::make_unique<CQuack>();
	m_flyBehavior = std::make_unique<CFlyWithWings>();
	m_danceBehavior = std::make_unique<CWaltzDance>();
}

/// CRubberDuck
void CRubberDuck::Display()
{
	cout << "RubberDuck" << endl;
}

CRubberDuck::CRubberDuck()
{
	m_quackBehavior = std::make_unique<CSqueak>();
	m_flyBehavior = std::make_unique<CFlyNoWay>();
	m_danceBehavior = std::make_unique<CNoDance>();
}

/// CDecoyDuck
void CDecoyDuck::Display()
{
	cout << "DecoyDuck" << endl;
}

CDecoyDuck::CDecoyDuck()
{
	m_quackBehavior = std::make_unique<CMuteQuack>();
	m_flyBehavior = std::make_unique<CFlyNoWay>();
	m_danceBehavior = std::make_unique<CNoDance>();
}

/// CRedheadDuck
void CRedheadDuck::Display()
{
	cout << "RedheadDuck" << endl;
}

CRedheadDuck::CRedheadDuck()
{
	m_quackBehavior = std::make_unique<CQuack>();
	m_flyBehavior = std::make_unique<CFlyWithWings>();
	m_danceBehavior = std::make_unique<CMinuetDance>();
}
