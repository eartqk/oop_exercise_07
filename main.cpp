// Артамонов Олег, М80-208Б
// Вариант 16, 8-угольник, треугольник, квадрат

#include <iostream>
#include <algorithm>

#include "factory.h"
#include "document.h"

void help()
{
    std::cout << "0 - Print help information.\n";
    std::cout << "1 - Add figure.\n";
    std::cout << "2 - Delete figure.\n";
    std::cout << "3 - Print actual info/file.\n";
    std::cout << "4 - Undo last action.\n";
    std::cout << "5 - Create a new file.\n";
    std::cout << "6 - Save info to file.\n";
    std::cout << "7 - Load file.\n";
    std::cout << "8 - Exit.\n";
}

int main()
{
    std::ofstream fout;
    std::ifstream fin;
    Document doc;
    int choice;
    unsigned long position;
    char filename[50];
    help();
    std::cout << ">> ";
    while (true)
    {
        std::cin >> choice;
        switch (choice)
        {
        case 0:
            help();
            break;
        case 1:
            std::cout << "Select the position where you want to save figure: ";
            std::cin >> position;
            try
            {
                if (position > doc.figures.size() + 1)
                {
                    throw position;
                }
            }
            catch (const unsigned long a)
            {
                std::cout << "There is no such position.\n";
                break;
            }
            doc.AddElem(position);
            std::cout << "Done.\n";
            break;
        case 2:
            std::cout << "Enter the position of the figure you want to delete: ";
            try
            {
                std::cin >> position;
                if (position > doc.figures.size())
                {
                    throw position;
                }
            }
            catch (const unsigned long s)
            {
                std::cout << "There is no such position.\n";
                break;
            }
            doc.DeleteElem(position);
            std::cout << "Done.\n";
            break;
        case 3:
        {
            auto print = [](std::shared_ptr<Figure> elem) {
                elem->Print();
            };
            std::for_each(doc.figures.begin(), doc.figures.end(), print);
            break;
        }
        case 4:
            doc.Undo();
            break;
        case 5:
            doc.CreateNew();
            break;
        case 6:
            std::cout << "Enter the name of file to save: ";
            std::cin >> filename;
            fout.open(filename, std::ios::out);
            doc.Save(fout);
            std::cout << "The file was saved.\n";
            fout.close();
            break;
        case 7:
            std::cout << "Enter the name of file to load: ";
            std::cin >> filename;
            fin.open(filename, std::ios::in);
            if (fin)
            {
                doc.Load(fin);
                std::cout << "The file has been loaded.\n";
                fin.close();
            }
            else
            {
                std::cout << "Can't open the file.\n";
            }
            break;
        case 8:
            std::cout << "Goodbye.\n";
            return false;
            break;
        default:
            std::cout << "Incorrect input!\n";
            break;
        }
        std::cout << ">> ";
    }
}