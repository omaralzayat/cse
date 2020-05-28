#include<iostream>
#include<string>
#include<sstream>
#include<process.h>
#include<map>
using namespace std;
class Matrix
{
public:
	static const int max = 100;           //maximam numder of rows and columns
	double value[max][max] = {};
	string name;
	int numRows=0;
	int numColumns = 0;
	void SetMatrix(string str) {
		for (size_t i = 0; i < 10; i++)
		{
			fill(begin(value[i]), end(value[i]), 0);
		}
		numColumns = 0;
		size_t asspos , begin , end , Sempos , LastSempos;
		string input = "";
		string TakeFirstWord ,Row , Element;
		stringstream fss;
		int i, j;
		i = 0;
		j = 0;
		asspos = str.find('=');
		begin = str.find('[');
		end = str.find(']');
		fss << str.substr(0, asspos);
		fss >> TakeFirstWord;
		name = TakeFirstWord;
		if ((begin != string::npos) && (end != string::npos))
		{
			input = str.substr(begin + 1, end - begin - 1)+" ";
		}
		Sempos = input.find(';');
		LastSempos = 0;
		int numbinp = 0;
		while (Sempos != string::npos)
		{
			j = 0;
			Row = input.substr(LastSempos, Sempos - LastSempos);
			LastSempos = Sempos + 1;
			Element = "";
			Sempos = input.find(';',LastSempos);
			for (auto TempEl : Row)
			{
				if ((TempEl == ' ') && (Element != "") && (Element != " ")) {
					value[i][j] = atof(Element.c_str());
					j++;
					Element = "";
				}
				else {
					Element += TempEl;
					if (Element == " ") {
						Element = "";
					}
				}
			}
			if (atof(Element.c_str()) != 0) {
				value[i][j] = atof(Element.c_str());
				j++;
				Element = "";
			}
			i++;
			if (j > numColumns)
			{
				numColumns = j;
			}
		}
		j = 0;
		Row = input.substr(LastSempos, Sempos - LastSempos);
		LastSempos = Sempos + 1;
		Sempos = input.find(';', LastSempos);
		Element = "";
		int noOfEl = 0;
		for (auto TempEl : Row)
		{
			noOfEl++;
			if ((TempEl == ' ')&&(Element != "")&&(Element!=" ")) {
				value[i][j] = atof(Element.c_str());
				j++;
				Element = "";
			}
			else {
				Element += TempEl;
				if (Element == " ") {
					Element = "";
				}
			}
			
		}
		value[i][j] = atof(Element.c_str());
		Element = "";
		i++;
		numRows = i;
		if (j > numColumns)  numColumns = j;
	}
	void display() {
		if(numColumns!= 0)cout << "[ ";
		for (int i = 0; i < numRows; i++)
		{
			for (int j = 0; j < numColumns; j++)
			{
				if (std::abs(value[i][j]) < 0.000001) { value[i][j] = 0; }
				cout << value[i][j] << " ";
			}
			if (i != numRows-1)
			{
				cout << ";";
			}
		}
		if (numColumns != 0)cout << "]"<<endl;
	}
	void add(Matrix other , Matrix third) {
		for (size_t i = 0; i < 10; i++)
		{
			fill(begin(value[i]), end(value[i]), 0);
		}
		 if ((third.numColumns == other.numColumns) && (third.numRows == other.numRows)) {
			 for (int i = 0; i < numRows; i++)
			 {
				 for (int j = 0; j < numColumns; j++)
				 {
					 value[i][j] = other.value[i][j] + third.value[i][j];
				 }
			 }
			 numColumns = other.numColumns;
			 numRows = other.numRows;
			 name = other.name + "p" + third.name;
		 }
	}
	void sub(Matrix other, Matrix third) {
		for (size_t i = 0; i < 10; i++)
		{
			fill(begin(value[i]), end(value[i]), 0);
		}
		if ((third.numColumns == other.numColumns) && (third.numRows == other.numRows)) {
			for (int i = 0; i < numRows; i++)
			{
				for (int j = 0; j < numColumns; j++)
				{
					value[i][j] = other.value[i][j] - third.value[i][j];
				}
			}
			numColumns = other.numColumns;
			numRows = other.numRows;
			name = other.name + "m" + third.name;
		}
	}
	void T(Matrix other) {
		for (size_t i = 0; i < 10; i++)
		{
			fill(begin(value[i]), end(value[i]), 0);
		}
		for (int i = 0; i < max; i++)
		{
			for (int j = 0; j < max; j++)
			{
				value[i][j] = other.value[j][i];     //switch the number of col and row for an element and store it in a new matrix
			}
			numColumns = other.numRows;
			numRows = other.numColumns;
			name = other.name + "T";
		}
	}
	void mult(Matrix first, Matrix second) {
		for (size_t i = 0; i < 10; i++)
		{
			fill(begin(value[i]), end(value[i]), 0);
		}
		if (first.numColumns == second.numRows) {
		    numColumns = second.numColumns;
			numRows = first.numRows;
			for (int i = 0; i < numRows; i++)
			{
				for (int j = 0; j < second.numColumns; j++)
				{
					for (int k = 0; k < first.numColumns; k++) {
						value[i][j] += first.value[i][k] * second.value[k][j];
					}
				}
			}
			name = first.name + "x" + second.name;
		}
	}
	double det() {
		Matrix Con;
		Con.numColumns = numColumns - 1;
		Con.numRows = numRows - 1;
		int sign;
		int a;
		double result=0;
		if (numColumns == numRows) {
			if (numColumns == 1) {
				return value[0][0];
			}
			else
			{
				for (int j = 0; j < numColumns; j++) {
					for (int k = 1; k < numRows; k++)
					{
						for (int i = 0; i < numColumns; i++)
						{
							if (i != j) {
								a = (i < j) ? i : i - 1;
								Con.value[k - 1][a] = value[k][i];
							}
						}
					}
					sign = (j % 2 == 0) ? 1 : -1;
					result += sign * value[0][j] * Con.det();
				}
				return result;
			}

		}
	}
	void inverse(Matrix other) {
		//finding the inverse using gauss-jordon method
		for (int i = 0; i < 10; i++)
		{
			fill(begin(value[i]), end(value[i]), 0);
		}
		numColumns = other.numColumns;
		numRows = other.numRows;
		name = other.name + "i";
		double factor;
		//Appling the opreation only if the maitrix is square and has more than one element
		if ((other.numColumns == other.numRows)&&(other.numColumns != 1)) {
			for (int i = 0; i < numRows; i++)
			{                                         //set the inverse matrix as identity matrix
				for (int j = 0; j < numColumns; j++)
				{
					value[i][j] = (i == j) ? 1 : 0;
				}
			}
			for (int i = 0; i < numRows; i++)
			{                                        //Apply elementary row operations untill the matrix is a diagonal matrix and the identity matrix is the inverse
				for (int j = 0; j < numRows; j++)
				{
					if (i != j) {
						factor = other.value[j][i] / other.value[i][i];
						for (int k = 0; k < numColumns; k++)
						{
							value[j][k] -= factor * value[i][k];
							other.value[j][k] -= factor * other.value[i][k];
						}
					}
				}
			}
			for (int i = 0; i < numRows; i++)
			{
				for (int j = 0; j < numColumns ; j++)
				{
					value[i][j] = value[i][j] / other.value[i][i];
				}
			}
		} 
	}
	void empty() {
		for (size_t i = 0; i < 10; i++)
		{
			fill(begin(value[i]), end(value[i]), 0);
		}
		numColumns = 0;
		numRows = 0;
		name = "";
	}
};
int main() {
	cout << "Enter a matrix in the form:'MatrixName = [value11 value12 ; value21 value22]'";
	cout <<	"\nup to 100*100 Matrix\nonly the first word in the name will be taken"<<endl;
	int NumberOfOpEl = 0;
	int numberOfsubEl = 0;
	string tempoperation = "";
	string x;
	string operation="";
	string lastoperation = "";
	string suboperation = "";
	string lastsuboperation = "";
	string username = "";
	int lastmult = 0;
	char plusorminus='n';
	Matrix path ,temp ,Operational;
	map<string, Matrix > matrices;
		getline(cin, x);             //get the users first input
		if ((x == "exit") || (x == "Exit")) exit(0);
		//looking for equal sign or operation in the input
		for (auto el : x)
		{
			if (el == '=')
			{
				path.SetMatrix(x);            //take the first word of the string and set it as the matrixname and set the value for the number btw []
				matrices[path.name] = path;    //store the Matix in a map and set the key as the Matrix name
				//delete the matrix if its name includes an oberation
				for (auto i : path.name)
				{
					if ((i == '+') || (i == '-') || (i == '*') || (i == '\''))matrices.erase(path.name);
				}
				break;
			}
		}
		cout << "You can type the matrix name to display or use the operations + , - , * ,A^ for the inverse A ";
		cout << "and ' for traspose\nthe name cannot cotain an operation\n";
	while (true)
	{
		getline(cin , x);
		if ((x == "exit")||(x == "Exit")) exit(0);
		if ((x.find('=')!=string::npos)&&(x.find('[') == string::npos)) {
			username = x.substr(0, x.find('='));
			x = x.substr(x.find('=') + 1, x.length() - x.find('=') - 1);
		}
		size_t transposepos = x.find('\'');        //the position of transpose sign
		size_t inversepos = x.find('^');
		size_t multpos = x.find('*');           //the position of multiplication sign
		size_t pluspos = x.find('+');
		size_t minuspos = x.find('-');
		if ((x.find('[') == string::npos)&&((x.find('+') != string::npos)|| (x.find('*') != string::npos) || (x.find('-') != string::npos)))x += "+";
		//looping the characters of the users input until there is an operation(=,+,-,*,',^)
		for (auto el : x)
		{
			if (el == '[')
			{
				path.SetMatrix(x);
				matrices[path.name] = path;
				for (auto i : path.name)
				{
					if ((i == '+') || (i == '-') || (i == '*') || (i == '\''))matrices.erase(path.name);
					break;
				}
				break;
			}
			else 
			{
				if (((el == '+') || (el == '-')))
				{
					operation += "*";
					lastsuboperation = "";
					for (auto l : operation)
					{
						if (l == '\'')
						{
							Operational.T(matrices[x.substr(lastmult, numberOfsubEl-lastmult)]);
							matrices[Operational.name] = Operational;
							matrices[username] = Operational;
							suboperation.replace(0, suboperation.length(), Operational.name);
						}
						if (l == '^')
						{
							if (matrices[x.substr(lastmult , numberOfsubEl-lastmult)].numColumns == matrices[x.substr(lastmult , numberOfsubEl-lastmult)].numRows)
							{
								Operational.inverse(matrices[x.substr(lastmult , numberOfsubEl-lastmult)]);
								matrices[Operational.name] = Operational;
								suboperation.replace(0, suboperation.length(), Operational.name);
							}
							else
							{
								cout << "Matrix has no inverse" << endl;
							}
						}
						if (l == '*')
						{
							lastmult = numberOfsubEl+1;
							if (lastsuboperation != "")
							{
									if (matrices[lastsuboperation].numColumns == matrices[suboperation].numRows) {
										Operational.mult(matrices[lastsuboperation], matrices[suboperation]);
									}
									else
									{
										cout << "invalid operation"<<endl;
										Operational.empty();
									}
								operation.replace(0, numberOfsubEl, Operational.name);
								if (Operational.name != "") {
									matrices[Operational.name] = Operational;
									suboperation = Operational.name; 
								}
							}
							lastsuboperation = suboperation;
							suboperation = "";
							numberOfsubEl++;
						}
						else
						{
							numberOfsubEl++;
							if((l != '\0')&&(l != '\'')&&(l != '^'))suboperation += l;
						}
						if (tempoperation != lastsuboperation)
						{
							tempoperation = lastsuboperation;
						}
						else
						{
							if(suboperation !="")tempoperation = suboperation;
						}
					}
					operation = tempoperation;
					suboperation = "";
					if (lastoperation != "")
					{
							if ((matrices[lastoperation].numColumns == matrices[operation].numColumns)&& (matrices[lastoperation].numRows == matrices[operation].numRows)) {
								if (plusorminus == '+') {
									Operational.add(matrices[lastoperation], matrices[operation]);
									Operational.add(matrices[lastoperation], matrices[operation]);
								}
								if (plusorminus == '-') {
									Operational.sub(matrices[lastoperation], matrices[operation]);
									Operational.sub(matrices[lastoperation], matrices[operation]);
								}
							}
							else
							{
								cout << "invalid operation" << endl;
								Operational.empty();
							}
					}
					lastoperation = operation;
					operation = "";
					NumberOfOpEl++;
					plusorminus = el;
				}
				else
				{
					NumberOfOpEl++;
					operation += el;
				}
				if ((pluspos == string::npos)&& (minuspos == string::npos)&& (multpos == string::npos))
				{
					if (el == '\'')
					{
						Operational.T(matrices[x.substr(0, transposepos)]);
						matrices[Operational.name] = Operational;
					}
					if (el == '^')
					{
						if (matrices[x.substr(0, inversepos)].numColumns == matrices[x.substr(0, inversepos)].numRows)
						{
							Operational.inverse(matrices[x.substr(0, inversepos)]);
							matrices[Operational.name] = Operational;
						}
						else
						{
							cout << "Matrix has no inverse" << endl;
						}
					}
				}
			}
		}
		matrices[username] = Operational;
		matrices.erase(Operational.name);
		matrices[x].display();
		if (matrices[x].name != x)
		{
			if((x.find('[') == string::npos)&& (x.find(']') == string::npos))Operational.display();
		}
		Operational.empty();
		NumberOfOpEl = 0;
		numberOfsubEl = 0;
		operation = "";
		tempoperation = "";
		lastsuboperation = "";
		suboperation = "";
		lastoperation = "";
		username = "";
		lastmult = 0;
	}
	return 0;
}