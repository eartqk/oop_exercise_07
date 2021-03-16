#pragma once

#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

const int ID_Octagon = 1;
const int ID_Triangle = 2;
const int ID_Square = 3;

class Figure
{
public:
	virtual void Print() = 0;
	virtual void Save(std::ostream &file) = 0;
	virtual ~Figure() {}
};

template <typename T>
class Octagon : public Figure
{
private:
	using coord = std::pair<T, T>;
	coord a, b, c, d, e, f, g, h;
	coord center;
	size_t side;

public:
	Octagon(T s, coord center) : side(s), center(center)
	{
		a.first = center.first - (double)side / 2;
		b.first = center.first + (double)side / 2;
		a.second = b.second = center.second + (double)side / 2 + side / sqrt(2);

		c.first = d.first = center.first + (double)side / 2 + side / sqrt(2);
		c.second = center.second + side / sqrt(2);
		d.second = center.second - side / sqrt(2);

		e.first = b.first;
		f.first = a.first;
		e.second = f.second = center.second - (double)side / 2 - side / sqrt(2);

		g.first = h.first = center.first - (double)side / 2 - side / sqrt(2);
		g.second = d.second;
		h.second = c.second;
	}

	Octagon() {}

	~Octagon()
	{
		side = 0;
	}

	void Print() override
	{
		std::cout << "Octagon: \n";
		std::cout << "Coordinate of center - (" << center.first << ", " << center.second << ") \n";
		std::cout << "Coordinates of vertex: \n";
		std::cout << std::fixed;
		std::cout << "(" << std::setprecision(6) << a.first << ", " << std::setprecision(6) << a.second << "), \n";
		std::cout << "(" << std::setprecision(6) << b.first << ", " << std::setprecision(6) << b.second << "), \n";
		std::cout << "(" << std::setprecision(6) << c.first << ", " << std::setprecision(6) << c.second << "), \n";
		std::cout << "(" << std::setprecision(6) << d.first << ", " << std::setprecision(6) << d.second << "), \n";
		std::cout << "(" << std::setprecision(6) << e.first << ", " << std::setprecision(6) << f.second << "), \n";
		std::cout << "(" << std::setprecision(6) << f.first << ", " << std::setprecision(6) << e.second << "), \n";
		std::cout << "(" << std::setprecision(6) << g.first << ", " << std::setprecision(6) << g.second << "), \n";
		std::cout << "(" << std::setprecision(6) << h.first << ", " << std::setprecision(6) << h.second << ").\n"
				  << std::endl;
	}

	void Save(std::ostream &file) override
	{
		file.write((char *)&ID_Octagon, sizeof(int));
		file.write((char *)&side, sizeof(size_t));
		file.write((char *)&center, sizeof(coord));
	}
};

template <typename T>
class Triangle : public Figure
{
private:
	using coord = std::pair<T, T>;
	coord a, b, c;
	coord center;
	size_t side;

public:
	Triangle(T s, coord center) : side(s), center(center)
	{
		a.first = center.first;
		a.second = center.second + side / sqrt(3);
		b.first = center.first + (double)side / 2;
		c.first = center.first - (double)side / 2;
		b.second = c.second = center.second - sqrt(3) * side / 6;
	}

	Triangle() {}

	~Triangle()
	{
		side = 0;
	}

	void Print() override
	{
		std::cout << "Triangle: \n";
		std::cout << "Coordinate of center - (" << center.first << ", " << center.second << ") \n";
		std::cout << "Coordinates of vertex: \n";
		std::cout << std::fixed;
		std::cout << "(" << std::setprecision(6) << a.first << ", " << std::setprecision(6) << a.second << "), \n";
		std::cout << "(" << std::setprecision(6) << b.first << ", " << std::setprecision(6) << b.second << "), \n";
		std::cout << "(" << std::setprecision(6) << c.first << ", " << std::setprecision(6) << c.second << ").\n"
				  << std::endl;
	}

	void Save(std::ostream &file) override
	{
		file.write((char *)&ID_Triangle, sizeof(int));
		file.write((char *)&side, sizeof(size_t));
		file.write((char *)&center, sizeof(coord));
	}
};

template <typename T>
class Square : public Figure
{
private:
	using coord = std::pair<T, T>;
	coord a, b, c, d;
	coord center;
	size_t side;

public:
	Square(T s, coord center) : side(s), center(center)
	{
		a.first = d.first = center.first - (double)side / 2;
		b.first = c.first = center.first + (double)side / 2;
		a.second = b.second = center.second + (double)side / 2;
		d.second = c.second = center.second - (double)side / 2;
	}

	Square() {}

	~Square()
	{
		side = 0;
	}

	void Print() override
	{
		std::cout << "Square: \n";
		std::cout << "Coordinate of center - (" << center.first << ", " << center.second << ") \n";
		std::cout << "Coordinates of vertex: \n";
		std::cout << std::fixed;
		std::cout << "(" << std::setprecision(6) << a.first << ", " << std::setprecision(6) << a.second << "), \n";
		std::cout << "(" << std::setprecision(6) << b.first << ", " << std::setprecision(6) << b.second << "), \n";
		std::cout << "(" << std::setprecision(6) << c.first << ", " << std::setprecision(6) << c.second << "), \n";
		std::cout << "(" << std::setprecision(6) << d.first << ", " << std::setprecision(6) << d.second << ").\n"
				  << std::endl;
	}

	void Save(std::ostream &file) override
	{
		file.write((char *)&ID_Square, sizeof(int));
		file.write((char *)&side, sizeof(size_t));
		file.write((char *)&center, sizeof(coord));
	}
};