#pragma once

#include "IBeverage.h"

// Базовый декоратор "Добавка к напитку". Также является напитком
class CCondimentDecorator : public IBeverage
{
public:
	[[nodiscard]] std::string GetDescription() const override
	{
		// Описание декорированного напитка добавляется к описанию оборачиваемого
		// напитка
		return m_beverage->GetDescription() + ", " + GetCondimentDescription();
	}

	[[nodiscard]] double GetCost() const override
	{
		// Стоимость складывается из стоимости добавки и стоимости декорируемого
		// напитка
		return m_beverage->GetCost() + GetCondimentCost();
	}

	// Стоимость и описание добавки вычисляется в классах конкретных декораторов
	[[nodiscard]] virtual std::string GetCondimentDescription() const = 0;
	[[nodiscard]] virtual double GetCondimentCost() const = 0;

protected:
	explicit CCondimentDecorator(IBeveragePtr&& beverage)
		: m_beverage(std::move(beverage))
	{
	}

private:
	IBeveragePtr m_beverage;
};

// Добавка из корицы
class CCinnamon : public CCondimentDecorator
{
public:
	explicit CCinnamon(IBeveragePtr&& beverage)
		: CCondimentDecorator(std::move(beverage))
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override { return 20; }

	[[nodiscard]] std::string GetCondimentDescription() const override { return "Cinnamon"; }
};

// Лимонная добавка
class CLemon : public CCondimentDecorator
{
public:
	explicit CLemon(IBeveragePtr&& beverage, unsigned quantity = 1)
		: CCondimentDecorator(std::move(beverage))
		, m_quantity(quantity)
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override { return 10.0 * m_quantity; }
	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Lemon x " + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
};

enum class IceCubeType
{
	Dry, // Сухой лед (для суровых сибирских мужиков)
	Water // Обычные кубики из воды
};

// Добавка "Кубики льда". Определяется типом и количеством кубиков, что влияет
// на стоимость и описание
class CIceCubes : public CCondimentDecorator
{
public:
	CIceCubes(IBeveragePtr&& beverage, unsigned quantity,
		IceCubeType type = IceCubeType::Water)
		: CCondimentDecorator(std::move(beverage))
		, m_quantity(quantity)
		, m_type(type)
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		// Чем больше кубиков, тем больше стоимость.
		// Сухой лед стоит дороже
		return (m_type == IceCubeType::Dry ? 10 : 5) * m_quantity;
	}
	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return std::string(m_type == IceCubeType::Dry ? "Dry" : "Water") + " ice cubes x " + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
	IceCubeType m_type;
};

// Тип сиропа
enum class SyrupType
{
	Chocolate, // Шоколадный
	Maple, // Кленовый
};

// Добавка "Сироп"
class CSyrup : public CCondimentDecorator
{
public:
	CSyrup(IBeveragePtr&& beverage, SyrupType syrupType)
		: CCondimentDecorator(std::move(beverage))
		, m_syrupType(syrupType)
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override { return 15; }
	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return std::string(m_syrupType == SyrupType::Chocolate ? "Chocolate"
															   : "Maple")
			+ " syrup";
	}

private:
	SyrupType m_syrupType;
};

// Шоколадная крошка
class CChocolateCrumbs : public CCondimentDecorator
{
public:
	CChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass)
		: CCondimentDecorator(std::move(beverage))
		, m_mass(mass)
	{
	}

	[[nodiscard]] double GetCondimentCost() const override { return 2.0 * m_mass; }

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Chocolate crumbs " + std::to_string(m_mass) + "g";
	}

private:
	unsigned m_mass;
};

// Кокосовая стружка
class CCoconutFlakes : public CCondimentDecorator
{
public:
	CCoconutFlakes(IBeveragePtr&& beverage, unsigned mass)
		: CCondimentDecorator(std::move(beverage))
		, m_mass(mass)
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override { return 1.0 * m_mass; }
	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Coconut flakes " + std::to_string(m_mass) + "g";
	}

private:
		unsigned m_mass;
};

// Шоколадная долька
class CChocolateSlice : public CCondimentDecorator
{
public:
	explicit CChocolateSlice(IBeveragePtr&& beverage, unsigned quantity = 1)
		: CCondimentDecorator(std::move(beverage))
		, m_quantity(quantity > 5 ? 5 : quantity)
	{
	}

	[[nodiscard]] double GetCondimentCost() const override { return 10.0 * m_quantity; }

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Chocolate slice x" + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
};

// Добавка Сливок
class CCream : public CCondimentDecorator
{
public:
	explicit CCream(IBeveragePtr&& beverage)
		: CCondimentDecorator(std::move(beverage))
	{
	}

protected:
	[[nodiscard]] double GetCondimentCost() const override { return 25; }

	[[nodiscard]] std::string GetCondimentDescription() const override { return "Cream"; }
};

enum class LiqueurType
{
	Nutty,
	Chocolate
};

std::string ToStringLiqueurType(LiqueurType liqueurType)
{
	switch (liqueurType)
	{
	case LiqueurType::Chocolate:
		return "Chocolate";
	case LiqueurType::Nutty:
	default:
		return "Nutty";
	}
}

class CLiqueur : public CCondimentDecorator
{
public:
	CLiqueur(IBeveragePtr&& beverage, LiqueurType liqueurType)
		: CCondimentDecorator(std::move(beverage))
		, m_liqueurType(liqueurType)
	{
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{

		return ToStringLiqueurType(m_liqueurType) + " Liqueur";
	}

	[[nodiscard]] double GetCondimentCost() const override
	{
		return 50;
	}

private:
	LiqueurType m_liqueurType;
};