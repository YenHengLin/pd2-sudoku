#include<iostream>
class Sudoku
{
public:
   void GiveQuestion();
   void ReadIn();
   void Solve();
   static const int sudokusize=12;
private:
   int SudokuCompare[sudokusize][sudokusize];

};

