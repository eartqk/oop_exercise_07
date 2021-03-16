#pragma once

#include <fstream>
#include <list>
#include <stack>

#include "factory.h"

class Document
{
	class TAction
	{
	public:
		virtual void Action(Document &doc) = 0;
		virtual ~TAction() {}
	};

	class AddAction : public TAction
	{
	private:
		size_t position;
		std::shared_ptr<Figure> figure;

	public:
		AddAction(size_t n, std::shared_ptr<Figure> f) : position(n), figure(f) {}
		void Action(Document &doc) override
		{
			doc.Add(position, figure);
			doc.actions.pop();
		}
	};

	class DeleteAction : public TAction
	{
	private:
		size_t position;

	public:
		DeleteAction(size_t n) : position(n) {}
		void Action(Document &doc) override
		{
			doc.Delete(position);
		}
	};

public:
	void CreateNew()
	{
		figures.clear();
		while (!actions.empty())
		{
			actions.pop();
		}
	}

	void Save(std::ostream &file)
	{
		if (figures.size() == 0)
		{
			std::cout << "There are no figures to save.\n";
		}
		size_t size = figures.size();
		file.write((char *)&size, sizeof(size_t));
		for (auto i = figures.begin(); i != figures.end(); ++i)
		{
			(*i)->Save(file);
		}
	}

	void Load(std::istream &file)
	{
		CreateNew();
		size_t size, id, side;
		using coord = std::pair<double, double>;
		coord center;
		file.read((char *)&size, sizeof(size_t));
		for (unsigned long i = 0; i < size; ++i)
		{
			file.read((char *)&id, sizeof(int));
			file.read((char *)&side, sizeof(size_t));
			file.read((char *)&center, sizeof(coord));
			if (id == 1)
			{
				figures.push_back(std::shared_ptr<Figure>(new Octagon<double>(side, center)));
			}
			if (id == 2)
			{
				figures.push_back(std::shared_ptr<Figure>(new Triangle<double>(side, center)));
			}
			if (id == 3)
			{
				figures.push_back(std::shared_ptr<Figure>(new Square<double>(side, center)));
			}
		}
	}

	void AddElem(size_t pos)
	{
		int choice;
		std::cout << "1 - Octagon\n2 - Triangle\n3 - Square\n";
		std::cout << "Select a figure: ";
		std::cin >> choice;
		Add(pos, Factory<double>::CreateFigure(choice));
		TAction *act = new DeleteAction(pos);
		actions.push(std::shared_ptr<TAction>(act));
	}

	void Add(size_t pos, std::shared_ptr<Figure> fig)
	{
		if (fig == nullptr)
		{
			return;
		}
		if (pos == figures.size() + 1)
		{
			figures.push_back(fig);
		}
		else
		{
			auto it = figures.begin();

			for (size_t i = 1; i < pos; ++i)
			{
				++it;
			}
			figures.insert(it, fig);
		}
	}

	void Delete(size_t pos)
	{
		if (pos == figures.size())
		{
			figures.pop_back();
		}
		else
		{
			auto it = figures.begin();
			for (size_t i = 1; i < pos; ++i)
			{
				++it;
			}
			figures.erase(it);
		}
	}

	void DeleteElem(size_t pos)
	{
		if (pos == figures.size())
		{
			TAction *act = new AddAction(pos, figures.back());
			actions.push(std::shared_ptr<TAction>(act));
			figures.pop_back();
		}
		else
		{
			auto it = figures.begin();
			for (size_t i = 1; i < pos; ++i)
			{
				++it;
			}
			TAction *act = new AddAction(pos, *it);
			actions.push(std::shared_ptr<TAction>(act));
			figures.erase(it);
		}
	}

	void Undo()
	{
		if (actions.empty())
		{
			std::cout << "No recent actions to cancel.\n";
		}
		else
		{
			actions.top()->Action(*this);
			actions.pop();
		}
	}

	std::list<std::shared_ptr<Figure>> figures;
	std::stack<std::shared_ptr<TAction>> actions;
};