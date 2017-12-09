// MatrixCalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "conio.h"
struct matrix
{
	float**values;
	int nr, nc;
	char name[30];
};
float Determinant(struct matrix* a);
struct matrix* creatematrix(int nr, int nc);
float reduce(struct matrix* a, int i)//to get a matrix less than the input and calc. its determenant by recursion
{
	float sum = 0;
	int r = 0, c;
	struct matrix* b;
	b = creatematrix(a->nr - 1, a->nc - 1);
	for (int j = 1; j<a->nr; j++)
	{
		c = 0;
		for (int y = 0; y<a->nc; y++)
		{
			if (y != i)//not to copy the marked column
				b->values[r][c] = a->values[j][y];
			else
				c--;
			c++;
		}
		r++;
	}
	sum = Determinant(b);
	return sum;
}
float Determinant(struct matrix* a)
{
	float sum = 0;
	if (a->nr == a->nc)
	{
		if (a->nr == 1)
			sum = a->values[0][0];
		else if (a->nr == 2)
			sum = a->values[0][0] * a->values[1][1] - a->values[1][0] * a->values[0][1];
		else//if the matrix is 3*3 or more
		{
			for (int i = 0; i<a->nc; i++)
			{
				if (i == 0 || i % 2 == 0)//if condition for sign rule
					sum += a->values[0][i] * reduce(a, i);
				else
					sum -= a->values[0][i] * reduce(a, i);
			}
		}
	}
	else
		if (a->nr != a->nc) { printf("error"); exit(0); }
	return sum;
}
int per(char c)
{
	if (c == '/')return 4;
	else if (c == '*')return 3;
	else if (c == '-')return 2;
	else if (c == '+')return 1;
	else if (c == ' ')return 0;
	else if (c == '(')return -1;
}
int isoperator(char c)
{
	if (c == '/' || c == '*' || c == '-' || c == '+')return 1;
	else return 0;
}
int abdalih(char c)
{
	if (c == '+' || c == '*')return 1;
	else if (c == '/' || c == '-')return 0;
}
int mabdalih(char c)
{
	if (c == '+')return 1;
	else return 0;
}
void checkmatrix(char*x, int*nr, int*nc)
{
	int i = 0;
	*nr = 0, *nc = 0;
	while (x[i] != '\0')
	{

		if (x[i] == ';')
			*nr = *nr + 1;
		else if (x[i] == ' '&&*nr == 0)
		{
			*nc = *nc + 1;
		}
		i++;
	}
	*nr = *nr + 1;
	*nc = *nc + 1;
}
int search(struct matrix* a[], char x[], int n)
{
	int i = 0;
	while (i<n)
	{
		if (strcmp(a[i]->name, x) == 0)break;
		i++;
	}
	if (i == n)return -1;
	else return i;
}
void parsing(char*p, char y[][20], int c, int* q)
{
	char z[20] = " ";
	int g, jj, k = 0, t = 1, flag = 0;
	for (g = 0; g<100; g++)
	{
		for (jj = 0; jj<20; jj++)
		{
			if (p[k] == '(')
			{
				if (k == 0 || isoperator(p[k - 1]))
				{
					z[t] = p[k];
					t++;
					g--;
				}
				else if (p[k - 1] == ')')
				{
					z[t] = '*';
					z[t + 1] = '(';
					t = t + 2;
				}
				else
				{
					y[g][jj] = '\0';
					z[t] = '*';
					z[t + 1] = '(';
					t = t + 2;
				}
				k++;
				break;
			}
			else if (p[k] == ')')
			{
				y[g][jj] = '\0';
				while (z[t - 1] != '(')
				{
					y[g + 1][0] = z[t - 1];
					y[g + 1][1] = '\0';
					z[t - 1] = '\0';
					t--;
					g++;
				}
				z[t - 1] = '\0';
				t--;
				k++;
			}
			else if (isalpha(p[k]) || isdigit(p[k]) || p[k] == '.')
			{
				y[g][jj] = p[k];
				k++;
			}
			else if (p[k] == '\0' || p[k] == ' ' || p[k] == ';' || p[k] == ']')
			{
				y[g][jj] = '\0';
				*q = k;
				while (z[t - 1] != ' ')
				{
					y[g + 1][0] = z[t - 1];
					y[g + 1][1] = '\0';
					t--;
					g++;
				}
				y[g + 1][0] = '\0';
				flag = 1;
				break;
			}
			else if (isoperator(p[k]))
			{
				y[g][jj] = '\0';
				if ((p[k] == '-'&&k == 0) || (p[k] == '-' && (p[k - 1] == '/' || p[k - 1] == '*')) || p[k - 1] == '(')
				{
					y[g][jj] = p[k];
					k++;
				}
				else if (per(z[t - 1])>per(p[k]))
				{
					while (per(p[k])<per(z[t - 1]))
					{
						y[g + 1][0] = z[t - 1];
						y[g + 1][1] = '\0';
						z[t - 1] = '\0';
						g++;
						t--;
					}
					z[t] = p[k];
					k++;
					t++;
					break;
				}
				else if ((mabdalih(p[k]) && c == 1) || (abdalih(p[k]) && c == 0))
				{
					z[t] = p[k];
					k++;
					t++;
					break;
				}
				else if ((!mabdalih(p[k]) && c == 1) || (!abdalih(p[k]) && c == 0))
				{
					if (per(z[t - 1])<per(p[k]))
					{
						z[t] = p[k];
						k++;
						t++;
						break;
					}
					else if (per(z[t - 1]) == per(p[k]))
					{
						y[g + 1][0] = z[t - 1];
						y[g + 1][1] = '\0';
						z[t - 1] = p[k];
						k++;
						g++;
						break;
					}
				}
			}
		}
		if (flag == 1)break;
	}
}
void calc(char* p, float*m, int*q)
{
	p++;
	char y[90][20];
	parsing(p, y, 0, q);
	float h[30];
	int i = 0, n = 0;
	while (y[i][0] != '\0')
	{
		if (isdigit(y[i][0]) || atof(y[i]))
		{
			h[n] = atof(y[i]);
			n++;
		}
		else if (y[i][0] == '*')
		{
			h[n - 2] = h[n - 2] * h[n - 1];
			h[n - 1] = '\0';
			n--;
		}
		else if (y[i][0] == '+')
		{
			h[n - 2] = h[n - 2] + h[n - 1];
			h[n - 1] = '\0';
			n--;
		}
		else if (y[i][0] == '-')
		{
			h[n - 2] = h[n - 2] - h[n - 1];
			h[n - 1] = '\0';
			n--;
		}
		else if (y[i][0] == '/')
		{
			h[n - 2] = h[n - 2] / h[n - 1];
			h[n - 1] = '\0';
			n--;
		}
		i++;
	}
	*m = h[0];
}
void calc2(char* p, float*m, int*q, struct matrix* snake[], int u)
{
	p++;
	int i = 0;
	char y[10];
	while (p[i] != ' '&&p[i] != ']'&&p[i] != ';')
	{
		y[i] = p[i];
		i++;
	}
	*q = i;
	y[i] = '\0';
	int v;
	v = search(snake, y, u);
	*m = Determinant(snake[v]);

}
struct matrix* creatematrix(int nr, int nc)
{
	int r;
	struct matrix* rm;
	rm = (struct matrix*)malloc(sizeof(struct matrix));
	rm->nr = nr;
	rm->nc = nc;
	rm->values = (float**)malloc(nr * sizeof(float*));
	for (r = 0; r<nr; r++)
		rm->values[r] = (float*)malloc(nc * sizeof(float));
	return rm;
}
struct matrix* getmatrix(char x[], int nc, int nr, struct matrix* snake[], int u)
{
	struct matrix* rm;
	rm = creatematrix(nr, nc);
	int i = 0, d = 0;
	char*p;
	p = x;
	while (p[i] != '=')
	{
		rm->name[i] = p[i];
		i++;
	}
	rm->name[i] = '\0';
	p += i + 1, i = 0;
	if (isalpha(p[1]))d = 1;
	for (int r = 0; r<nr; r++)
	{
		for (int c = 0; c<nc; c++)
		{
			if (d == 0)calc(p, &rm->values[r][c], &i);
			else if (d == 1)calc2(p, &rm->values[r][c], &i, snake, u);
			p = p + i + 1;
		}
	}
	return rm;
}
void printmatrix(struct matrix*pm)
{
	int r, c;
	printf("%s\n", pm->name);
	for (r = 0; r<pm->nr; r++)
	{
		for (c = 0; c<pm->nc; c++)
			printf("%f\t", pm->values[r][c]);
		printf("\n");
	}
}
struct matrix* copy(struct matrix* pm)
{
	struct matrix* rm;
	rm = creatematrix(pm->nr, pm->nc);
	for (int i = 0; i<pm->nr; i++)
	{
		for (int j = 0; j<pm->nc; j++)
		{
			rm->values[i][j] = pm->values[i][j];
		}
	}
	strcpy(rm->name, " ");
	return rm;
}
void destroymatrix(struct matrix* a)
{
	int nr;
	nr = a->nr;
	for (int r = 0; r<nr; r++)
		free(a->values[r]);
	free(a->values);
	free(a);

}
struct matrix* inverse(struct matrix * a)
{
	struct matrix* inverse;
	struct matrix* b;
	inverse = creatematrix(a->nr, 2 * a->nr);
	b = creatematrix(a->nr, a->nc);
	if (Determinant(a) == 0) { printf("matrix error\n"); exit(0); }
	else
	{
		int i, j, f = 0;
		float l;
		for (i = 0; i<a->nr; i++)//Ê÷⁄ «·„’›Ê›Â »ÃÊ«— „’›Ê›Â «·ÊÕœÂ
		{
			for (j = 0; j<2 * a->nc; j++)
			{
				if (j == i + a->nr)
				{
					inverse->values[i][j] = 1;
				}
				else if (j<a->nc)inverse->values[i][j] = a->values[i][j];
				else inverse->values[i][j] = 0;
			}
		}
		for (int r = 0; r<a->nr; r++)
		{
			if (inverse->values[r][r] == 0)//⁄‘«‰ «Ê· ⁄‰’— Â‰ﬁ”„ ⁄·ÌÂ
			{
				while (inverse->values[f][r] == 0)
					f++;
				for (int c = 0; c<2 * a->nc; c++)
					inverse->values[r][c] = inverse->values[f][c] + inverse->values[r][c];
			}
			if (inverse->values[r][r] != 1)//⁄‘«‰ ‰Œ·ÌÂ Ê«Õœ
			{
				l = inverse->values[r][r];
				for (int c = 0; c<2 * a->nc; c++)
					inverse->values[r][c] = inverse->values[r][c] / l;
			}
			for (int y = 0; y<a->nr; y++)//⁄‘«‰ ‰’›— «··Ì ›Êﬁ «·Ê«Õœ «Ê «··Ï  Õ Â 
			{
				if (y != r)
				{
					l = inverse->values[y][r];
					for (int c = 0; c<2 * a->nc; c++)
						inverse->values[y][c] = inverse->values[y][c] - (l * inverse->values[r][c]);
				}
			}
		}
		for (i = 0; i<a->nr; i++)
			for (j = 0; j<a->nc; j++)
				b->values[i][j] = inverse->values[i][j + a->nc];//to get inverse
	}
	destroymatrix(inverse);
	return b;
}
struct matrix* mullordiv(struct matrix*pm1, struct matrix*pm2)
{
	if (pm1->nc != pm2->nr) { printf("error"); exit(0); }
	int r, c, i;
	struct matrix* pm;
	pm = creatematrix(pm1->nr, pm2->nc);
	for (r = 0; r<pm->nr; r++)
	{
		for (c = 0; c<pm->nc; c++)
		{
			pm->values[r][c] = 0;
			for (i = 0; i<pm1->nc; i++)pm->values[r][c] += pm1->values[r][i] * pm2->values[i][c];
		}
	}
	return pm;
}
struct matrix* addorsub(struct matrix*pm1, struct matrix*pm2, int i)
{
	int r, c;
	struct matrix*rm;
	if (pm1->nc != pm2->nc || pm1->nr != pm2->nr) { printf("error"); exit(0); }
	rm = creatematrix(pm1->nr, pm1->nc);
	if (i == 1)
	{
		for (r = 0; r<rm->nr; r++)
		{
			for (c = 0; c<rm->nc; c++)
				rm->values[r][c] = pm1->values[r][c] + pm2->values[r][c];
		}
	}
	else if (i == -1)
	{
		for (r = 0; r<rm->nr; r++)
		{
			for (c = 0; c<rm->nc; c++)
				rm->values[r][c] = pm1->values[r][c] - pm2->values[r][c];
		}
	}
	return rm;
}
void calcator(struct matrix* snake[], char*p, int j)
{
	char y[90][20];
	int t = 0;
	int*q = &t;
	parsing(p, y, 1, q);
	int i = 0, k = 0;
	int v;
	while (y[i][0] != '\0')
	{
		k = 0;
		while (y[i][k] != '\0')
		{
			if (isalpha(y[i][k]))
			{
				v = search(snake, y[i], j);
				snake[j] = copy(snake[v]);
				j++;
			}
			else if (atof(y[i]))
			{
				snake[j] = creatematrix(1, 1);
				snake[j]->values[0][0] = atof(y[i]);
				strcpy(snake[j]->name, ".");
				j++;
			}
			else if (y[i][0] == '+' || y[i][0] == '-')
			{
				int d;
				if (y[i][0] == '+')d = 1;
				else d = -1;
				snake[j - 2] = addorsub(snake[j - 2], snake[j - 1], d);
				destroymatrix(snake[j - 1]);
				j--;
			}
			else if (y[i][0] == '*' || y[i][0] == '/')
			{
				if (strcmp(snake[j - 2]->name, ".") == 0 || strcmp(snake[j - 1]->name, ".") == 0)
				{
					if (y[i][0] == '/'&&strcmp(snake[j - 1]->name, ".") == 0)
					{
						for (int r = 0; r<snake[j - 2]->nr; r++)
							for (int c = 0; c<snake[j - 2]->nc; c++)
								snake[j - 2]->values[r][c] = snake[j - 2]->values[r][c] / snake[j - 1]->values[0][0];
					}
					else if (y[i][0] == '/'&&strcmp(snake[j - 2]->name, ".") == 0)
					{
						snake[j - 1] = inverse(snake[j - 1]);
						for (int r = 0; r<snake[j - 1]->nr; r++)
							for (int c = 0; c<snake[j - 1]->nc; c++)
								snake[j - 1]->values[r][c] = snake[j - 1]->values[r][c] * snake[j - 2]->values[0][0];
						snake[j - 2] = creatematrix(snake[j - 1]->nr, snake[j - 1]->nc);
						snake[j - 2] = copy(snake[j - 1]);
					}
					else if (y[i][0] == '*'&&strcmp(snake[j - 2]->name, ".") == 0)
					{
						for (int r = 0; r<snake[j - 1]->nr; r++)
							for (int c = 0; c<snake[j - 1]->nc; c++)
								snake[j - 1]->values[r][c] = snake[j - 1]->values[r][c] * snake[j - 2]->values[0][0];
						snake[j - 2] = creatematrix(snake[j - 1]->nr, snake[j - 1]->nc);
						snake[j - 2] = copy(snake[j - 1]);
					}
					else if (y[i][0] == '*'&&strcmp(snake[j - 1]->name, ".") == 0)
					{
						for (int r = 0; r<snake[j - 2]->nr; r++)
							for (int c = 0; c<snake[j - 2]->nc; c++)
								snake[j - 2]->values[r][c] = snake[j - 2]->values[r][c] * snake[j - 1]->values[0][0];
					}

				}
				else
				{
					if (y[i][0] == '/')snake[j - 1] = inverse(snake[j - 1]);
					snake[j - 2] = mullordiv(snake[j - 2], snake[j - 1]);
				}
				destroymatrix(snake[j - 1]);
				j--;
			}
			k++;
			break;
		}
		i++;
	}
}
void main()
{
	struct matrix* snake[1000];
	char x[2000], y[20];
	int nc = 0, nr = 0, flag = 0, j = 0, v;
	while (1)
	{
		printf(">");
		gets_s(x);
		for (int i = 0; i<20; i++)
		{
			if (x[i] == '=')
			{
				if (x[i + 1] == '[')
				{
					memcpy(y, x, sizeof(char)*i);
					y[i] = '\0';
					v = search(snake, y, j);
					checkmatrix(x, &nr, &nc);
					if (v == -1)
					{
						snake[j] = getmatrix(x, nc, nr, snake, j);
						j++;
					}
					else
					{
						destroymatrix(snake[v]);
						snake[v] = getmatrix(x, nc, nr, snake, j);
					}
					break;
				}
				else
				{
					char*p;
					p = x + i + 1;
					memcpy(y, x, sizeof(char)*i);
					y[i] = '\0';
					v = search(snake, y, j);
					if (v == -1)
					{

						calcator(snake, p, j);
						strcpy(snake[j]->name, y);
						j++;
					}
					else
					{
						calcator(snake, p, j);
						destroymatrix(snake[v]);
						snake[v] = creatematrix(snake[j]->nr, snake[j]->nc);
						snake[v] = copy(snake[j]);
						strcpy(snake[v]->name, y);
						destroymatrix(snake[j]);
					}
					break;
				}
			}
			else if (x[i] == '?')
			{
				int a = 0;
				char s[10];
				memcpy(s, x, sizeof(char)*i);
				s[i] = '\0';
				a = search(snake, s, j);
				if (a == -1)printf("not found matrix with name %s\n", s);
				else printmatrix(snake[a]);
				break;
			}
			else if (strcmp(x, "exit") == 0)
			{
				flag = 1;
				for (int i = 0; i<j; i++)
					destroymatrix(snake[i]);
				break;
			}
		}
		if (flag == 1)break;
	}
}
