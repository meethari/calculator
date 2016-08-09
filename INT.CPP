#include <math.h>
#include <iostream.h>
#include <fstream.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>
#include <stdlib.h>

struct entry {
	char operand[1000], operation[40], result[1000];
};

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

void integrate_def()
{

	clrscr();
	cout<<"Enter lower and upper limit\n";
	double upper, lower;
	cin>>lower>>upper;
	clrscr();
	char grand[1000] = "";
	double result = 0;
	char ch;
	int coeff, cofactor, argcount = 0;

	do
	{
		clrscr();
		gotoxy(40 - strlen(grand)/2, 2);
		cout<<grand<<endl;

		cout<<"Make your choice:\n\n1.x\n2.sin x\n3.cos x\n4.tan x\n5.e^x\nC.calculate\n\n";
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
			cout<<"\nEnter the coefficient: ";
			do {
			cin>>coeff;
			} while (coeff==0);

			if(ch == '1' | ch == '5')
				cout<<"\nEnter the exponent: ";
			else
				cout<<"\nEnter x's cofactor: ";

			do {
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

	cout<<endl<<"Result: "<<result;
	
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
	
	clrscr();
	char grand[1000] = "";
	char result[1000] = "";
	char ch;
	int coeff, cofactor, argcount = 0;
	
	do 
	{
		clrscr();
		gotoxy(40 - strlen(grand)/2, 2);
		cout<<grand<<endl;
		
		cout<<"Make your choice:\n\n1.x\n2.sin x\n3.cos x\n4.tan x\n5.e^x\nC.calculate\n\n";
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
			cout<<"\nEnter the coefficient: ";
			do {
			cin>>coeff;
			} while (coeff==0);
			
			if(ch == '1' | ch == '5')
				cout<<"\nEnter the exponent: ";
			else
				cout<<"\nEnter x's cofactor: ";
				
			do {
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

	cout<<endl<<"Result: "<<result;
	
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
	clrscr();
	fstream x("result.dat", ios::binary|ios::in);
	entry r;
	
	cout<<"History\n\n";
	while(x.read((char*)&r, sizeof(r)))
	{
		cout<<r.operation<<endl<<r.operand<<endl<<r.result<<"\n\n";
	}
	
	x.close();
	getch();
	
}

void renderScreen(char title[] = "\0", char info[] = "\0")
{
	clrscr();
	box();
	gotoxy((int)(40 - strlen(title)/2), 3);
	puts(title);
	gotoxy((int)(40 - strlen(info)/2), 22);
	puts(info);

}

void main()
{
	char list[6][100] = {"Definite Integration", "Indefinite Integration", "Differentiation", "Matrix Operations", "History", "Quit"};
	char ch;
	int x_offset = 10, y_offset = 10;
	
	do {
	renderScreen("Project MODI - Matrix Operations, Differentiation and Integration","By Hariharan S, Sarvesh Deepak Menon and Hith M Jain");
	
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
		case '5':
			history();
			break;
		
	}
	
	} while (ch != '6');
}