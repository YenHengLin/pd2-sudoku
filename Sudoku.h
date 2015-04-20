#include<iostream>
class Sudoku
{
public:
   void GiveQuestion();
   void ReadIn();
   void Solve();
   void zerocheck();
   void check_row();
   void check_column();
   void check_block();
   void initiall();
   void initiall_m();
   static const int sudokusize=12;
   static const int member=10;
   static const int totall=12;
   static const int blocksize=16;
private:
   int SudokuCompare[sudokusize][sudokusize];

    int calculateorigin;
    int calculatecompare;
    int row[totall][member];
    int column[totall][member];
    int block[blocksize][member];
    int fix[totall][totall];
    int number[totall][totall][member];
    int match[totall][totall];



};

