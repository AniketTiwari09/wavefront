/*
Name: Aniket Tiwari 
Date: 6/10/22
Description: The aim of this assignment is to create Pathfinder using Wavefront algorithm
Usage: g++ Tiwari_Aniket_hw2.cpp (using g++ as a C++ compiler and a.exe is the executable file)
       ./a.exe
*/

#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

ofstream myfile ("wave.txt");

// struct Node for storing coords
struct Node
{
   public: //defines public variables for the node class
    int x;
    int y;

    Node()
    {
        x = -1;
        y = -1;
    }
    Node(int X, int Y) //sets values for the nodes
    {
        x = X;
        y = Y;
    }
};

// struct Queue that implements a queue data structure using an array
struct Queue
{
   private:
    Node* arr;
    int front;
    int back;

   public: //performs queue functions on the struct
    void push(int x, int y) { arr[back++] = Node(x, y); }
    Node pop() { return arr[front++]; };
    bool empty() { return (front == back); };

    Queue(int N)
    {
        arr = (Node*)malloc((N + 1) * sizeof(Node));
        front = back = 0;
    }
};

//greed path finding function based on recursion
void greed(int** arr, int W, int H,int X,int Y,char** charr)
{
    int newX, newY;
    int mini = arr[Y][X];
    if(mini == 1)  //checks conditions for X and Y values and does operations based on them.
        return;
    else if(arr[Y-1][X-1] < mini && arr[Y-1][X-1] > 1)
    {
        charr[Y-1][X-1] = '*';
        newX = X-1;newY = Y-1;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y][X-1] < mini && arr[Y][X-1] > 1)
    {
        charr[Y][X-1] = '*';
        newX = X-1;newY = Y;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y+1][X-1] < mini && arr[Y+1][X-1] > 1)
    {
        charr[Y+1][X-1] = '*';
        newX = X-1;newY = Y+1;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y-1][X] < mini && arr[Y-1][X] > 1)
    {
        charr[Y-1][X] = '*';
        newX = X;newY = Y-1;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y][X] < mini && arr[Y][X] > 1)
    {
        charr[Y][X] = '*';
        newX = X;newY = Y;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y+1][X] < mini && arr[Y+1][X] > 1)
    {
        charr[Y+1][X] = '*';
        newX = X;newY = Y+1;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y-1][X+1] < mini && arr[Y-1][X+1] > 1)
    {
        charr[Y-1][X+1] = '*';
        newX = X+1;newY = Y-1;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y][X+1] < mini && arr[Y][X+1] > 1)
    {
        charr[Y][X+1] = '*';
        newX = X+1;newY = Y;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y+1][X+1] < mini && arr[Y+1][X+1] > 1)
    {
        charr[Y+1][X+1] = '*';
        newX = X+1;newY = Y+1;
        greed(arr, W, H, newX, newY, charr);
    }


}

//  function to print int array
void PrintEnvironment(int** arr, int W, int H) {
    cout << "arr:\n";
    myfile << "arr:\n";
    for (int i = 0; i < H; i++) //prints array based on the height and width
    {
        for (int j = 0; j < W; j++) {
            cout << setw(2) << arr[i][j] << " ";
            myfile << setw(2) << arr[i][j] << " ";
        }
        cout << "\n";
        myfile << "\n";
    }
}
// function to print char array
void CPrintEnvironment(char** arr, int W, int H) {
    cout << "arr:\n";
    myfile << "arr:\n";
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << setw(2) << arr[i][j] << " ";
            myfile << setw(2) << arr[i][j] << " ";
        }
        cout << "\n";
        myfile << "\n";
    }
}

// find and increment moore neighbour
void Moore(int** arr, int W, int H, int X, int Y) {
    Queue q(W * H);
    q.push(Y, X);

    while (!q.empty()) //loops while q is not empty
    {
        Node curr = q.pop();
        int i = curr.x, j = curr.y;
        bool north = (i > 0), south = (i < H - 1), east = (j < W - 1), west = (j > 0);

    //checks conditions based on different directions.
        if (north && east && !arr[i - 1][j + 1])
        {
            arr[i - 1][j + 1] = arr[i][j] + 1;
            q.push(i - 1, j + 1);
        }
        if (north && west && !arr[i - 1][j - 1])
        {
            arr[i - 1][j - 1] = arr[i][j] + 1;
            q.push(i - 1, j - 1);
        }
        if (south && east && !arr[i + 1][j + 1])
        {
            arr[i + 1][j + 1] = arr[i][j] + 1;
            q.push(i + 1, j + 1);
        }
        if (south && west && !arr[i + 1][j - 1])
        {
            arr[i + 1][j - 1] = arr[i][j] + 1;
            q.push(i + 1, j - 1);
        }
        if (north && !arr[i - 1][j])
        {
            arr[i - 1][j] = arr[i][j] + 1;
            q.push(i - 1, j);
        }
        if (south && !arr[i + 1][j])
        {
            arr[i + 1][j] = arr[i][j] + 1;
            q.push(i + 1, j);
        }
        if (east && !arr[i][j + 1])
        {
            arr[i][j + 1] = arr[i][j] + 1;
            q.push(i, j + 1);
        }
        if (west && !arr[i][j - 1])
        {
            arr[i][j - 1] = arr[i][j] + 1;
            q.push(i, j - 1);
        }
    }
}

int main()
{
    srand (time(NULL));
    // vars
    int H, W, X, Y, impass, log, check=1;
    char choice;
    //input width and height
    cout << "Welcome to CSE240 WaveFront Pather." <<endl <<endl;
    cout << "Enter the width (at least 10): ";
    cin >> W;
    cout << "Enter the height (at least 10): ";
    cin >> H;
    // dynamically initialize array
    int** arr = (int**)malloc(H * sizeof(int*));
    for (int i = 0; i < H; i++)
        arr[i] = (int*)malloc(W * sizeof(int));

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            arr[i][j] = 0;
        }
    }

    while(true) //asks user for the percent of terrain
    {
        cout << "Enter the percent of impassible terrain (0 - 100): ";
        cin >> impass;
        if(impass > 35)
        {
            cout << "Having a value greater than 35% might create poor results, do you with to continue? (y/n):";
            cin >> choice;
            if(choice == 'y')
                break;
        }
        else break;
    }


    log = (impass * H * W)/100; //sets log value.


    int i = 0;
    while(i<log) //loops while log in greater than i.
    {
        if(arr[rand()%H][rand()%W] != -1)
        {
            arr[rand()%H][rand()%W] = -1;
            i++;
        }
    }

    while(check!=0) //loops while check is non zero.
    {

        cout << "Please enter the Goal Position X: ";
        cin >> X;
        cout << "Please enter the Goal Position Y: ";
        cin >> Y;

        while(X > H || X > W || Y>H || Y>W)
        {
                    cout<<"Please enter a value that is in range of the grid."<<endl;
                    cout << "Please enter the Goal Position X: ";
                    cin >> X;
                    cout << "Please enter the Goal Position Y: ";
                    cin >> Y;
        }

        if(arr[Y][X]!=-1)
        {
            arr[Y][X] = 1;
            check = 0;
        }
        else
            cout << "Sorry, that position is inside an obstacle" << endl;;
    }


    Moore(arr, W, H, X, Y);

    PrintEnvironment(arr, W, H); //prints the grid

    char** parr = (char**)malloc(H * sizeof(char*));
    for (int i = 0; i < H; i++)
        parr[i] = (char*)malloc(W * sizeof(char));

    int sX, sY;
    check = 1;
    while(check!=0) //loops while check is not 0
    {
        cout << "Please enter the Start Position X: ";
        cin >> sX;
        cout << "Please enter the Start Position Y: ";
        cin >> sY;
        if(arr[sY][sX]!=-1)
        {
            parr[sY][sX] = '@';
            check = 0;
        }
        else
            cout << "Sorry, that position is inside an obstacle" << endl;;
    }

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if(arr[i][j] == -1)
                parr[i][j] = '#';
            else if(arr[i][j] == 1)
                parr[i][j] = '$';
            else
                parr[i][j] = ' ';
        }
    }
    parr[sY][sX] = '@';

    greed(arr, W, H, sX, sY, parr);

    CPrintEnvironment(parr, W, H);

    myfile.close();
    
    return 0;
}
