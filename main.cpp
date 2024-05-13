/******************************************************************************
Spring 2024 Programming Foundations I
Author: STUDENT NAME
Date: April ???, 2024
Purpose: Make a character creator using the Character class
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "Character.cpp"
using namespace std;

// size of complete_spell_list.txt
const int SPELL_DOC_SIZE = 46;

// -------------------------------------------------
// Name: readInSpells
// Parameters: pass-by-value string filename
//             string array arr
//             pass-by-value int arr_size
// Returns: bool - true when successful, false otherwise
// Purpose: Opens the file with filename and reads in spells line-by-line into the array arr of size arr_size
// -------------------------------------------------
bool readInSpells (string filename, string arr[], const int arr_size)
{
    // Open file
    ifstream spell_document;
    spell_document.open(filename);

    // Error checking if file cannot be opened
    if (!spell_document.is_open())
    {
        cout << "Error opening " << filename << endl;
        return false;
    }

    // Otherwise, get each line and save it into the array
    else {
        for (int i = 0; i < arr_size; i++) {
            getline(spell_document, arr[i]);
        }
        return true; 
    }
}

int main()
{
    /* YOU SHOULD NOT CHANGE CODE BELOW THIS LINE UNLESS TO UNCOMMENT IT */

    // declare and initialize needed variables
    string all_spells[SPELL_DOC_SIZE];
    for (int i = 0; i < SPELL_DOC_SIZE; i++)
        all_spells[i] = "Empty";
    
    string character_name = "";
    string character_class = "";
    int character_level, choice = 0;
    bool makeAnother = false;

    // Testing methods...
    cout << "Testing readInSpells()..." << endl;
    if (readInSpells("complete_spell_list.txt", all_spells, SPELL_DOC_SIZE))
    {
        cout << "Read in spells successfully" << endl << endl;
    }

    cout << "Testing constructor..." << endl;
    Character magnus;
    magnus.print();
    cout << endl;

    cout << "Testing parameterized constructor..." << endl;
    Character merle("Merle", "Cleric", 1, true);
    merle.generateSpellList(all_spells, SPELL_DOC_SIZE);
    merle.print();
    cout << endl;

    cout << "Testing copy constructor..." << endl;
    Character merle2(merle);
    merle2.print();
    cout << endl;

    cout << "Testing setters..." << endl;
    magnus.setName("Magnus");
    magnus.setClassName("Fighter");
    magnus.setIsCaster(false);
    magnus.setLevel(3);
    magnus.setStats(18, 14, 15, 10, 11, 12);
    magnus.setSingleStat(Character::STR, 20);
    magnus.generateHitPoints();
    magnus.print();
    cout << endl;

    cout << "Testing saveCharacterSheet()..." << endl;
    if (magnus.saveCharacterSheet())
    {
        cout << "Successfully saved character sheet." << endl << endl;
    }

    /* YOU SHOULD NOT CHANGE CODE ABOVE THIS LINE UNLESS TO UNCOMMENT IT*/

    /* WHERE CHARACTER CREATOR BEGINS! */
    /** YOUR CODE GOES BELOW! */

    // Welcome user
    cout << "Welcome to the Basic DnD Character Creator!\n";

    // Object creation
        Character newCharacter; 
    
        // Variable declaration
        string name;
        int classChoice;
        string className;
        int level;
        bool repeatLoop;

    // do...
    do {

        // Prompt user for character name
        cout << "What do you want to name your character?\n";
        cin >> name;
        newCharacter.setName(name);

        // Prompt user for character class
        cout << "What class do you want your character to be?\n"
	         << "1. Fighter\n"
	         << "2. Rogue\n"
	         << "3. Wizard\n"
	         << "4. Cleric\n";

        // Set class
        cin >> classChoice;

            // Error checking
            while (classChoice < 1 || classChoice > 4) {
                cout << "Invalid choice. Please choose again\n";
                cin >> classChoice;
            }


        switch (classChoice) {
            case 1:
                className = "Fighter"; 
                break;
            case 2:
                className = "Rogue";
                break;
            case 3:
                className = "Wizard";
                break;
            case 4:
                className = "Cleric";
                break;
            default:
                className = "None selected";
                break;
        }
        
        newCharacter.setClassName(className);

        // Checking if user chooses a spell caster
        newCharacter.setIsCaster(classChoice == 3 || classChoice == 4);
        if (newCharacter.getIsCaster()) {
            newCharacter.generateSpellList(all_spells, SPELL_DOC_SIZE);
        }

        // Prompt user for character level
        cout << "What level is your character?\n";

        // Set level
        cin >> level;
            // Error checking
            while (level < 1 || level > 20) {
                cout << "Invalid choice. Please choose again\n";
                cin >> level;
            }
        newCharacter.setLevel(level);

        // Generate random Stats
        newCharacter.generateRandomStats();

        // Now that level, class, and stats are known, generate the character's hit points
        newCharacter.generateHitPoints(); 

        // do...
        do {

            // Print out the character
            newCharacter.print();

            // Print menu
            cout << "Would you like to do anything else?\n"
	             << "1. Change stats and regenerate hit points\n"
	             << "2. Generate a different spell list\n"
	             << "3. No. I'm finished with this character\n";    
            
            cin >> choice;

            while (choice < 1 || choice > 3) {
                cout << "Invalid choice. Please choose again\n";
                cin >> choice;
            }

            // If they chose to change stats and regenerate hit points...
            if (choice == 1) {
                // Ask if user wants to generate random stats or enter stats
                cout << "Would you like to...\n"
                     << "1. Generate new random stats\n"
                     << "2. Set all stats by hand\n";
                cin >> choice;
                    while (choice < 1 || choice > 2) {
                        cout << "Invalid choice. Please choose again\n";
                        cin >> choice;
                    }

                // if they want to generate random stats...
                if (choice == 1) {
                        newCharacter.generateRandomStats();
                        //newCharacter.print();
                    }
            

                // otherwise, if they want to enter stats by hand...
                else {

                    // Prompt user for stats
                    cout << "Enter scores for Strength, Dexterity, Constitution, Intelligence, Wisdom, and Charisma one at a time (in that order!)\n";

                    // For each stat...
                    for (int i = 0; i < 6; i++) {
                        // Get user input
                        cin >> choice;
                        
                        // Check that the new score is valid...
                        while (choice < 8 || choice > 20) {
                                cout << "Invalid choice. Please choose again\n";
                                cin >> choice;
                            }


                        // Set stat
                        newCharacter.setSingleStat(i, choice);
                    }
                }
            }
                // Generate new hit points
                newCharacter.generateHitPoints();
            
            // otherwise, if they want to generate a new spell list...
            if (choice == 2) {
            
                // if the character is a spellcaster...
                if (newCharacter.getIsCaster()) {
                
                    // generate a new spell list
                    newCharacter.generateSpellList(all_spells, SPELL_DOC_SIZE); 
                }
                
                // otherwise (if the character ISN'T a spellcaster)
                else {
                
                    // Print out message to user that their character isn't a caster
                    cout << "This character isn't a caster! They don't have a spell list.\n";
                }
            }

        }            
        // while the user isn't finished with their character
        while (choice != 3);

        if (choice == 3) {
                cout << "What would you like to do now that " << name << " is finished?\n";
            }


        // Prompt the user if they would like to save or scrap their character
        cout << "1. Save character\n" 
	         << "2. Scrap character and start over\n";
                    
        cin >> choice;
        while (choice < 1 || choice > 2) {
            cout << "Invalid choice. Please choose again\n";
            cin >> choice;
        }
        
        // if they choose to save their character...
        if (choice == 1) {    

            // If the character sheet is saved successfully...
            if (newCharacter.saveCharacterSheet()) {

                // Print out a message to the user saying so
                cout << name << " successfully saved!\n";
            }
            
            // otherwise...
            else {

                // Print an error message
                cout << "Character save failed\n";
            }
        
        
            // Prompt user to see if they want to make another character
            cout << "Would you like to make another character?\n"
                 << "1. Yes\n"
                 << "2. No\n";
            cin >> choice;
            //Error checking
            while (choice < 1 || choice > 2) {
            cout << "Invalid choice. Please choose again\n";
            cin >> choice;
            }

            // if the user said yes...
            if (choice == 1) {
            
                // reset the character
                newCharacter.reset();

                // repeat the loop
                repeatLoop = true;
            }
            
            // otherwise (the user said no)
            else {

                // don't repeat the loop
                cout << "Thanks for using the Character Creator! Happy rolling!\n";
                return 0;
            }    
        }
        // Otherwise, if they chose to scrap their character and start over...
        if (choice == 2) {
        
            // reset the character
            newCharacter.reset();

            // repeat the loop
            repeatLoop = true;
        }    

    }
    // while the user wants to repeat the loop and make another character
    while (repeatLoop);

    // Print goodbye message
    cout << "Thanks for using the Character Creator! Happy rolling!\n";
    
    return 0;
}