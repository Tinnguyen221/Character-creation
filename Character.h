/******************************************************************************
Spring 2024 Programming Foundations I
Author: STUDENT NAME
Date: April ???, 2024
Purpose: Define the Character class
*******************************************************************************/

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Character {
    public:
        Character(); // default constructor
        Character(const string newName, const string newClassName, const int newLevel, const bool newIsCaster); // parameterized constructor
        Character(Character &other); // copy constructor
        ~Character(); // destructor

        // getters
        string getName() const;
        string getClassName() const;
        int getHitPoints() const;
        int getLevel() const;
        int getStat(const int index) const;
        bool getIsCaster() const;

        // setters
        void setName(const string newName);
        void setClassName(const string newClassName);
        void setLevel(const int newLevel);
        void setStats(const int strength, const int dexterity, const int constitution, const int intelligence, const int wisdom, const int charisma);
        void setSingleStat(const int index, const int score);
        void setIsCaster(const bool newIsCaster);

        // other functions
        void print() const;
        void reset();
        bool saveCharacterSheet() const;
        void generateSpellList(const string complete_spells[], const int size);
        void generateRandomStats();
        void generateHitPoints();

        // indeces for the stats array
        static const int STR = 0;
        static const int DEX = 1;
        static const int CON = 2;
        static const int INT = 3;
        static const int WIS = 4;
        static const int CHA = 5;
    
    private:
        string name;
        string className;
        int hitPoints;
        int level;
        int stats[6];
        string spellList[10];
        bool isCaster;
        static const int STAT_SIZE = 6;
        static const int SPELL_LIST_SIZE = 10;
};

#endif