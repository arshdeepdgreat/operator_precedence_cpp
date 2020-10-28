#include <bits/stdc++.h>
using namespace std;
string wordsk[20];
int wordi=0;

bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}

void goodstring(string str)
{
   string word = "";
   for (auto x : str)
   {
       if (x == ' ')
       {
           wordsk[wordi]=word;
           wordi++;
           word = "";
       }
       else
       {
           word = word + x;
       }
   }
wordsk[wordi]=word;
wordi++;
}

bool a=false,b=false,c=false,d=false,e=false;
int precedence(char op){
	if(op == '+'||op == '-')
	return 1;
	if(op == '*'||op == '/')
	return 2;
	if (op == '^')
    return 3;

	return 0;
}

int applyOp(int a, int b, char op){
	switch(op){
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
		case '^': return pow(a,b);
	}
}


int evaluate(string tokens){
	int i;

	// stack to store integer values.
	stack <int> values;

	// stack to store operators.
	stack <char> ops;

	for(i = 0; i < tokens.length(); i++){

		// Current token is a whitespace,
		// skip it.
		if(tokens[i] == ' ')
			continue;

		else if(isdigit(tokens[i])){
			int val = 0;

			// There may be more than one
			// digits in number.
			while(i < tokens.length() &&
						isdigit(tokens[i]))
			{
				val = (val*10) + (tokens[i]-'0');
				i++;
			}

			values.push(val);
		}

		// Current token is an operator.
		else
		{
			// While top of 'ops' has same or greater
			// precedence to current token, which
			// is an operator. Apply operator on top
			// of 'ops' to top two elements in values stack.
			while(!ops.empty() && precedence(ops.top())
								>= precedence(tokens[i])){
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			// Push current token to 'ops'.
			ops.push(tokens[i]);
		}
	}

	// Entire expression has been parsed at this
	// point, apply remaining ops to remaining
	// values.
	while(!ops.empty()){
		int val2 = values.top();
		values.pop();

		int val1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();

		values.push(applyOp(val1, val2, op));
	}

	// Top of 'values' contains result, return it.
	return values.top();
}

void valid(string wordsk[20])
{
    int cnt=0;
    while (wordsk[cnt]!= "\0")
    {
        cnt++;
    }

    if (!isNumber(wordsk[cnt-1]))
    {
        cout<<"wrong string"<<endl;
        exit(100);
    }
    for (int k=1;k<cnt;k+=2)
    {
        if (wordsk[k]=="+" || wordsk[k]=="-" || wordsk[k]=="*" || wordsk[k]=="/" || wordsk [k]=="^")
        {
            continue;
        }
        else
        {
            cout<<"wrong string"<<endl;
            exit(100);
        }
    }
    for (int k=0;k<cnt;k+=2)
    {
        if (!isNumber(wordsk[k]))
        {
            cout<<"error";
            exit(100);
        }
    }

}

void printing(char ar[6],int i,int k)
{
    cout<<"\t";
    cout << ar[k];
        for (int l=1;l<i;l++)
        {
            if (precedence(ar[k])>precedence(ar[l]))
            {
                cout <<" "<< '>' ;
            }
            else if (precedence(ar[k])==precedence(ar[l]) && precedence(ar[l])!=3)
            {
                cout<<" "<< '>';
            }
            else if (precedence(ar[k])< precedence(ar[l]))
            {
                cout<<" "<<'<';
            }
            else if (precedence(ar[k])==precedence(ar[l]) && precedence(ar[l])==3)
            {
                cout<<" "<<'<';
            }
        }
        cout << endl;
}

int main()
{
    cout << "enter a expression \nin a manner that the operators and operands are seperated by a single space \nand only ^,*,/,+,- are allowed"<< "\n";
    string tokens;
    getline(cin,tokens);

    goodstring(tokens);
    valid(wordsk);

    cout<< endl;
    for (int i=0;i<tokens.length();i++)
    {
        switch (tokens[i])
        {
            case '+':a=true;
            break;
            case '-':b=true;
            break;
            case '*':c=true;
            break;
            case '/':d=true;
            break;
            case '^':e=true;
            break;
        }
    }
    //cout<< a <<" "<< b << " " << c << " " << d << endl;

    char ar[6];
    int i=1;

    if (a==true)
    {
        ar[i]='+';
        i++;
    }
    if (b==true)
    {
        ar[i]='-';
        i++;
    }
    if (c==true)
    {
        ar[i]='*';
        i++;
    }
    if (d==true)
    {
        ar[i]='/';
        i++;
    }
    if (e==true)
    {
        ar[i]='^';
        i++;
    }
cout<<"OPERATOR PRECEDENCE FOR THE GIVEN EXPRESSION"<<endl;
cout<<"\t";
for (int j=0;j<i;j++)
    cout << ar[j]<< " ";
    cout<<endl;

for (int k=1;k<i;k++)
    {
        printing(ar,i,k);
    }
cout<<endl<<endl;
cout<<"_____________________________________________"<<endl<<endl<<endl;

    cout<<"   "<<"Answer of  "<<tokens;
    cout<<" = "<< evaluate(tokens)<< endl;
    cout<<endl;
cout<<"_____________________________________________"<<endl<<endl<<endl;
    return 0;
}
