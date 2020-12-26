#define _USE_MATH_DEFINES
#include "Prefix_Calculation.h"
#include <iostream>
#include <string>
#include <math.h>

//define constants pi and e
#define pi = M_PI;
#define e = M_E;

using namespace std;

//reverse expression
void reverse(LinkedList& expression_list)
{
	LinkedList temp_expression_list;
	string temp_value, temp_value2;
	for (int i = 0; i < expression_list.get_size(); i++)
	{
		if (expression_list.at(i) == "cos" || expression_list.at(i) == "sin" || expression_list.at(i) == "ctg" || expression_list.at(i) == "abs" || expression_list.at(i) == "log" || expression_list.at(i) == "ln" || expression_list.at(i) == "tg" || expression_list.at(i) == "sqrt")
		{
			temp_expression_list.push_front(expression_list.at(i));
			continue;
		}
		if (expression_list.at(i) == "(")
		{
			temp_expression_list.push_front(")");
			continue;
		}
		else if (expression_list.at(i) == ")")
		{
			temp_expression_list.push_front("(");
			continue;
		}
		temp_expression_list.push_front(expression_list.at(i));
	}
	if (temp_expression_list.at(temp_expression_list.get_size() - 1) == "-" && (atof(temp_expression_list.at(temp_expression_list.get_size() - 2).c_str()) || temp_expression_list.at(temp_expression_list.get_size() - 2) == "cos" || temp_expression_list.at(temp_expression_list.get_size() - 2) == "sin" || temp_expression_list.at(temp_expression_list.get_size() - 2) == "ctg" || temp_expression_list.at(temp_expression_list.get_size() - 2) == "abs" || temp_expression_list.at(temp_expression_list.get_size() - 2) == "log" || temp_expression_list.at(temp_expression_list.get_size() - 2) == "ln" || temp_expression_list.at(temp_expression_list.get_size() - 2) == "tg" || temp_expression_list.at(temp_expression_list.get_size() - 2) == "sqrt"))
	{
		temp_expression_list.pop_back();
		temp_expression_list.push_back("--");
	}
	for (int i = 0; i < temp_expression_list.get_size(); i++)
	{
		if (temp_expression_list.get_size() - i >= 3)
		{
			if (temp_expression_list.at(i + 1) == "-" && temp_expression_list.at(i + 2) == ")" && atof(temp_expression_list.at(i).c_str()))
			{
				temp_expression_list.remove(i + 1);
				temp_expression_list.insert("--", i + 1);
			}
		}
	}
	expression_list.clear();
	for (int i = 0; i < temp_expression_list.get_size(); i++)
		expression_list.push_back(temp_expression_list.at(i));
}

//change notaion to another
void change_notation(LinkedList& expression_list)
{
	LinkedList temp_expression_list, postfix_expression_list;

	for (int i = 0; i < expression_list.get_size(); i++)
	{
		if (atof(expression_list.at(i).c_str()))
		{
			postfix_expression_list.push_back(expression_list.at(i));
			continue;
		}
		if (expression_list.at(i) == "(")
		{
			temp_expression_list.push_front(expression_list.at(i));
			continue;
		}

		if (expression_list.at(i) == ")")
		{
			while (temp_expression_list.at(0) != "(")
			{
				postfix_expression_list.push_back(temp_expression_list.at(0));
				temp_expression_list.pop_front();
			}
			if (temp_expression_list.at(0) != "(" && temp_expression_list.at(0) != ")")
			{
				postfix_expression_list.push_back(temp_expression_list.at(0));
				temp_expression_list.pop_front();
			}
			temp_expression_list.pop_front();
		}

		if (!(atof(expression_list.at(i).c_str())) && !temp_expression_list.isEmpty() && expression_list.at(i) != ")" && expression_list.at(i) != "--")
		{
			temp_expression_list.push_front(expression_list.at(i));
			continue;
		}
		if (!(atof(expression_list.at(i).c_str())) && temp_expression_list.isEmpty() && expression_list.at(i) != ")" && expression_list.at(i) != "(")
		{
			while (true)
			{
				if (priority(expression_list.at(i)) >= priority(temp_expression_list.at(0)))
				{
					if ((temp_expression_list.at(0) == "cos" || temp_expression_list.at(0) == "sin" || temp_expression_list.at(0) == "ctg" || temp_expression_list.at(0) == "log" || temp_expression_list.at(0) == "abs" || temp_expression_list.at(0) == "ln" || temp_expression_list.at(0) == "tg" || temp_expression_list.at(0) == "sqrt") && expression_list.at(i) == "--")
					{
						postfix_expression_list.push_back(temp_expression_list.at(0));
						temp_expression_list.pop_front();
						postfix_expression_list.push_back(expression_list.at(i));
						if (!temp_expression_list.isEmpty())
							break;
					}
					else
					{
						temp_expression_list.push_front(expression_list.at(i));
						break;
					}
				}
				else if (priority(expression_list.at(i)) < priority(temp_expression_list.at(0)))
				{
					while (priority(expression_list.at(i)) < priority(temp_expression_list.at(0)))
					{
						postfix_expression_list.push_back(temp_expression_list.at(0));
						temp_expression_list.pop_front();
						if (!temp_expression_list.isEmpty())
							break;
					}
				}
				if (!temp_expression_list.isEmpty() && expression_list.at(i) != "--")
				{
					temp_expression_list.push_front(expression_list.at(i));
					break;
				}
				if (i == expression_list.get_size() - 1)
					break;
			}
		}
		if (i == expression_list.get_size())
			break;
	}
	while (temp_expression_list.isEmpty())
	{
		postfix_expression_list.push_back(temp_expression_list.at(0));
		temp_expression_list.pop_front();
	}
	expression_list.clear();
	for (int i = 0; i < postfix_expression_list.get_size(); i++)
		expression_list.push_back(postfix_expression_list.at(i));
}

//check operation priority
int priority(string operation)
{
	int priority_value=0;
	if (operation == "^")
		priority_value = 3;
	else
	{
		if (operation == "*" || operation == "/")
			priority_value = 2;
		else
		{
			if (operation == "+" || operation == "-")
				priority_value = 1;
		}
	}
	if (operation == "(")
		priority_value = 0;
	if (operation == "cos" || operation == "sin" || operation == "ctg" || operation == "abs" || operation == "tg" || operation == "ln" || operation == "log" || operation == "sqrt")
		priority_value = 3;
	if (operation == "--")
		priority_value = 3;
	return priority_value;
}

//calculate the result of an expression
double calculation(LinkedList& expression_list)
{
	LinkedList temp_expression_list;
	string value1, value2, value3;
	double result;

	for (int i = 0; i < expression_list.get_size(); i++)
	{
		if (!(atof(expression_list.at(i).c_str())))
		{
			temp_expression_list.push_front(expression_list.at(i));
			continue;
		}
		if (atof(expression_list.at(i).c_str()))
		{
			value3 = expression_list.at(i);
		again:
			if (!(atof(temp_expression_list.at(0).c_str())) && !(temp_expression_list.at(0) == "sin" || temp_expression_list.at(0) == "cos" || temp_expression_list.at(0) == "log" || temp_expression_list.at(0) == "abs" || temp_expression_list.at(0) == "ctg" || temp_expression_list.at(0) == "ln" || temp_expression_list.at(0) == "tg" || temp_expression_list.at(0) == "sqrt" || temp_expression_list.at(0) == "--"))
			{
				temp_expression_list.push_front(expression_list.at(i));
				continue;
			}
			else if (temp_expression_list.at(0) == "sin" || temp_expression_list.at(0) == "cos" || temp_expression_list.at(0) == "log" || temp_expression_list.at(0) == "abs" || temp_expression_list.at(0) == "ctg" || temp_expression_list.at(0) == "ln" || temp_expression_list.at(0) == "tg" || temp_expression_list.at(0) == "sqrt" || temp_expression_list.at(0) == "--")
			{
				if (temp_expression_list.at(0) == "sin")
				{
					temp_expression_list.pop_front();
					value3 = to_string(sin(atof(value3.c_str())));
					goto next2;
				}
				if (temp_expression_list.at(0) == "cos")
				{
					temp_expression_list.pop_front();
					value3 = to_string(cos(atof(value3.c_str())));
					goto next2;
				}
				if (temp_expression_list.at(0) == "log")
				{
					temp_expression_list.pop_front();
					value3 = to_string(log10(atof(value3.c_str())));
					goto next2;
				}
				if (temp_expression_list.at(0) == "abs")
				{
					temp_expression_list.pop_front();
					value3 = to_string(abs(atof(value3.c_str())));
					goto next2;
				}
				if (temp_expression_list.at(0) == "ctg")
				{
					temp_expression_list.pop_front();
					value3 = to_string(cos(atof(value3.c_str())) / sin(atof(value3.c_str())));
					goto next2;
				}
				if (temp_expression_list.at(0) == "ln")
				{
					temp_expression_list.pop_front();
					value3 = to_string(log(atof(value3.c_str())));
					goto next2;
				}
				if (temp_expression_list.at(0) == "tg")
				{
					temp_expression_list.pop_front();
					value3 = to_string(tan(atof(value3.c_str())));
					goto next2;
				}
				if (temp_expression_list.at(0) == "sqrt")
				{
					temp_expression_list.pop_front();
					value3 = to_string(sqrt(atof(value3.c_str())));
					goto next2;
				}
				if (temp_expression_list.at(0) == "--")
				{
					temp_expression_list.pop_front();
					value3 = to_string((-1) * atof(value3.c_str()));
					goto next2;
				}
			next2:
				if (temp_expression_list.get_size() != 0)
					if (atof(temp_expression_list.at(0).c_str()) || temp_expression_list.at(0) == "sin" || temp_expression_list.at(0) == "cos" || temp_expression_list.at(0) == "log" || temp_expression_list.at(0) == "abs" || temp_expression_list.at(0) == "ctg" || temp_expression_list.at(0) == "ln" || temp_expression_list.at(0) == "tg" || temp_expression_list.at(0) == "sqrt" || temp_expression_list.at(0) == "--")
						goto again;
				temp_expression_list.push_front(value3);
				continue;
			}
			value1 = temp_expression_list.at(0);
			temp_expression_list.pop_front();
			if (temp_expression_list.at(0) == "-")
			{
				temp_expression_list.pop_front();
				value3 = to_string(atof(value1.c_str()) - atof(value3.c_str()));
				goto next;
			}
			if (temp_expression_list.at(0) == "+")
			{
				temp_expression_list.pop_front();
				value3 = to_string(atof(value1.c_str()) + atof(value3.c_str()));
				goto next;
			}
			if (temp_expression_list.at(0) == "*")
			{
				temp_expression_list.pop_front();
				value3 = to_string(atof(value1.c_str()) * atof(value3.c_str()));
				goto next;
			}
			if (temp_expression_list.at(0) == "/")
			{
				temp_expression_list.pop_front();
				value3 = to_string(atof(value1.c_str()) / atof(value3.c_str()));
				goto next;
			}
			if (temp_expression_list.at(0) == "^")
			{
				temp_expression_list.pop_front();
				value3 = to_string(pow(atof(value1.c_str()), atof(value3.c_str())));
				goto next;
			}
		next:
			if (temp_expression_list.get_size() != 0)
				if (atof(temp_expression_list.at(0).c_str()) || temp_expression_list.at(0) == "sin" || temp_expression_list.at(0) == "cos" || temp_expression_list.at(0) == "log" || temp_expression_list.at(0) == "abs" || temp_expression_list.at(0) == "ctg" || temp_expression_list.at(0) == "ln" || temp_expression_list.at(0) == "tg" || temp_expression_list.at(0) == "sqrt" || temp_expression_list.at(0) == "--")
					goto again;
			temp_expression_list.push_front(value3);
		}
	}
	if (!(temp_expression_list.get_size() == 1))
	{
		while (temp_expression_list.get_size() != 1)
		{
			value1 = temp_expression_list.at(0);
			temp_expression_list.pop_front();
			if (temp_expression_list.at(0) == "-" || temp_expression_list.at(0) == "+" || temp_expression_list.at(0) == "*" || temp_expression_list.at(0) == "/" || temp_expression_list.at(0) == "^")
			{
				value2 = temp_expression_list.at(0);
				temp_expression_list.pop_front();
			}
			if (temp_expression_list.at(0) == "-")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(atof(value2.c_str()) - atof(value1.c_str())));
			}
			if (temp_expression_list.at(0) == "+")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(atof(value2.c_str()) + atof(value1.c_str())));
			}
			if (temp_expression_list.at(0) == "*")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(atof(value2.c_str()) * atof(value1.c_str())));
			}
			if (temp_expression_list.at(0) == "/")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(atof(value2.c_str()) / atof(value1.c_str())));
			}
			if (temp_expression_list.at(0) == "^")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(pow(atof(value2.c_str()), atof(value1.c_str()))));
			}
			if (temp_expression_list.at(0) == "sin")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(sin(atof(value1.c_str()))));
			}
			if (temp_expression_list.at(0) == "cos")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(cos(atof(value1.c_str()))));
			}
			if (temp_expression_list.at(0) == "log")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(log10(atof(value1.c_str()))));
			}
			if (temp_expression_list.at(0) == "abs")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(abs(atof(value1.c_str()))));
			}
			if (temp_expression_list.at(0) == "ctg")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(cos(atof(value1.c_str())) / sin(atof(value3.c_str()))));
			}
			if (temp_expression_list.at(0) == "ln")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(log(atof(value1.c_str()))));
			}
			if (temp_expression_list.at(0) == "tg")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(tan(atof(value1.c_str()))));
			}
			if (temp_expression_list.at(0) == "sqrt")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string(sqrt(atof(value1.c_str()))));
			}
			if (temp_expression_list.at(0) == "--")
			{
				temp_expression_list.pop_front();
				temp_expression_list.push_front(to_string((-1) * atof(value1.c_str())));
			}
		}
	}
	result = atof(temp_expression_list.at(0).c_str());
	temp_expression_list.clear();
	return result;
}

//check expression for errors
void check(LinkedList& str)
{
	int left_bracket = 0, right_bracket = 0;
	for (int j = 0; j < str.get_size(); j++)
	{
		if (str.at(j) == "(")
			left_bracket++;
		if (str.at(j) == ")")
			right_bracket++;
		if (str.at(j) >= "a" && str.at(j) < +"b")
			throw "Unknown symbol.\n";
		if (str.get_size() - j >= 2)
			if ((str.at(j) == "+" && str.at(j + 1) == "+") || (str.at(j) == "-" && str.at(j + 1) == "-"))
				throw "Extra symbols.\n";
	}
	if (left_bracket != right_bracket)
		throw "The number of opening and closing parentheses is not equal.\n";
	if (str.get_size() == 1)
		throw "Single symbol. No calculations possible.\n";
	if (str.get_size() == 2)
		throw "Only two symbols. No calculations possible.\n";
}

//select parts of the string and add to the nodes of the list
void input(string input ,LinkedList &expression_list)
{
	int counter = 0;
	string temp1, temp2;
	LinkedList transit_expression_list;
	while (counter < input.length())
	{
		while (isdigit(input[counter]) || (input[counter] == '.'))
		{
			temp1.push_back(input[counter]);
			counter++;
		}
		if (temp1[0])
		{
			for (int j = 0; j < temp1.length(); j++)
				temp2.push_back(temp1[j]);
			transit_expression_list.push_back(temp2);
			temp1.clear();
			temp2.clear();
			if (counter == input.length())
				break;
		}
		if (input[counter] == 'p' && input[counter + 1] == 'i')
		{
			transit_expression_list.push_back(to_string(M_PI));
			counter += 2;
			if (counter == input.length())
				break;
		}
		if (input[counter] == 'e')
		{
			transit_expression_list.push_back(to_string(M_E));
			counter++;
			if (counter == input.length())
				break;
		}
		if ((input[counter] == 'c' && input[counter + 1] == 'o' && input[counter + 2] == 's') || (input[counter] == 's' && input[counter + 1] == 'i' && input[counter + 2] == 'n') || (input[counter] == 'c' && input[counter + 1] == 't' && input[counter + 2] == 'g') || (input[counter] == 'l' && input[counter + 1] == 'o' && input[counter + 2] == 'g') || (input[counter] == 'a' && input[counter + 1] == 'b' && input[counter + 2] == 's') || (input[counter] == 'l' && input[counter + 1] == 'n') || (input[counter] == 't' && input[counter + 1] == 'g') || (input[counter] == 's' && input[counter + 1] == 'q' && input[counter + 2] == 'r' && input[counter + 3] == 't'))
		{
			if ((input[counter] == 'c' && input[counter + 1] == 'o' && input[counter + 2] == 's') || (input[counter] == 's' && input[counter + 1] == 'i' && input[counter + 2] == 'n') || (input[counter] == 'c' && input[counter + 1] == 't' && input[counter + 2] == 'g') || (input[counter] == 'l' && input[counter + 1] == 'o' && input[counter + 2] == 'g') || (input[counter] == 'a' && input[counter + 1] == 'b' && input[counter + 2] == 's'))
			{
				for (int j = counter; j < counter + 3; j++)
				{
					temp1.push_back(input[j]);
				}
				if (temp1[0])
				{
					for (int j = 0; j < temp1.length(); j++)
						temp2.push_back(temp1[j]);
					transit_expression_list.push_back(temp2);
					temp1.clear();
					temp2.clear();
					counter += 3;
					if (counter == input.length())
						break;
				}
			}
			if ((input[counter] == 'l' && input[counter + 1] == 'n') || (input[counter] == 't' && input[counter + 1] == 'g'))
			{
				for (int j = counter; j < counter + 2; j++)
				{
					temp1.push_back(input[j]);
				}
				if (temp1[0])
				{
					for (int j = 0; j < temp1.length(); j++)
						temp2.push_back(temp1[j]);
					transit_expression_list.push_back(temp2);
					temp1.clear();
					temp2.clear();
					counter += 2;
					if (counter == input.length())
						break;
				}
			}
			if (input[counter] == 's' && input[counter + 1] == 'q' && input[counter + 2] == 'r' && input[counter + 3] == 't')
			{
				for (int j = counter; j < counter + 4; j++)
				{
					temp1.push_back(input[j]);
				}
				if (temp1[0])
				{
					for (int j = 0; j < temp1.length(); j++)
						temp2.push_back(temp1[j]);
					transit_expression_list.push_back(temp2);
					temp1.clear();
					temp2.clear();
					counter += 4;
					if (counter == input.length())
						break;
				}
			}
		}
		if (counter == input.length())
			break;
		temp1.push_back(input[counter]);
		transit_expression_list.push_back(temp1);
		temp1.clear();
		counter++;
	}
	for (int i = 0; i < transit_expression_list.get_size(); i++)
	{
		expression_list.push_back(transit_expression_list.at(i));
	}
}

//getting prefix notation
void prefix_notation(LinkedList& expression_list)
{
	reverse(expression_list);
	change_notation(expression_list);
	reverse(expression_list);
}

//print expression in prefix notation
string print_prefix(LinkedList& expression_list)
{
	string prefix;
	for (int i = 0; i < expression_list.get_size(); i++)
		prefix += expression_list.at(i) + " ";
	return prefix;
}