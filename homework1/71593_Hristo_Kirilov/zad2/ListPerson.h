#ifndef LISTPERSON_H
#define LISTPERSON_H
#include "structures.h"

class ListPerson
{
private:
    Vizitka* arr;
    unsigned size,
             maxSize;
    Zodiac zodii[12];
    void fillZodii ();
public:
    ListPerson();
    ListPerson(const Vizitka&);
    ListPerson(const ListPerson&);
    ~ListPerson();
    ListPerson& operator= (const ListPerson&);

    void addVizitka (const Vizitka&);
    void removeVizitka (const Vizitka&);
    Vizitka& findVizitka (const char*);

    ListPerson& operator+= (const ListPerson&);     //Обединение на две картотеки
    ListPerson& operator-= (const ListPerson&);     //Разлика на две картотеки
    ListPerson& operator== (const ListPerson&);     //Сецхение на две картотеки

    Zodiac& findZodiac (const char*);

    void print ()
    {
        for(int i = 0; i < size; i++)
            cout << arr[i].name << endl << arr[i].date << endl << endl;
    }
};

#endif // LISTPERSON_H
