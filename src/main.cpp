#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <array>

#define NUMBER_OF_DOORS         3
#define NUMBER_OF_SIMULATIONS   123456

enum DoorState
{
    open,
    closed
};

enum DoorPrize
{
    car,
    goat
};

struct Door
{
    DoorPrize   prize;
    DoorState   state;
    bool        selected;

    Door() : prize(DoorPrize::goat), state(DoorState::closed), selected(false) {};

    Door(DoorPrize p) : prize(p), state(DoorState::closed), selected(false) {};
};

struct Doors
{
    std::array<Door, NUMBER_OF_DOORS> arrDoors;
    Door *pChoice;

    Doors() : arrDoors(), pChoice(NULL)
    {
        arrDoors[rand() % 3].prize = DoorPrize::car;
    };

    void chooseDoor(unsigned int doorIndex)
    {
        if (doorIndex > NUMBER_OF_DOORS - 1)
        {
            throw std::invalid_argument("door index must be within range [0, NUMBER_OF_DOORS - 1]"); 
        }

        arrDoors[doorIndex].selected = true;
    };

    void openBadDoor()
    {
        for (Door& door : arrDoors)
        {
            if (door.selected == false && door.prize == DoorPrize::goat)
            {
                door.state = DoorState::open;
                break;
            }
        }
    };

    unsigned int revealPrize()
    {
        for (int i = 0; i < NUMBER_OF_DOORS; i++)
        {
            if (arrDoors[i].prize == DoorPrize::car)
            {
                return i;
            }
        }
        return -1; 
    }
};

int main (int argc, char *argv[]) 
{
    srand(time(NULL));
    
    unsigned int correctGuesses = 0;

    for (int i = 0; i < NUMBER_OF_SIMULATIONS; i++)
    {
        Doors doors;

        doors.chooseDoor(0);
        doors.openBadDoor();

        if (0 == doors.revealPrize())
        {
            correctGuesses++;
        }
    }

    printf("correct guesses: %f%%\n", static_cast<double>(static_cast<double>(correctGuesses) * 100 / NUMBER_OF_SIMULATIONS));
}




