#pragma once

#include <utility>

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	explicit CBeverage(std::string description)
		: m_description(std::move(description))
	{
	}

	[[nodiscard]] std::string GetDescription() const override final
	{
		return m_description;
	}

private:
	std::string m_description;
};

enum class PortionMultiplier
{
	Standard,
	Double,
	Triple
};

// Кофе
class CCoffee : public CBeverage
{
public:
	explicit CCoffee(const std::string& description = "Coffee")
		: CBeverage(description)
	{
	}

	[[nodiscard]] double GetCost() const override
	{
		return 60;
	}
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	explicit CCappuccino(PortionMultiplier portionMult = PortionMultiplier::Standard)
		: CCoffee(portionMult == PortionMultiplier::Double ? "Double Cappuccino"
														   : "Standard Cappuccino")
		, m_portionMultiplier(portionMult)
	{
	}

	[[nodiscard]] double GetCost() const override
	{
		double cost = m_portionMultiplier == PortionMultiplier::Double ? 120 : 80;
		return cost;
	}

private:
	PortionMultiplier m_portionMultiplier;
};
// Диаграмма
// Латте
class CLatte : public CCoffee
{
public:
	explicit CLatte(PortionMultiplier portionMult = PortionMultiplier::Standard)
		: CCoffee(portionMult == PortionMultiplier::Double ? "Double Latte" : "Standard Latte")
		, m_portionMultiplier(portionMult)
	{
	}

	[[nodiscard]] double GetCost() const override
	{
		double cost = m_portionMultiplier == PortionMultiplier::Double ? 130 : 90;
		return cost;
	}

private:
	PortionMultiplier m_portionMultiplier;
};

enum class TeaType
{
	Black,
	Green,
	Rainbow,
	Yellow
};

std::string ToStringTeaType(TeaType teaType)
{
	switch (teaType)
	{
	case TeaType::Green:
		return "Green";
	case TeaType::Rainbow:
		return "Rainbow";
	case TeaType::Yellow:
		return "Yellow";
	case TeaType::Black:
	default:
		return "Black";
	}
}

// Чай
class CTea : public CBeverage
{
public:
	explicit CTea(TeaType teaType = TeaType::Black)
		: CBeverage(ToStringTeaType(teaType) + " Tea")
		, m_teaType(teaType)
	{
	}

	[[nodiscard]] double GetCost() const override
	{
		return 30;
	}

private:
	TeaType m_teaType;
};

enum class PortionSize
{
	Small,
	Medium,
	Large
};

std::string ToStringPortionSize(PortionSize size)
{
	switch (size)
	{
	case PortionSize::Small:
		return "Small";
	case PortionSize::Large:
		return "Large";
	case PortionSize::Medium:
	default:
		return "Medium";
	}
}

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	explicit CMilkshake(PortionSize portionSize = PortionSize::Medium)
		: CBeverage(ToStringPortionSize(portionSize) + " Milkshake")
		, m_portionSize(portionSize)
	{
	}

	[[nodiscard]] double GetCost() const override
	{
		switch (m_portionSize)
		{
		case PortionSize::Small:
			return 50;
		case PortionSize::Medium:
			return 60;
		case PortionSize::Large:
			return 80;
		}
	}

private:
	PortionSize m_portionSize;
};