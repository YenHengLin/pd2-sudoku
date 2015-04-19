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

            SudokuMember[i][j]=0;

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
            cin>>SudokuCompare[i][j];
        }
    }


}
void Sudoku::initiall()
{
    int i,j,k;
    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            for(k=0;k<member;k++)
            {
                number[i][j][k]=0;
            }
        }
    }
}
void Sudoku::zerocheck()
{
    int i,j;
    int totall;
    calculateorigin=0;
    totall=12;
    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            fix[i][j]=0;
        }
    }
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

}
void Sudoku::check_row()
{
    int i,j,element;
    for(i=0;i<totall;i++)
    {
        for(j=0;j<member;j++)
        {
            row[i][j]=0;
        }
    }
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
}
void Sudoku::check_column()
{
    int i,j,element;
    for(i=0;i<totall;i++)
    {
        for(j=0;j<member;j++)
        {
            column[i][j]=0;
        }
    }
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
}
void Sudoku::check_block()
{
    int i,j,k,z,blockplace,element;
    for(i=0;i<blocksize;i++)
    {
        for(j=0;j<member;j++)
        {
            block[i][j]=0;
        }
    }
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
    //將一格要totall有的元素帶入
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
}
void Sudoku::Solve()
{


    int i,j,change,element;
    change=0;
    calculateorigin=0;
    calculatecompare=0;

    int SudokuOrigin[12][12]={
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
    {5,6,9,-1,-1,-1,3,0,0,0,0,0},
};

    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            SudokuCompare[i][j]=SudokuOrigin[i][j];
        }
    }
    initiall();
    zerocheck();
    cout<<calculateorigin<<endl;
    check_row();
    check_column();
    check_block();

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
    cout<<calculatecompare<<endl;
if(calculateorigin>calculatecompare)
{
    change=0;
}
else if(calculateorigin==calculatecompare)
{
    change=1;

}
else if(calculateorigin<calculatecompare)
{
    change=2;
    cout<<change<<endl;
}
 cout<<change<<endl;
if(change==1||change==2)
{


        for(i=0;i<totall;i++)
        {
            for(j=0;j<totall;j++)
            {
                for(element=1;element<10;element++)
                {
                    if( (number[i][j][element]==3)&&fix[i][j]==1 )
                    {
                        SudokuCompare[i][j]=element;
                        initiall();
                        zerocheck();
                        check_row();
                        check_column();
                        check_block();
                    if(calculateorigin==0)
                    {
                        break;
                    }

                    }
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

