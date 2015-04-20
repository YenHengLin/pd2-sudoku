#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include"Sudoku.h"
using namespace std;
void Sudoku::GiveQuestion()
{
    srand(time(0));
    int i;
    int j;
    int SubstitudeA;
    int SubstitudeB;
    const int maxsize=12;
    int SudokuOrigin[maxsize][maxsize]={
    {4,2,6,8,7,0,0,0,1,-1,-1,-1},
    {8,7,3,9,5,1,6,0,0,-1,-1,-1},
    {9,5,1,0,2,0,8,7,0,-1,-1,-1},
    {-1,-1,-1,1,3,2,0,8,7,9,0,6},
    {-1,-1,-1,0,0,5,1,9,0,4,0,3},
    {-1,-1,-1,4,9,0,0,3,5,8,7,1},
    {1,0,0,2,4,0,-1,-1,-1,6,9,5},
    {2,8,4,5,0,0,-1,-1,-1,0,0,7},
    {0,0,5,3,1,7,-1,-1,-1,0,0,4},
    {0,1,0,-1,-1,-1,7,0,0,5,6,9},
    {0,4,8,-1,-1,-1,0,6,9,3,1,2},
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
        for(i=0;i<totall;i++)
        {
            for(j=0;j<totall;j++)
            {
                for(element=1;element<10;element++)
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
                    if( ( (k*4+z) ==blockplace)&&(block[blockplace][element]==0) )
                    {
                       number[i][j][element]++;
                    }
                }
            }
        }
    }
}
void Sudoku::initiall_m()
{
    int i,j;
    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            match[i][j]=0;

        }
    }
}
void Sudoku::Solve()
{


    int i,j,element,z;
    z=0;
    calculateorigin=0;
    calculatecompare=0;
    while(1)
    {
        zerocheck();
        initiall();
        check_row();
        check_column();
        check_block();
        initiall_m();
    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            for(element=1;element<10;element++)
            {
                if(number[i][j][element]==3)
                {
                    match[i][j]++;
                }
            }
        }
    }
    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            for(element=1;element<10;element++)
            {
                if( (match[i][j]==1)&&(number[i][j][element]==3)&&fix[i][j]==1 )
                {
                    SudokuCompare[i][j]=element;
                }
                    
            }
        }

    }


    if(calculateorigin==0)
    {
        cout<<"1"<<endl;
        break;
    }

    if(z!=0&&calculateorigin>=calculatecompare)
    {
        break;
    }
    z++;
    calculatecompare=calculateorigin;
    }

    zerocheck();
    initiall();
    check_row();
    check_column();
    check_block();
    initiall_m();
    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            for(element=1;element<10;element++)
            {
                if(number[i][j][element]==3)
                {
                    match[i][j]++;
                }
            }
        }
    }
    for(i=0;i<totall;i++)
    {
        for(j=0;j<totall;j++)
        {
            if(fix[i][j]==1&&(match[i][j]>1))
            {
                z=1;
                break;
            }
            else if(fix[i][j]==1&&(match[i][j]==0))
            {
                z=0;
                break;
            }
        }
    }
    if(z==0)
    {
        cout<<0<<endl;
    }
    else if(z==1)
    {
        cout<<"2"<<endl;
    }
    if(z==1)
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
                        check_row();
                        check_column();
                        check_block();
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




       if(calculateorigin==0)
       {
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

