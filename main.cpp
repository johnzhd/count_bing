// bing_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>

#include <assert.h>


/*

1             1 1 1 
  2                 1 1 1
    3                   0                                                   t       t
      4       *           1 1 1           *  1 - i * i(n) * 1 - n * g * i(n)  * b(i) 
        5                       1
	      .                       .
	        b                       b(i)






*/






using namespace std;


#define MOD_NUMBER (1000000007)

#define MY_SWAP(a,b) do{if(a!=b){ a^=b;b^=a;a^=b;}}while(0)

class MyMatrix
{
public:
	MyMatrix():row(0),col(0){m_matrix.reserve(3000);};
	~MyMatrix(){};

public:
	void new_row( int n )
	{
		m_matrix.push_back(std::vector<int>());
		m_matrix.back().resize(col,n);
		row++;
	};
	void new_col( int n )
	{
		for ( std::vector<std::vector<int>>::iterator it = m_matrix.begin(); it != m_matrix.end(); it++ )
		{
			it->push_back(n);
		};
		col++;
	};
	void swap( MyMatrix& src )
	{
		m_matrix.swap(src.m_matrix);
		MY_SWAP(row,src.row);
		MY_SWAP(col,src.col);
	};

public:

	int row;
	int col;

	std::vector<std::vector<int>> m_matrix;
	
};

bool multiplication( MyMatrix& result, MyMatrix& left, MyMatrix & right )
{
	MyMatrix res;

	if ( left.col != right.row )
		return false;

	res.col = right.col;
	for ( int i = 0; i < left.row ; i++ )
	{
		res.new_row(0);
	};

	assert( res.row == left.row );


	for ( int i = 0; i < res.row; i++ )
		for ( int j = 0; j < res.col ; j++ )
		{
			res.m_matrix[i][j] = 0;
			for ( int n = 0; n < left.col; n++ )
			{
				res.m_matrix[i][j] += left.m_matrix[i][n] * right.m_matrix[n][j];
			};
		};

	result.swap(res);
	return true;
};

int sum_matrix( MyMatrix& in )
{
	int sum = 0;
	for ( int i = 0; i < in.row; i++ )
		for ( int j = 0; j < in.col ; j++ )
		{
			sum += in.m_matrix[i][j];
			if ( sum > MOD_NUMBER )
				sum %= MOD_NUMBER;
		}

	return sum;
};


class Test {
public:
    static int howmany (string s)
    {
		size_t npos;
		npos = s.find_first_of("bB");
		if ( npos == std::string::npos )
			return 0;
		s.erase(0,npos);
		npos = s.find_last_of("gB");
		if ( npos == std::string::npos )
			return 0;
		s.erase(npos+1);

		std::transform( s.begin(),s.end(), s.begin(), tolower );

		MyMatrix b_i;
		MyMatrix i_n;
		MyMatrix n_g;
		MyMatrix result;

		//
		for ( npos = 0; npos < s.length(); npos++ )
		{
			switch ( s[npos] )
			{
			case 'b':
				b_i.new_row(0);
				break;
			case 'i':
				b_i.new_col(1);
				i_n.new_row(0);
				break;
			case 'n':
				i_n.new_col(1);
				n_g.new_row(0);
				break;
			case 'g':
				n_g.new_col(1);
				break;
			default:
				throw "Input err.";
				break;
			};
		};


		if( false == multiplication(result, b_i, i_n) )
			throw "matrix err for i";

		if( false == multiplication(result, result, n_g) )
			throw "matrix err for n";

		return sum_matrix(result);

		//
    }
public:
	
};


//start 提示：自动阅卷起始唯一标识，请勿删除或增加。
int main()
{   
    cout<<Test::howmany("iinbinbing")<<endl;

	system("pause");
} 
//end //提示：自动阅卷结束唯一标识，请勿删除或增加。