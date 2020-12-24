#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

struct Stack
{
	string exp;
	char c;
	Stack* next;
} *top;

int Prior(char);
Stack* InS(Stack*, char);
Stack* OutS(Stack*, char&);
double Result(char*);

int Prior(char a)
{
	switch (a)
	{
	case '^': return 4;
	case '*': case '/': return 3;
	case '+': case '-': return 2;
	case '(': return 1;
	}
	return 0;
}

Stack* InS(Stack* p, char out)
{
	Stack* t = new Stack;
	t->c = out;
	t->next = p;
	return t;
}

Stack* OutS(Stack* p, char& in)
{
	Stack* t = p;
	in = p->c;
	p = p->next;
	delete t;
	return p;
}

Stack* InS_str(Stack* p, string out)
{
	Stack* t = new Stack;
	t->exp = out;
	t->next = p;
	return t;
}

Stack* OutS_str(Stack* p, string& in)
{
	Stack* t = p;
	in = p->exp;
	p = p->next;
	delete t;
	return p;
}

void reverse(char* str)
{
	char rev[81];
	int temp, i, j;
	for (i = 0, j = strlen(str) - 1; i < strlen(str), j >= 0; i++, j--)
	{
		if ((str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's' && str[i + 3] == '(') || (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n' && str[i + 3] == '('))
		{
			for (int q = i, k = 5; q < i + 6; q++, k--)
			{
				rev[j - k] = str[q];
			}
			i += 5;
			j -= 5;
			continue;
		}
		else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's')
		{
			for (int q = i, k = 2; q < i + 3; q++, k--)
			{
				rev[j - k] = str[q];
			}
			i += 2;
			j -= 2;
			continue;
		}
		else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n')
		{
			for (int q = i, k = 2; q < i + 3; q++, k--)
			{
				rev[j - k] = str[q];
			}
			i += 2;
			j -= 2;
			continue;
		}
		if (str[i] == ')')
		{
			rev[j] = '(';
			continue;
		}
		else if (str[i] == '(')
		{
			rev[j] = ')';
			continue;
		}
		rev[j] = str[i];

	}
	for (int i = 0; i < strlen(str); i++)
		str[i] = rev[i];
}

int del_border(char* str)
{
	int p, left = 0, right = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '(')
			left++;
		if (str[i] == ')')
			right++;
	}

	if (right != left)
		throw "\nincorrect input\n";

	return strlen(str) - left - right;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////



void main()
{
	Stack* t, * Op = NULL;
	char a;
	string b;
	char In[81],Out[81];
	int k = 0, l = 0, p;
	cout << "Enter expression: ";
	cin >> In;
	try
	{
		p = del_border(In);
	}
	catch (const char* exception)
	{
		cerr << exception;
		return;
	}



	reverse(In);
	while (In[k] != '\0')
	{
		//cos
		if (In[k] == 'c' && In[k + 1] == 'o' && In[k + 2] == 's')
		{
			Op = InS_str(Op, "cos");
			k += 4;
			Out[l] = In[k];
			l++;
			k += 2;
		}

		//sin
		if (In[k] == 's' && In[k + 1] == 'i' && In[k + 2] == 'n')
		{
			Op = InS_str(Op, "sin");
			k += 4;
			Out[l] = In[k];
			l++;
			k += 2;
		}


		if (In[k] >= 'a' && In[k] <= 'z' && In[k] != 'e' && (In[k] != 'p' && In[k + 1] != 'i'))
		{
			Out[l] = In[k];
			l++;
		}


		if (In[k] == '(')
			Op = InS(Op, In[k]);


		if (In[k] == ')')
		{
			while ((Op->c) != '(')
			{
				if (Op->exp == "cos")
				{
					Op = OutS_str(Op, b);
					if (!Op)
					{
						a = '\0';
						Out[l++] = a;
					}
					for (int i = l, q = 0; i < l + 3; i++, q++)
						Out[i] = b[q];
					l += 3;
				}
				else if(Op->exp=="sin")
				{ 
					Op = OutS_str(Op, b);
					if (!Op)
					{
						a = '\0';
						Out[l++] = a;
					}
					for (int i = l, q = 0; i < l + 3; i++, q++)
						Out[i] = b[q];
					l += 3;
				}
				else
				{
					Op = OutS(Op, a);
					if (!Op)
						a = '\0';
					Out[l++] = a;
				}
			}
			t = Op;
			Op = Op->next;
			delete t;
		}


		if (In[k] == '+' || In[k] == '-' || In[k] == '/' || In[k] == '*' || In[k] == '^' || (In[k] == 'c' && In[k + 1] == 'o' && In[k + 2] == 's') ||(In[k] == 's' && In[k + 1] == 'i' && In[k + 2] == 'n'))
		{
			if (Op)
			{
				if (Op->exp == "cos")
				{
					Op = OutS_str(Op, b);
					for (int i = l, q = 0; i < l + 3; i++, q++)
						Out[i] = b[q];
					l += 3;
				}
				if (Op)
				{
					if (Op->exp == "sin")
					{
						Op = OutS_str(Op, b);
						for (int i = l, q = 0; i < l + 3; i++, q++)
							Out[i] = b[q];
						l += 3;
					}
				}
			}
			while (Op != NULL && Prior(Op->c) >= Prior(In[k]))
			{
				Op = OutS(Op, a);
				Out[l++] = a;
			}
			Op = InS(Op, In[k]);
		}


		if (!In[k])
			break;
		k++;
	}


	while (Op != NULL)
	{
		if (Op->exp == "cos")
		{
			Op = OutS_str(Op, b);
			for (int i = l, q = 0; i < l + 3; i++, q++)
				Out[i] = b[q];
			l += 3;
		}
		else if (Op->exp == "sin")
		{
			Op = OutS_str(Op, b);
			for (int i = l, q = 0; i < l + 3; i++, q++)
				Out[i] = b[q];
			l += 3;
		}
		else
		{
			Op = OutS(Op, a);
			Out[l++] = a;
		}
	}
	Out[p] = '\0';
	reverse(Out);
	cout << "\nPrefix = " << Out << endl;




	k = 0, l = 0;
	reverse(In);
	while (In[k] != '\0')
	{
		//cos
		if (In[k] == 'c' && In[k + 1] == 'o' && In[k + 2] == 's')
		{
			Op = InS_str(Op, "cos");
			k += 4;
			Out[l] = In[k];
			l++;
			k += 2;
		}

		//sin
		if (In[k] == 's' && In[k + 1] == 'i' && In[k + 2] == 'n')
		{
			Op = InS_str(Op, "sin");
			k += 4;
			Out[l] = In[k];
			l++;
			k += 2;
		}


		if (In[k] >= 'a' && In[k] <= 'z' && In[k] != 'e' && (In[k] != 'p' && In[k + 1] != 'i'))
		{
			Out[l] = In[k];
			l++;
		}


		if (In[k] == '(')
			Op = InS(Op, In[k]);


		if (In[k] == ')')
		{
			while ((Op->c) != '(')
			{
				if (Op->exp == "cos")
				{
					Op = OutS_str(Op, b);
					if (!Op)
					{
						a = '\0';
						Out[l++] = a;
					}
					for (int i = l, q = 0; i < l + 3; i++, q++)
						Out[i] = b[q];
					l += 3;
				}
				else if (Op->exp == "sin")
				{
					Op = OutS_str(Op, b);
					if (!Op)
					{
						a = '\0';
						Out[l++] = a;
					}
					for (int i = l, q = 0; i < l + 3; i++, q++)
						Out[i] = b[q];
					l += 3;
				}
				else
				{
					Op = OutS(Op, a);
					if (!Op)
						a = '\0';
					Out[l++] = a;
				}
			}
			t = Op;
			Op = Op->next;
			delete t;
		}


		if (In[k] == '+' || In[k] == '-' || In[k] == '/' || In[k] == '*' || In[k] == '^' || (In[k] == 'c' && In[k + 1] == 'o' && In[k + 2] == 's') || (In[k] == 's' && In[k + 1] == 'i' && In[k + 2] == 'n'))
		{
			if (Op)
			{
				if (Op->exp == "cos")
				{
					Op = OutS_str(Op, b);
					for (int i = l, q = 0; i < l + 3; i++, q++)
						Out[i] = b[q];
					l += 3;
				}
				if (Op)
				{
					if (Op->exp == "sin")
					{
						Op = OutS_str(Op, b);
						for (int i = l, q = 0; i < l + 3; i++, q++)
							Out[i] = b[q];
						l += 3;
					}
				}
			}
			while (Op != NULL && Prior(Op->c) >= Prior(In[k]))
			{
				Op = OutS(Op, a);
				Out[l++] = a;
			}
			Op = InS(Op, In[k]);
		}


		if (!In[k])
			break;
		k++;
	}


	while (Op != NULL)
	{
		if (Op->exp == "cos")
		{
			Op = OutS_str(Op, b);
			for (int i = l, q = 0; i < l + 3; i++, q++)
				Out[i] = b[q];
			l += 3;
		}
		else if (Op->exp == "sin")
		{
			Op = OutS_str(Op, b);
			for (int i = l, q = 0; i < l + 3; i++, q++)
				Out[i] = b[q];
			l += 3;
		}
		else
		{
			Op = OutS(Op, a);
			Out[l++] = a;
		}
	}
	Out[p] = '\0';
	cout << "\nResult = " << fixed << setprecision(2) << Result(Out) << endl;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////



double Result(char* str)
{
	int i;
	char ss, ss1, ss2, ssR = 'z' + 1;
	double op1, op2, res = 0, mas[200];
	cout << "Input data\n";
	for (i = 0; str[i] != '\0'; ++i)
	{
		ss = str[i];
		if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's')
		{
			i += 2;
			continue;
		}
		if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n')
		{
			i += 2;
			continue;
		}
		if (ss >= 'a' && ss <= 'z')
		{
			cout << ss << " = ";
			cin >> mas[int(ss)];
		}

	}
	for (i = 0; str[i] != '\0'; ++i)
	{
		ss = str[i];
		if (!(ss == '+' || ss == '*' || ss == '-' || ss == '/' || ss == '^') && !(str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') && !(str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n'))
			top = InS(top, ss);
		else
		{
			if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's')
			{
				top = OutS(top, ss2);
				op2 = mas[int(ss2)];
				res = cos(op2);
				i += 2;
			}
			else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n')
			{
				top = OutS(top, ss2);
				op2 = mas[int(ss2)];
				res = sin(op2);
				i += 2;
			}
			else
			{
				top = OutS(top, ss2);
				top = OutS(top, ss1);
				op2 = mas[int(ss2)];
				op1 = mas[int(ss1)];
				switch (ss)
				{
				case'+':
					res = op1 + op2;
					break;
				case'-':
					res = op1 - op2;
					break;
				case'/':
					res = op1 / op2;
					break;
				case'*':
					res = op1 * op2;
					break;
				case'^':
					res = pow(op1, op2);
				}
			}
			mas[int(ssR)] = res;
			top = InS(top, ssR);
			ssR++;
		}
	}
	return res;
}