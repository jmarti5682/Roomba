#include <iostream>
#include <ctime>
using namespace std;
int inc(int x)
{
    x++;
    return x;
}
int dec(int x)
{
    x--;
    return x;
}
int collide(int x, int y)
{
    if(x < 0)
    {
        x++;
        return true;
    }
    else if(x > 9)
    {
        x--;
        return true;
    }
    else if(y < 0)
    {
        y++;
        return true;
    }
    else if(y > 9)
    {
        y--;
        return true;
    }
    else
        return false;
}

int main()
{
    srand(time(0));

    //randomize dirt location
    int dirtX = rand() % 10;
    int dirtY = rand() % 10;

    //randomize initial direction
    int dir = rand() % 4; //0 = north, 1 = east, 2 = south, 3 = west
    cout << dir << endl;
    bool dirAmbiguity = true;

    //initial roomba location
    int x = 0;
    int y = 0;

    //roomba movement based on rotation direction
   
    while(dirAmbiguity)
    {
        int collisionCount = 0;

        if(dir == 0)
            dec(y);
        else if(dir == 1)
            inc(x);
        else if(dir == 2)
            inc(y);
        else if(dir == 3)
            dec(x);

        bool collision = collide(x, y);
        if(collision)
        {
            dir = (dir + 1) % 4;
            collisionCount++;
        }
        else if(collision && collisionCount == 1)
        {
            dir = (dir + 1) % 4;
            collisionCount++;
            cout << "You are now facing right" << endl;
            dirAmbiguity = false;
        }
        else if(!collision && collisionCount == 1)
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