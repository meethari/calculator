#include<iostream.h>
#include<math.h>
#include<conio.h>

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

	int res = 0, sign, j[10][10];

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

		res += a[0][i] * sign * det (j, m-1);
	}

	return res;
}

void adj (int a[10][10], int m)
{
	

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
	clrscr();
	int a[10][10], c[10][10], m;
	cout<<"Enter size of square matrix\n";
	cin>>m;
	cout<<"\nEnter the matrix\n";
	for(int i=0;i<m;i++)
	{
		cout<<"\nRow "<<i+1<<endl;
		for(int j=0;j<m;j++)
			cin>>a[i][j];
	}

	int n=0;
	cout<<"Select Operation \n1.Determinant \n2.Inverse \n3.Transpose \n4.Square \n5.Trace \n6.Multiplication"<<endl;
	while (!(n >= 1 && n <= 6))
		cin>>n;
	
	clrscr();
	switch (n)
	{
		case 1:
			cout<<"\n Determinant = "<<det(a, m);
			break;
		
		case 3:
			cout<<"\n Transpose ="<<endl;
			for(int i=0;i<m;i++)
			{
				for(int j=0;j<m;j++)
				{
					cout<<a[j][i]<<"\t";
				}
				cout<<endl;
			}
			break;

		case 4:
			cout<<"\n Square ="<<endl;
			mult(a,a,c,m);
			for(i=0;i<m;i++)
			{
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
			cout<<"\n Trace ="<<trace;
			break;

		case 6:
			int b[10][10];
			cout<<"\nEnter another matrix of dimension "<<m<<endl;
			for(i=0;i<m;i++)
			{
				cout<<"\nRow "<<i+1<<endl;
				for(int j=0;j<m;j++)
					cin>>b[i][j];
			}
			mult(a,b,c,m);
			cout<<"Product of matrices ="<<endl;
			for(i=0;i<m;i++)
			{
				for(int j=0;j<m;j++)
				cout<<c[i][j]<<"\t";
				cout<<endl;
			}
			break;
	}
	getch();
}

void main()
{
	matrix_ops();
}