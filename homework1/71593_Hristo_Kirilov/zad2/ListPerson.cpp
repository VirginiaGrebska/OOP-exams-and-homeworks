#include "ListPerson.h"

ListPerson:: ListPerson():
    arr(NULL),size(0),maxSize(0)
{
    fillZodii();
}

ListPerson:: ListPerson(const Vizitka& other):
    size(1),maxSize(1)
{
    arr = new Vizitka [maxSize];
    strncpy(arr[0].name,other.name,20);
    strncpy(arr[0].date,other.date,11);
    fillZodii();
}

ListPerson:: ListPerson(const ListPerson& other):
    size(other.size),maxSize(other.maxSize)
{
    if(other.arr != NULL)
    {
        arr = new Vizitka [maxSize];
        for(int i = 0; i < size; i++)
        {
            strncpy(arr[i].name,other.arr[i].name,20);
            strncpy(arr[i].date,other.arr[i].date,11);
        }
    }
    else arr = NULL;
}

ListPerson:: ~ListPerson()
{
    delete [] arr;
}

ListPerson& ListPerson:: operator= (const ListPerson& other)
{
    if(this == &other)
        return *this;
    size = other.size;
    maxSize = other.maxSize;
    if(other.arr != NULL)
    {
        if(arr != NULL)
            delete [] arr;
        arr = new Vizitka [maxSize];
        for(int i = 0; i < size; i++)
        {
            strncpy(arr[i].name,other.arr[i].name,20);
            strncpy(arr[i].date,other.arr[i].date,11);
        }
    }
    else
        arr = NULL;
    return *this;
}

void ListPerson:: addVizitka (const Vizitka& other)
{
    bool flag = 1;
    for(int i = 0; i < size && flag; i++)
        if (strcmp(arr[i].name,other.name) == 0)
            flag = 0;
    if (flag)
    {
        if(size == maxSize)
        {
            if(arr != NULL)
            {
                maxSize *= 2;
                Vizitka *tmp;
                tmp = new Vizitka [maxSize];
                for(int i = 0; i < size; i++)
                {
                    strncpy(tmp[i].name,arr[i].name,20);
                    strncpy(tmp[i].date,arr[i].date,11);
                }
                delete [] arr;
                arr = tmp;
            }
            else
            {
                maxSize = 1;
                arr = new Vizitka [maxSize];
            }
        }
        strncpy(arr[size].name,other.name,20);
        strncpy(arr[size++].date,other.date,11);
    }
}

void ListPerson:: removeVizitka (const Vizitka& other)
{
    bool flag = 1;
    for (int i = 0 ;i < size && flag; i++)
    {
        if(strcmp(arr[i].name,other.name) == 0)
        {
            if(--size == 0)
            {
                arr = NULL;
                maxSize = 0;
            }
            else
            {
                strncpy(arr[i].name, arr[size].name, 20);
                strncpy(arr[i].date, arr[size].date, 11);
                if (size * 2 < maxSize)
                {
                    maxSize /= 2;
                    Vizitka * tmp;
                    tmp = new Vizitka[maxSize];
                    for(int i = 0; i < size; i++)
                    {
                        strncpy(tmp[i].name,arr[i].name,20);
                        strncpy(tmp[i].date,arr[i].date,11);
                    }
                    delete [] arr;
                    arr = tmp;
                }
            }
            flag = 0;
        }
    }
    if (flag)
        cout << "Vizitkata ne e namerena.\n";
}

Vizitka& ListPerson:: findVizitka (const char* name)
{
    for (int i = 0; i < size; i++)
        if(strcmp(arr[i].name,name) == 0)
            return arr[i];
    cout << "Vizitkata ne beshe otkrita. \n";
    Vizitka error;
    error.name[0] = '\0';
    error.date[0] = '\0';
    return error;
}

ListPerson& ListPerson:: operator+= (const ListPerson& other)
{
    if(this == & other)
        return *this;
    if(size + other.size > maxSize)
    {
        if(maxSize == 0)
        {
            arr = new Vizitka [other.maxSize];
            maxSize = other.maxSize;
        }
        else
        {
            maxSize = size + other.size;
            Vizitka *tmp;
            tmp = new Vizitka [maxSize];
            for(int i = 0; i < size; i++)
            {
                strncpy(tmp[i].name,arr[i].name,20);
                strncpy(tmp[i].date,arr[i].date,11);
            }
            delete [] arr;
            arr = tmp;
        }
    }
    for (int j = 0; j < other.size; j++)
    {
        bool flag = 1;
        for(int i = 0; i < size && flag; i++)
            if (strcmp(arr[i].name,other.arr[j].name) == 0)
                flag = 0;
        if (flag)
        {
            strncpy(arr[size].name, other.arr[j].name, 20);
            strncpy(arr[size++].date, other.arr[j].date, 11);
        }
    }
    return *this;
}

ListPerson& ListPerson:: operator-= (const ListPerson& other)
{
    if(this == &other)
    {
        delete [] arr;
        size = 0;
        maxSize = 0;
        return *this;
    }
    for(int i = 0; i < size; i++)
    {
        bool flag = 1;
        for (int j = 0; j < other.size && flag; j++)
            if (strcmp(arr[i].name,other.arr[j].name) == 0)
                flag = 0;
        if(!flag)
            removeVizitka(arr[i]);
    }
    return *this;
}
ListPerson& ListPerson:: operator== (const ListPerson& other)
{
    if(this == &other)
        return *this;
    for(int i = 0;i < size; i++)
    {
        bool flag = 1;
        for(int j = 0; j < other.size && flag; j++)
            if (strcmp(arr[i].name,other.arr[j].name) == 0)
                flag = 0;
        if (flag)
            removeVizitka(arr[i]);
    }
    return * this;
}

void ListPerson:: fillZodii ()
{
    strncpy(zodii[0].name, "Oven\0", 5);
    zodii[0].startDay = 21;
    zodii[0].startMonth = 3;
    zodii[0].endDay = 21;
    zodii[0].endMonth = 4;

    strncpy(zodii[1].name, "Telec\0", 6);
    zodii[1].startDay = 22;
    zodii[1].startMonth = 4;
    zodii[1].endDay = 20;
    zodii[1].endMonth = 5;

    strncpy(zodii[2].name, "Bliznaci\0", 9);
    zodii[2].startDay = 21;
    zodii[2].startMonth = 5;
    zodii[2].endDay = 21;
    zodii[2].endMonth = 6;

    strncpy(zodii[3].name, "Rak\0", 4);
    zodii[3].startDay = 22;
    zodii[3].startMonth = 6;
    zodii[3].endDay = 21;
    zodii[3].endMonth = 7;

    strncpy(zodii[4].name, "Lav\0", 4);
    zodii[4].startDay = 22;
    zodii[4].startMonth = 7;
    zodii[4].endDay = 23;
    zodii[4].endMonth = 8;

    strncpy(zodii[5].name, "Deva\0", 5);
    zodii[5].startDay = 24;
    zodii[5].startMonth = 8;
    zodii[5].endDay = 22;
    zodii[5].endMonth = 9;

    strncpy(zodii[6].name, "Vezni\0", 6);
    zodii[6].startDay = 23;
    zodii[6].startMonth = 9;
    zodii[6].endDay = 22;
    zodii[6].endMonth = 1;

    strncpy(zodii[7].name, "Skorpion\0", 9);
    zodii[7].startDay = 23;
    zodii[7].startMonth = 10;
    zodii[7].endDay = 21;
    zodii[7].endMonth = 11;

    strncpy(zodii[8].name, "Strelec\0", 8);
    zodii[8].startDay = 22;
    zodii[8].startMonth = 11;
    zodii[8].endDay = 21;
    zodii[8].endMonth = 12;

    strncpy(zodii[9].name, "Kozirog\0", 8);
    zodii[9].startDay = 22;
    zodii[9].startMonth = 12;
    zodii[9].endDay = 20;
    zodii[9].endMonth = 1;

    strncpy(zodii[10].name, "Vodolei\0", 8);
    zodii[10].startDay = 21;
    zodii[10].startMonth = 1;
    zodii[10].endDay = 19;
    zodii[10].endMonth = 2;

    strncpy(zodii[11].name, "Ribi\0", 5);
    zodii[11].startDay = 20;
    zodii[11].startMonth = 2;
    zodii[11].endDay = 20;
    zodii[11].endMonth = 3;
}

Zodiac& ListPerson:: findZodiac (const char* name)
{
    Vizitka person = findVizitka(name);
    unsigned day, month;
    day = 10 * (person.date[0] - '0') + (person.date[1] - '0');
    month =10 * (person.date[3] - '0') + (person.date[4] - '0');
    for(int i = 0; i < 12; i++)
    {
        if(zodii[i].startMonth == month && day >= zodii[i].startDay)
            return zodii[i];
        if(zodii[i].startMonth == month)
            return zodii[i-1];
    }

}
