#include<iostream.h>
#include<math.h>
#include<conio.h>

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
	clrscr();
	int a[10][10], c[10][10], m = 0;
	cout<<"Enter size of square matrix\n";
	while (m <= 0)
		cin>>m;
	cout<<"\nEnter the matrix\n";
	for(int i=0;i<m;i++)
	{
		cout<<"\nRow "<<i+1<<endl;
		for(int j=0;j<m;j++)
			cin>>a[i][j];
	}

	int n=0;
	cout<<"\nSelect Operation \n1.Determinant \n2.Inverse \n3.Transpose \n4.Square \n5.Trace \n6.Multiplication \n7.Adjoint"<<endl;
	while (!(n >= 1 && n <= 7))
		cin>>n;
	
	clrscr();
	switch (n)
	{
		case 1:
			cout<<"\n Determinant = "<<det(a, m);
			break;
		
		case 2:
			inv(a, m);
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
		
		case 7:
			adj(a, m);
			break;
	}
	getch();
}

void main()
{
	matrix_ops();
}