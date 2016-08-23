#include <math.h>
#include <iostream.h>
#include <fstream.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>

// char op_list[7][100] = {"Make your choice:","1. x", "2. sin x", "3. cos x", "4. tan x", "5. e^x", "C. Calculate"};

void box(int pos_x = 0, int pos_y = 0, int rowspan = 77, int colspan = 24){
  char arr[8] = {'Ú', 'Ä', '¿', '³', 'Ù', 'Ä', 'À', '³'};
  rowspan+=2;
  colspan+=2;

  gotoxy(pos_x+1, pos_y+1);
  cout<<arr[0];
  
  for(int i=(pos_x+2);i<(pos_x + rowspan );i++)
  {
    gotoxy(i, pos_y + 1);
    cout<<arr[1];
  }
  
  gotoxy((pos_x + rowspan ), (pos_y +1));
  cout<<arr[2];

  for(int j=(pos_y + 2); j<(colspan + pos_y - 1);j++)
  {
    gotoxy((pos_x + rowspan),j);
    cout<<arr[3];
  }
  
  gotoxy((pos_x + rowspan  ), (pos_y + colspan - 1 ));
  cout<<arr[4];

  for(i=(pos_x + rowspan - 1);i>(pos_x + 1);i--)
  {
    gotoxy(i,(pos_y + colspan -1));
    cout<<arr[5];
  }
  
  gotoxy(pos_x+1 , pos_y + colspan -1);
  cout<<arr[6];

  for(j=(pos_y + colspan -2);j>(pos_y + 1);j--)
  {
    gotoxy(pos_x + 1,j);
    cout<<arr[7];
  }
}

void renderScreen(char title[] = "\0", char info[] = "\0")
{
	clrscr();
	box();
	gotoxy((int)(40 - strlen(title)/2), 3);
	puts(title);
	gotoxy((int)(40 - strlen(info)/2), 5);
	puts(info);

}

void splash_screen()
{
    int gdriver = DETECT, gmode, errorcode;
    int i,j;
    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;
    char flag='0';
    initgraph(&gdriver, &gmode, "C:/TC/BGI");
    settextstyle(3,0,9);
    textcolor(6);
    outtextxy(midx+80, midy+80,"SCIENTIFIC");
    outtextxy(midx+30,midy+160,"CALCULATOR");
    gotoxy(30,20);
    textcolor(9);
    cout<<"ENTER ANY KEY TO CONTINUE";
    rectangle(0,0,getmaxx(),getmaxy());
    rectangle(5,5,getmaxx()-5,getmaxy()-5);
    do
    {
        i++;
        setbkcolor(i%6);
        sleep(1);
        if(kbhit())
        {
            flag='1';
        }
    }while(flag!='1');
    getch();
    closegraph();
}
void credits()
{
    int gdriver = DETECT, gmode, errorcode;
    int i,j;
    int midx = 0;
    int midy = 0;
    char flag=0;
    initgraph(&gdriver, &gmode, "C:/TC/BGI");
    settextstyle(3,0,9);
    outtextxy(midx+60, midy+40,"PROJECT BY:");
    settextstyle(5,0,5);
    outtextxy(midx+80, midy+160,"HARIHARAN.S");
    outtextxy(midx+80, midy+210,"SARVESH MENON");
    outtextxy(midx+80, midy+260,"HITH JAIN");
    setbkcolor(6);
    rectangle(0,0,getmaxx(),getmaxy());
    rectangle(5,5,getmaxx()-5,getmaxy()-5);
    getch();
    closegraph();
}

struct entry {
    char operand[1000], operation[40], result[1000];
};

int HCF(int a, int b)
{
	int max = 1;
	a = abs(a);
	b = abs(b);
	for (int i = 2; i <= a && i<= b; i++)
		if(i > max && a % i == 0 && b % i == 0)
			max = i;
	return max;
}


void transpose (int a[10][10], int m)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            if (i < j)
            {
                int swap = a[i][j];
                a[i][j] = a[j][i];
                a[j][i] = swap;
            }
}

int det (int a[10][10], int m)
{
    if (m == 1)
        return a[0][0];
    
    int res = 0, sign;
    int j[10][10];
    
    for (int i = 0; i < m; i++)
    {
        sign = (i % 2 == 0)? 1 : -1;
        
        // making [0, i]'s submatrix for
        for (int row = 1; row < m; row++)
            for (int col = 0, real_col = 0; col < m; col++)
            {
                if (col == i)
                    continue;
                j[row - 1][real_col] = a[row][col];
                real_col++;
            }
        
        res += a[0][i] *( sign) * det (j, m-1);
    }
    
    return res;
}

void adj (int a[10][10], int m)
{
    int res[10][10], h[10][10], sign;
    
    // m == 1 workaround
    res[0][0] = a[0][0];
    
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
        {
            // to make submatrix for a[i][j]
            for (int row = 0, real_row = 0; row < m; row++)
            {
                if (row == i)
                    continue;
                for (int col = 0, real_col = 0; col < m; col++)
                {
                    if (col == j)
                        continue;
                    h[real_row][real_col] = a[row][col];
                    real_col++;
                }
                real_row++;
            }
            
            
            // lets put the cofactor in its place
            sign = ((i+j) % 2 == 0)? 1 : -1;
            res[i][j] = sign * det(h, m-1);
            
        }
    
    transpose(res, m);
    
    cout<<"Adjoint:\n\n";
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
            cout<<res[i][j]<<" ";
        cout<<endl;
    }
    
    
    
}

void inv (int a[10][10], int m)
{
    int res[10][10], h[10][10], sign;
    
    // unit matrix
    res[0][0] = a[0][0];
    
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
        {
            // to make submatrix for a[i][j]
            for (int row = 0, real_row = 0; row < m; row++)
            {
                if (row == i)
                    continue;
                for (int col = 0, real_col = 0; col < m; col++)
                {
                    if (col == j)
                        continue;
                    h[real_row][real_col] = a[row][col];
                    real_col++;
                }
                real_row++;
            }
            
            
            // lets put the cofactor in its place
            sign = ((i+j) % 2 == 0)? 1 : -1;
            res[i][j] = (sign) * det(h, m-1);
            
        }
    
    transpose(res, m);
    
    int hcf = 1;
    int d = det(a, m);
    
    
    if (d != 0)
    {
        cout<<"Inverse:\n\n";
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < m; j++)
            {
                hcf = HCF(res[i][j], d);
                if (hcf == d || res[i][j] == 0)
                    cout<<res[i][j]/hcf<<"\t";
                else
                {
                    if ( (res[i][j]/hcf) * (d/hcf) > 0)
                        cout<<abs(res[i][j]/hcf)<<"/"<<abs(d/hcf)<<"\t";
                    else if ( (d/hcf) < 0)
                        cout<<-res[i][j]/hcf<<"/"<<-d/hcf<<"\t";
                    else
                        cout<<res[i][j]/hcf<<"/"<<d/hcf<<"\t";
                }
            }
            cout<<endl;
        }
    }
    else
    {
        cout<<"Inverse doesn't exist.";
    }
    
    
}

void mult (int a[10][10],int b[10][10],int c[10][10],int m)
{
    for(int i=0;i<m;i++)
    {
        cout<<endl;
        for(int j=0;j<m;j++)
        {
            c[i][j]=0;
            for(int k=0;k<m;k++)
                c[i][j]+=a[i][k]*b[k][j];
        }
    }
}

void matrix_ops()
{
	// aligned	
	
    clrscr();
    renderScreen("Matrix Operations");
    gotoxy(0, 5);
    
    int a[10][10], c[10][10], m = 0;
    cout<<"³\tEnter size of square matrix\n";
    while (m <= 0)
    {
    	cout<<"³\t";
        cin>>m;
    }
    cout<<"\n³\tEnter the matrix\n";
    for(int i=0;i<m;i++)
    {
        cout<<"\n³\tRow "<<i+1<<endl;
        cout<<"³\t";
        for(int j=0;j<m;j++)
        {
            cin>>a[i][j];
        }
    }
    
    int n=0;
    clrscr();
    renderScreen("Matrix Operations");
    gotoxy(0, 5);
    
    // start here:
    // char list[8][] = {};
    cout<<"\n³\tSelect Operation \n³\t1.Determinant \n³\t2.Inverse \n³\t3.Transpose \n³\t4.Square \n³\t5.Trace \n³\t6.Multiplication \n³\t7.Adjoint"<<endl;
    while (!(n >= 1 && n <= 7))
    {
        cout<<"³\t";
        cin>>n;
    }
    
    clrscr();
    renderScreen("Matrix Operations");
    gotoxy(0, 5);
    
    switch (n)
    {
        case 1:
            cout<<"\n³\tDeterminant = "<<det(a, m);
            break;
            
        case 2:
            inv(a, m);
            break;
            
        case 3:
            cout<<"\n³\tTranspose = \n"<<endl;
            for(int i=0;i<m;i++)
            {
            	cout<<"³\t";
                for(int j=0;j<m;j++)
                {
                    cout<<a[j][i]<<"\t";
                }
                cout<<endl;
            }
            break;
            
        case 4:
            cout<<"\n³\tSquare ="<<endl;
            mult(a,a,c,m);
            for(i=0;i<m;i++)
            {
            	cout<<"³\t";
                for(int j=0;j<m;j++)
                {
                    cout<<c[i][j]<<"\t";
                }
                cout<<endl;
            }
            break;
            
        case 5:
            int trace=0;
            for(i=0;i<m;i++)
                for(int j=0;j<m;j++)
                    if(i==j)
                        trace+=a[i][j];
            cout<<"\n³\tTrace = "<<trace;
            break;
            
        case 6:
            int b[10][10];
            cout<<"\n³\tEnter another matrix of dimension "<<m<<endl;
            for(i=0;i<m;i++)
            {
                cout<<"\n³\tRow "<<i+1<<endl;
                cout<<"³\t";
                for(int j=0;j<m;j++)
                    cin>>b[i][j];
            }
            mult(a,b,c,m);
            cout<<"Product of matrices ="<<endl;
            for(i=0;i<m;i++)
            {
            	cout<<"³\t";
                for(int j=0;j<m;j++)
                    cout<<c[i][j]<<"\t";
                cout<<endl;
            }
            break;
            
        case 7:
            adj(a, m);
            break;
    }
    getch();
}

void integrate_def()
{
	// aligned
	char grand[1000] = "";
	double result = 0;
	char ch;
	int coeff, cofactor, argcount = 0;
	
	clrscr();
	renderScreen("Definite Integration");
	gotoxy(40 - strlen(grand)/2, 4);
	cout<<grand<<endl;
	
	cout<<"³\tEnter lower and upper limit\n";
	double upper, lower;
	cout<<"³\t";
	cin>>lower;
	cout<<"³\t";
	cin>>upper;
	clrscr();

	do
	{
		clrscr();
		renderScreen("Definite Integration", grand);
		gotoxy(40 - strlen(grand)/2, 4);
		
		cout<<"\n\n³\tMake your choice:\n³\t1. x\n³\t2. sin x\n³\t3. cos x\n³\t4. tan x\n³\t5. e^x\n³\tC. Calculate\n³\t";
		ch = getch();
		
		switch (ch)
		{
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case 'c':
			case 'C':
				break;

			default:
				continue;
		}

		if (!(ch == 'c' | ch == 'C'))
		{
			cout<<"\n³\tEnter the coefficient:\n";
			do {
			cout<<"³\t";
			cin>>coeff;
			} while (coeff==0);

			if(ch == '1' | ch == '5')
				cout<<"\n³\tEnter the exponent:\n";
			else
				cout<<"\n³\tEnter x's cofactor:\n";

			do {
			cout<<"³\t";
			cin>>cofactor;
			} while (cofactor==0);

			//lets ready both the integrand and the result

			int result_coeff = coeff/HCF(coeff, cofactor);
			int result_cofactor = cofactor/HCF(coeff, cofactor);

			if (result_coeff * result_cofactor > 0)
			{
				result_coeff = abs(result_coeff);
				result_cofactor = abs(result_cofactor);
			}
			else if (result_cofactor < 0)
			{
				result_cofactor *= -1;
				result_coeff *= -1;
			}

			if(argcount != 0)
			{
				strcat(grand, " + ");
			}

			char f[5], g[5];
			itoa(coeff, f, 10);
			itoa(cofactor, g, 10);

			if (coeff != 1)
				strcat(grand, f);
			
			
			
			switch(ch)
			{
				case '1':
				strcat(grand, "x^");
				strcat(grand, g);
				
				// to find the integrational result
				
				if (cofactor != -1)
				{
					result += (double)((double)coeff/(double)(cofactor + 1)) * (pow(upper, (cofactor + 1)) - pow(lower, (cofactor + 1)));
					//cout<<(double)(coeff/(cofactor + 1)) * (pow(upper, (cofactor + 1)) - pow(lower, (cofactor + 1)));
					//getch();
				}
				else
				{
					result += (double)(coeff) * (log(upper/lower));
					//cout<<(double)(coeff) * (log(upper/lower));
					//getch();
				}
				break;

				case '2':
				strcat(grand, " sin ");
				strcat(grand, g);
				strcat(grand, "x");

				result += (double)(coeff/cofactor) * - (cos(cofactor * upper) - cos(cofactor * lower));
				break;

				case '3':
				strcat(grand, " cos ");
				strcat(grand, g);
				strcat(grand, "x");

				result += (double)(coeff/cofactor) * (sin(cofactor * upper) - sin(cofactor * lower));
				break;

				case '4':
				strcat(grand, " tan ");
				strcat(grand, g);
				strcat(grand, "x");

				result += (double)(coeff/cofactor) * -(log(abs(cos(cofactor * upper))) - log(abs(cos(cofactor * lower))));
				break;

				case '5':
				strcat(grand, "e^");
				strcat(grand, g);
				strcat(grand, "x");

				result += (double)(coeff/cofactor) * (exp(cofactor*upper) - exp(cofactor*lower));

				break;

			}

		}

		argcount++;

		clrscr();
		gotoxy(40 - strlen(grand)/2, 2);
		cout<<grand<<endl;

	} while(!((ch == 'c' | ch == 'C') | argcount >= 5));
	
	renderScreen("Definite Integration");
	gotoxy(40 - strlen(grand)/2, 4);
	cout<<endl<<"³\tResult: "<<result;
	
	fstream x("result.dat", ios::binary|ios::app);
	entry r;
	strcpy(r.operand, grand);
	strcpy(r.operation, "Definite Integration");
	itoa((int)result, r.result, 10);
	x.write((char*)&r, sizeof(r));
	x.close();

	getch();
}

void integrate()
{
	// aligned
	clrscr();
	char grand[1000] = "";
	char result[1000] = "";
	char ch;
	int coeff, cofactor, argcount = 0;
	
	do 
	{
		clrscr();
		renderScreen("Indefinite Integration", grand);
		gotoxy(40 - strlen(grand)/2, 4);
		
		cout<<"\n\n³\tMake your choice:\n³\t1. x\n³\t2. sin x\n³\t3. cos x\n³\t4. tan x\n³\t5. e^x\n³\tC. Calculate\n³\t";
		ch = getch();
		cout<<endl;
		switch (ch)
		{
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case 'c':
			case 'C':
				break;
				
			default:
				continue;
		}
		
		if (!(ch == 'c' | ch == 'C'))
		{
			cout<<"\n³\tEnter the coefficient: ";
			do {
			cout<<"\n³\t";
			cin>>coeff;
			} while (coeff==0);
			
			if(ch == '1' | ch == '5')
				cout<<"\n³\tEnter the exponent: ";
			else
				cout<<"\n³\tEnter x's cofactor: ";
				
			do {
			cout<<"\n³\t";
			cin>>cofactor;
			} while (cofactor==0);

			//lets ready both the integrand and the result

			int result_coeff = coeff/HCF(coeff, cofactor);
			int result_cofactor = cofactor/HCF(coeff, cofactor);
			
			if (result_coeff * result_cofactor > 0)
			{
				result_coeff = abs(result_coeff);
				result_cofactor = abs(result_cofactor);
			}
			else if (result_cofactor < 0)
			{
				result_cofactor *= -1;
				result_coeff *= -1;
			}

			if(argcount != 0)
			{
				strcat(grand, " + ");
				strcat(result, " + ");
			}

			char f[5], g[5], res_f[5], res_g[5];
			itoa(coeff, f, 10);
			itoa(cofactor, g, 10);
			itoa(result_coeff, res_f, 10);
			itoa(result_cofactor, res_g, 10);

			if (coeff != 1)
				strcat(grand, f);
			
			if (ch != '1')
			{
				strcat(result, "(");
				strcat(result, res_f);
				strcat(result, "/");
			}
			
			switch(ch)
			{
				case '1':
				strcat(grand, "x^");
				strcat(grand, g);
				
				// to find the integrational result
				
				if (cofactor != -1)
				{
					cofactor++;
					itoa(cofactor, g, 10);
					
					result_coeff = coeff/HCF(coeff, cofactor);
					result_cofactor = cofactor/HCF(coeff, cofactor);
					
					if (result_coeff * result_cofactor > 0)
					{
						result_coeff = abs(result_coeff);
						result_cofactor = abs(result_cofactor);
					}
					else if (result_cofactor < 0)
					{
						result_cofactor *= -1;
						result_coeff *= -1;
					}
					
					itoa(result_coeff, res_f, 10);
					itoa(result_cofactor, res_g, 10);
				
					strcat(result, "(");
					strcat(result, res_f);
					strcat(result, "/");
					strcat(result, res_g);
					strcat(result, ") * x^");
					strcat(result, g);
				}
				else
				{
					strcat(result, "(");
					strcat(result, f);
					strcat(result, "/1) * ln x");
				}
				break;

				case '2':
				strcat(grand, " sin ");
				strcat(grand, g);
				strcat(grand, "x");

				strcat(result, res_g);
				strcat(result, ") * (-cos ");
				strcat(result, g);
				strcat(result, "x)");
				break;

				case '3':
				strcat(grand, " cos ");
				strcat(grand, g);
				strcat(grand, "x");

				strcat(result, res_g);
				strcat(result, ") * sin ");
				strcat(result, g);
				strcat(result, "x)");
				break;

				case '4':
				strcat(grand, " tan ");
				strcat(grand, g);
				strcat(grand, "x");

				strcat(result, res_g);
				strcat(result, ") * (ln sec ");
				strcat(result, g);
				strcat(result, "x)");
				break;

				case '5':
				strcat(grand, "e^");
				strcat(grand, g);
				strcat(grand, "x");

				strcat(result, res_g);
				strcat(result, ") * e^");
				strcat(result, g);
				strcat(result, "x");

				break;

			}

		}

		argcount++;

		clrscr();
		gotoxy(40 - strlen(grand)/2, 2);
		cout<<grand<<endl;

	} while(!((ch == 'c' | ch == 'C') | argcount >= 5));
	
	renderScreen("Indefinite Integration");
	cout<<endl<<"³\tResult: "<<result;
	
	fstream x("result.dat", ios::binary|ios::app);
	entry r;
	strcpy(r.operand, grand);
	strcpy(r.operation, "Indefinite Integration");
	strcpy(r.result, result);
	x.write((char*)&r, sizeof(r));
	x.close();

	getch();
}


void history()
{
	const int limit = 10;

	clrscr();
	fstream x("result.dat", ios::binary|ios::in);
	entry r;
	
	char a[] = "History";
	gotoxy(40 - (strlen(a)/2), 2);
	cout<<a<<endl<<endl;
	cout<<"ID\tType\tOperand\tResult\n";
	for(int i = 0; i < 79; i++)
		cout<<"-";
	cout<<endl<<endl;
	
	int count = 1;
	while(x.read((char*)&r, sizeof(r)) && count <= limit)
	{
		cout<<count<<"\t"<<r.operation<<"\t"<<r.operand<<"\t"<<r.result<<"\n\n";
		count++;
	}
	
	x.close();
	getch();
	
}


void differentiate()
{
	// Aligned
	
	char exp[1000] = "", res[1000] = "";
	int argcount = 0;
	char ch;
	
	do {
	
		clrscr();
		renderScreen("Differentiation", exp);
		gotoxy(40 - strlen(exp)/2, 4);
		cout<<"\n\n³\tMake your choice:\n³\t1. x\n³\t2. sin x\n³\t3. cos x\n³\t4. tan x\n³\t5. e^x\n³\tC. Calculate\n³\t";
				
		ch = getch();
		cout<<endl;
		int quit = 0;
		switch (ch)
		{
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
				break;
			case 'c':
			case 'C':
				quit = 1;
				break;
			default:
				continue;
		}
		
		if (quit == 1)
			break;
			
		int coeff = 0, exponent = 0;
		
		cout<<"³\tEnter coefficient\n";
		while (coeff == 0)
		{
			cout<<"³\t";
			cin>>coeff;
		}
		cout<<"\n³\tEnter exponent\n";
		while (exponent == 0)
		{
			cout<<"³\t";
			cin>>exponent;
		}

		if (argcount != 0)
		{
			strcat(exp, " + ");
			strcat(res, " + ");
		}

		char stra[5], strb[5], strc[5], strd[5];
		itoa(coeff, stra, 10);
		itoa(coeff*exponent, strb, 10);
		itoa(exponent, strc, 10);
		itoa(exponent - 1, strd, 10);

		if (coeff != 1)
			strcat(exp, stra);
		if (coeff * exponent != 1)
			strcat(res, strb);

		switch (ch)
		{
			case '1':
				strcat (exp, "x^");
				strcat (exp, strc);

				if (exponent - 1 != 0)
				{
					strcat (res, "x^");
					strcat (res, strd);
				}
				else
					strcat (res, strb);

				break;

			case '2':
				strcat (exp, "(sin x)^");
				strcat (exp, strc);

				strcat (res, "(cos x)");
				if (exponent - 1 != 0)
				{
					strcat (res, "(sin x)^");
					strcat (res, strd);
				}

				break;

			case '3':
				strcat (exp, "(cos x)^");
				strcat (exp, strc);

				strcat (res, "(-sin x)");
				if (exponent - 1 != 0)
				{
					strcat (res, "(cos x)^");
					strcat (res, strd);
				}

				break;

			case '4':
				strcat (exp, "(tan x)^");
				strcat (exp, strc);

				strcat (res, "(sec x) ^ 2");
				if (exponent - 1 != 0)
				{
					strcat (res, " * (tan x)^");
					strcat (res, strd);
				}

				break;

			case '5':
				strcat (exp, "e^");
				if(exponent != 1)
					strcat(exp, strc);
				strcat(exp, "x");

				strcat (res, "e^");
				if(exponent != 1)
					strcat(res, strc);
				strcat(res, "x");
		}

		clrscr();
		argcount++;

	} while (argcount <= 5);

	clrscr();
	renderScreen("Differentiation");
	cout<<"\n³\tResult: "<<res;

	fstream x("result.dat", ios::binary|ios::app);
	entry r;
	strcpy(r.operand, exp);
	strcpy(r.operation, "Differentiation");
	strcpy(r.result, res);
	x.write((char*)&r, sizeof(r));
	x.close();

	getch();
}


void main()
{
    clrscr();
    //splash_screen();
    clrscr();
	char list[6][100] = {"Definite Integration", "Indefinite Integration", "Differentiation", "Matrix Operations", "History", "Quit"};
	char ch;
	int x_offset = 10, y_offset = 10;
	
	do {
	renderScreen("Project MODI - Matrix Operations, Differentiation and Integration","Take your pick using the number keys");
	
	for(int i = 0; i < 6; i++)
	{
		gotoxy(40 - x_offset, y_offset + i);
		cout<<i+1<<". "<<list[i];
	}
	
	ch = getch();
	
	switch (ch)
	{
		case '1':
			integrate_def();
			break;
		case '2':
			integrate();
			break;
		case '3':
			differentiate();
			break;
        case '4':
            matrix_ops();
            break;
		case '5':
			history();
			break;
		
	}
	
	} while (ch != '6');
    
    clrscr();
    //credits();
}