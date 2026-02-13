/*
    Authors: Jose Martinez-Ponce, Marcel Castillo, Benjamin Kunze
    Date: 02/12/2026
    Purpose: To make a ROOMBA clean a 10x10 room with a bumper as its only sensor onboard.
*/

#include <iostream>
#include <ctime>
using namespace std;

int inc(int x) // inc x
{
    x++;
    return x;
}

int dec(int x) // dec x
{
    x--;
    return x;
}

int collide(int x, int y)
{
    // 0,0 == Home
    // (0,1) - (0,9) == Left Border
    // (9,0) - (9,9) == Right Border
    // (0,1) - (0,9) == Top Border
    // (0,9) - (9,9) == Bottom Border

    /*
       Example:

        if ROOMBA collides into bottom border @ (3,10)
            ROOMBA has collided into bottom border

        if ROOMBA collides into top border @ (8,-1)
            ROOMBA has collided into top border

        if ROOMBA collides into left border @ (-1,5)
            ROOMBA has collided into left border

        if ROOMBA collides into right border @ (10,4)
            ROOMBA has collied into right border
    */

    if (x < 0)
    {
        x++;
        // debug
        std::cout << "ROOMBA has collided into LEFT border! " << '\n';
        return true;
    }
    else if (x > 9)
    {
        x--;
        // debug
        std::cout << "ROOMBA has collied into RIGHT border " << '\n';
        return true;
    }
    else if (y < 0)
    {
        y++;
        // debug
        std::cout << "ROOMBA has collided into TOP border " << '\n';
        return true;
    }
    else if (y > 9)
    {
        y--;
        // debug
        std::cout << "ROOMBA has collided into BOTTOM border! " << '\n';
        return true;
    }
    else
    {
        // debug
        std::cout << "ROOMBA is FREE!" << '\n';
        return false;
    }
}

string setDir(int direction)
{
    string myDirection;

    switch (direction)
    {
    case 0:
    {
        myDirection = "North";
        break;
    }
    case 1:
    {
        myDirection = "East";
        break;
    }
    case 2:
    {
        myDirection = "South";
        break;
    }
    case 3:
    {
        myDirection = "West";
        break;
    }
    }

    return myDirection;
}

int main()
{
    srand(time(0));

    // init. ROOMBA coords --> starts at HOMEBASE
    int roomX = 0;
    int roomY = 0;

    // randomize dirt location
    int dirtX = rand() % 10;
    int dirtY = rand() % 10;
    if (dirtX == 0 && dirtY == 0) // dirt location cannot be (0,0)
    {
        dirtX = rand() % 10;
        dirtY = rand() % 10;
    }

    std::cout << "--------------------------" << '\n'
              << "Dirt Location: " << "(" << dirtX << "," << dirtY << ")" << '\n'
              << "--------------------------" << '\n';

    // randomize initial direction
    int dir = rand() % 4; // 0 = north, 1 = east, 2 = south, 3 = west

    // dirAmbiguity: tracks weather or not we know what direction ROOMBA is facing
    bool dirAmbiguity = true;

    // initial roomba location
    int x = 0;
    int y = 0;

    cout << "--------------------------" << '\n'
         << "Random Direction set: " << setDir(dir) << endl
         << "--------------------------" << '\n';

    /*
    // debug
    int x_test = 10;
    int y_test = 10;
    std::cout << "TEST CASE COORDS: " << '\n'
              << "--------------------------" << '\n'
              << "X: " << x_test << '\n'
              << "Y: " << y_test << '\n'
              << "Collided at: " << collide(x_test, y_test) << '\n'
              << "--------------------------" << '\n';
    */

    // roomba movement based on rotation direction

    while (dirAmbiguity)
    {
        int collisionCount = 0;

        if (dir == 0) // if facing north --> y--
            dec(y);
        else if (dir == 1)
            inc(x);
        else if (dir == 2)
            inc(y);
        else if (dir == 3)
            dec(x);

        bool collision = collide(x, y);
        if (collision)
        {
            dir = (dir + 1) % 4;
            collisionCount++;
        }
        else if (collision && collisionCount == 1)
        {
            dir = (dir + 1) % 4;
            collisionCount++;
            cout << "You are now facing right" << endl;
            dirAmbiguity = false;
        }
        else if (!collision && collisionCount == 1)
        {
            cout << "You are now facing right" << endl;
            dirAmbiguity = false;
        }
        else
        {
            cout << "Some other case" << endl;
            dirAmbiguity = false;
        }
    }

    cout << dirtX << " " << dirtY << " " << dir << endl;
}
