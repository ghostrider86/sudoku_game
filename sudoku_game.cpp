#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/**********************************************************************
 * Gets the file
 * ***********************************************************************/
void getFile(char fileN[])
{
   cout << "Where is your board located? ";
   cin >> fileN;
}

/**********************************************************************
 * reads fileN and uses the numbers in a 2D array
 * ***********************************************************************/
bool readSudoku(char fileN[], int board[][9])
{
   getFile(fileN);
   ifstream fin(fileN);
   if (fin.fail())
   {
      cout << "Error" << endl;
      return false;
   }
   else
   {
      for (int col = 0; col < 9; col++)
      {
         for (int row = 0; row < 9; row++)
         {
            fin >> board[col][row];
         }
      }
      fin.close();
      return true;
   }
}

/**********************************************************************
 * Display the sudoku board
 ***********************************************************************/
void displaySudoku(int board[][9])
{
   int row;
   int col;
   cout << "   A B C D E F G H I" << endl;
   for (col = 0; col < 9; col++)
   {
      cout << col + 1 << " ";
      for (row = 0; row < 9; row++)
      {
         if (row % 3 == 0 && row != 0)
         {
            if (board[col][row] != 0)
               cout << "|" << board[col][row];
            else
               cout << "| ";
         }
         else
         {
            if (board[col][row] != 0)
               cout << " " << board[col][row];
            else
               cout << "  ";
         }
      }
      if (col % 3 == 2 && col != 8)
         cout << endl << "   -----+-----+-----";
      cout << endl;
   }
   cout << endl; 
}

/**********************************************************************
 * Asks user for the specific row and column
 * ***********************************************************************/
void getCoordinate(int &row, int &col)
{
   char cord;
   cout << "What are the coordinates of the square: ";
   cin >> cord >> col;
   row = (cord) - 65;
   col--;
}

/**********************************************************************
 * Computes the value f the square
 ***********************************************************************/
void cValues(bool plausible[], int board[][9], int row, int col)
{
   int cRow;
   int cCol;

   for (int i = 0; i < 10; i++)
   {
      plausible[i] = true;
   }
   
   for (cRow = 0; cRow < 9; cRow++)
   {
      if (board[col][cRow] > 0)
      {
         plausible[board[col][cRow]] = false;
      }
   }
   
   for (cCol = 0; cCol < 9; cCol++)
   {
      if (board[cCol][row] > 0)
      {
         plausible[board[cCol][row]] = false;
      }
   }

   for (cRow = 0; cRow < 3; cRow++)
   {
      for (cCol = 0; cCol < 3; cCol++)
      {
         if (board[col / 3 * 3 + cCol][row / 3 * 3 + cRow] > 0)
         {
            plausible[board[col / 3 * 3 + cCol][row / 3 * 3 + cRow]] = false;
         }
      }
   }
}

/**********************************************************************
 * edits the prompted square
 ***********************************************************************/
void editSudoku(int row, int col, int board[][9])
{
   if (board[col][row] == 0)
   {
      int val;
      cout << "What is the value at \'" << (char)(row + 65); 
      cout << col + 1 << "\': ";
      cin >> val;
      bool plausible[10];
      cValues(plausible, board, row, col);
      if (!plausible[val])
      {
         cout << "ERROR: Value \'" << val << "\' in square \'";
         cout << (char)(row + 65) << col + 1 << "\' is invalid" << "\n";
      }
      else
      {
         board[col][row] = val;
      }
   }
   else
   {
      cout << "ERROR: Square '" << (char)(row + 65);
      cout << col + 1  << "\' is filled" << "\n"; 
   }
   cout << "\n";
}


/**********************************************************************
 * saves the board into a new file
 ***********************************************************************/
void newSudoku(char fileN2[], int board[][9])
{
   cout << "What file would you like to write your board to: ";
   cin >> fileN2;
   ofstream fout(fileN2);
   
   if (fout.fail())
      cout << "Error" << endl;
      
   for (int column = 0; column < 9; column++)
   {
      for (int rows = 0; rows < 9; rows++)
      {
         if (rows == 8)
            fout << board[column][rows] << endl;
         else
            fout << board[column][rows] << " ";
      }
   }
   cout << "Board written successfully" << endl;
}

/**********************************************************************
 * Shows possible value for the Sudoku board
 * ***********************************************************************/
void plausibleSudoku(char row, int col, int board[][9])
{
   bool plausible[10];
   cValues (plausible, board, row, col);
   cout << "The possible values for \'" << (char)(row + 65);
   cout << col + 1 << "\' are: ";
   bool one = true;
   
   for (int i = 1; i < 10; i++)
   {
      if (plausible[i])
      {
         if (!one)
         {
            cout << ", ";
         }
         else
         {
            one = false;
         }
         cout << i;
      }
   }
   cout << "\n";
}

/**********************************************************************
 * Shows options for sudoku menu
 * ***********************************************************************/
void displayO()
{
   cout << "Options:" << endl;
   cout << "   ?  " << "Show these instructions" << endl;
   cout << "   D  " << "Display the board" << endl;
   cout << "   E  " << "Edit one square" << endl;
   cout << "   S  " << "Show the possible values for a square" << endl;
   cout << "   Q  " << "Save and Quit" << endl;
   cout << endl;
}

/**********************************************************************
 * display options and calls the function
 ***********************************************************************/
void option(int board[][9])
{
   char selection;
   do
   {
      cout << "> ";
      cin >> selection;
      int row;
      int col;
      switch (selection)
      {
         case '?':
            displayO();
            cout << endl;
            break;
         case 'D':
            displaySudoku(board);
            break;
         case 'E':
            getCoordinate(row, col);
            editSudoku(row, col, board);
            break;
         case 'S':
            getCoordinate(row, col);
            plausibleSudoku(row,col,board);
            cout << "\n";
            break;
         case 'Q':
            char fileN2[256];
            newSudoku(fileN2, board);
            break;
         default:
            cout << "ERROR: Invalid command" << endl;
            break;
      }
   }
   while (toupper(selection) != 'Q');
}

/**********************************************************************
 * Main
 * Interact with a sudoku file, and lets the user display, and edit the
 * board and save it to a new file.
 *************************************************************************/
int main()
{
   char fileN[256];
   int board[9][9];
   if (readSudoku(fileN, board))
   {
      displayO();
      displaySudoku(board);
      option(board);
   }

   return 0;
}