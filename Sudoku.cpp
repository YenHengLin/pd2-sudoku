#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include"Sudoku.h"
using namespace std;
//#include<>
void Sudoku::GiveQuestion()
{
    srand(time(0));
    int i;
    int j;
    int SubstitudeA;
    int SubstitudeB;
    const int maxsize=12;
    int SudokuOrigin[maxsize][maxsize]={
    {4,2,6,8,7,3,9,5,1,-1,-1,-1},
    {8,7,3,9,5,1,6,2,4,-1,-1,-1},
    {9,5,1,6,2,4,8,7,3,-1,-1,-1},
    {-1,-1,-1,1,3,2,4,8,7,9,5,6},
    {-1,-1,-1,7,8,5,1,9,6,4,2,3},
    {-1,-1,-1,4,9,6,2,3,5,8,7,1},
    {1,3,7,2,4,8,-1,-1,-1,6,9,5},
    {2,8,4,5,6,9,-1,-1,-1,1,3,7},
    {6,9,5,3,1,7,-1,-1,-1,2,8,4},
    {3,1,2,-1,-1,-1,7,4,8,5,6,9},
    {7,4,8,-1,-1,-1,5,6,9,3,1,2},
    {5,6,9,-1,-1,-1,3,1,2,7,4,8},
};
    int SudokuMember[maxsize][maxsize];
    for(i=0;i<maxsize;i++)
    {
        for(j=0;j<maxsize;j++)
        {
            SudokuMember[i][j]=0;
        }
    }
    SubstitudeA=1+rand()%9;
    while(1)
    {
        SubstitudeB=1+rand()%9;
        if(SubstitudeA!=SubstitudeB)
        {
            break;
        }
    }
    for(i=0;i<maxsize;i++)
    {
        for(j=0;j<maxsize;j++)
        {
            SudokuMember[i][j]=SudokuOrigin[i][j];
            if(SudokuOrigin[i][j]==SubstitudeA)
            {
                SudokuMember[i][j]=SubstitudeB;
            }
             if(SudokuOrigin[i][j]==SubstitudeB)
            {
                SudokuMember[i][j]=SubstitudeA;
            }
        }
    }


    SudokuMember[11][11]=0;
    for(i=0;i<maxsize;i++)
    {
        for(j=0;j<maxsize;j++)
        {
            cout<<setw(3)<<SudokuMember[i][j];
        }
        cout<<endl;
    }


}
void Sudoku::ReadIn()
{
    int i,j;
    for(i=0;i<sudokusize;i++)
    {
        for(j=0;j<sudokusize;j++)
        {
            SudokuCompare[i][j];
        }
    }

    for(i=0;i<sudokusize;i++)
    {
        for(j=0;j<sudokusize;j++)
        {
            cin>>SudokuCompare[i][j];
        }
    }


}

void Sudoku::Solve()
{
    int i,j,k,z,blockplace,element;
    const int member=10;
    const int totall=12;
    const int blocksize=16;
    int calculateorigin=0;
    int calculatecompare=0;
    int row[totall][member]={0};
    int column[totall][member]={0};
    int block[blocksize][member]={0};
    int fix[totall][totall]={0};
    int number[totall][totall][member]={0};
    //先求出哪一個數字為0
    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            if(SudokuCompare[i][j]==0)
            {
                fix[i][j]++;
                calculateorigin++;
            }
        }
    }
    //求出橫列的值
    for(i=0;i<totall;i++)
    {
       for(element=1;element<10;element++)
       {
           for(j=0;j<totall;j++)
           {
               if(element==SudokuCompare[i][j])
               {
                   row[i][element]++;
               }

           }
       }
    }
    //再帶入求出每一列有可能的元素
    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            for(element=1;element<10;element++)
            if(fix[i][j]==1&&row[i][element]==0)
            {
                number[i][j][element]++;
            }
        }
    }
    //求出每一行的可能值
    for(i=0;i<totall;i++)
    {
       for(element=1;element<10;element++)
       {
           for(j=0;j<totall;j++)
           {
               if(element==SudokuCompare[j][i])
               {
                   column[i][element]++;
               }

           }
       }
    }
    //再帶入求出每一行有可能的元素
    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            for(element=1;element<10;element++)
            if(fix[j][i]==1&&column[i][element]==0)
            {
                number[j][i][element]++;
            }
        }
    }
    //求出一格要有的元素
    for(blockplace=0;blockplace<16;blockplace++)
    {
        for(element=1;element<10;element++)
        {
            for(i=0;i<totall;i++)
            {
                for(j=0;j<totall;j++)
                {
                    k=i/3;
                    z=j/3;
                    if( ( (k*4+z) ==blockplace)&&(element==SudokuCompare[i][j]) )
                    {
                        block[blockplace][element]++;
                    }
                }
            }
        }
    }
    //將一格要有的元素帶入
    for(blockplace=0;blockplace<16;blockplace++)
    {
        for(element=1;element<10;element++)
        {
            for(i=0;i<totall;i++)
            {
                for(j=0;j<totall;j++)
                {
                    k=i/3;
                    z=j/3;
                    if( ( (k*4+z) ==blockplace)&&(block[blockplace][element])==0 )
                    {
                       number[i][j][element]++;
                    }
                }
            }
        }
    }
    //求出一組解
    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            for(element=1;element<10;element++)
            {
                if(number[i][j][element]==3)
                {
                    calculatecompare++;
                }

            }
        }
    }
    if(calculatecompare<calculateorigin)
    cout<<"0";
    else if(calculatecompare==calculatecompare)
    {
        cout<<"1"<<endl;
        for(i=0;i<totall;i++)
        {
            for(j=0;j<totall;j++)
            {
                for(element=1;element<10;element++)
                {
                    if(SudokuCompare[i][j]==0&&number[i][j][element]==3)
                    {
                        SudokuCompare[i][j]=element;
                    }
                }
            }
        }
        for(i=0;i<totall;i++)
        {
            for(j=0;j<totall;j++)
            {
                cout<<setw(3)<<SudokuCompare[i][j];
            }
            cout<<endl;
        }
    }
    else if(calculatecompare>calculateorigin)
    {
        cout<<"2"<<endl;

        for(i=0;i<totall;i++)
        {
            for(j=0;j<totall;j++)
            {
                for(element=1;element<10;element++)
                {
                    if(SudokuCompare[i][j]==0&&number[i][j][element]==3)
                    {
                        SudokuCompare[i][j]=element;
                    }
                }
            }
        }
        for(i=0;i<totall;i++)
        {
            for(j=0;j<totall;j++)
            {
                cout<<setw(3)<<SudokuCompare[i][j];
            }
            cout<<endl;
        }

    }
}

