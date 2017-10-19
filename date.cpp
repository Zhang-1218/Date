#include <iostream>
#include <assert.h>
using namespace std;
class Date
{
public:

	Date(int year = 1949, int month = 10, int day = 1)	//构造函数
		: _year(year),
		_month(month),
		_day(day)
	{
		if (year < 0 || month<0 || month>12 || day < 0 || day > 31)
		{
			cout << "日期错误" << endl;
		}
	}

	Date(const Date& d)  // 拷贝构造函数
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
		count++;
	}

	~Date()  //析构函数
	{}
	friend ostream & operator<<(ostream & out, const Date & d);
	friend istream & operator>>(istream & cin, Date & d);
	int GetMonthDay(int year,int month);//获取每月天数
	Date& operator=(const Date & d);	// '=' 重载
	bool operator==(const Date& d);  	// '==' 重载
	bool operator!=(const Date& d);     // '!=' 重载
	bool operator<(const Date & d);     // '<' 重载
	bool operator>(const Date & d);     // '>' 重载
	bool operator<=(const Date & d);	// '<='
	bool operator>=(const Date & d);	// '>='
	Date operator+(int days);	        // '+' 加天数
	Date operator-(int days);	        // '-' 减天数
	Date& operator+=(int days);         // '+=' 
	Date& operator-=(int days);         // '-='
	Date& Date::operator++();           // 前置++
	Date& Date::operator--();           // 前置--
	Date operator++(int);               // 后置 ++
	Date operator--(int);				// 后置 --
	int operator-(const Date& d);       //两个日期相差天数

	void showtime()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	static void showCount();

private:
	int _year;
	int _month;
	int _day;
	static int count;
};

//获取每个月的天数
int Date::GetMonthDay(int year, int month)
{
	assert(month > 12 && month < 1);

	int arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (month == 2)
	{
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			arr[month] = 31;
		}
	}

	return arr[month];
}

// '=' 重载
Date & Date::operator=(const Date & d)
{
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	return *this;
}

// '==' 重载
bool Date::operator==(const Date& d)
{
	return (_year == d._year
		&& _month == d._month
		&& _day == d._day);

}

// '!=' 重载
bool Date::operator!=(const Date& d)
{
	return !(*this == d);
}

// '<' 重载
bool Date::operator<(const Date & d)
{
	if (this->_year < d._year)
	{
		return true;
	}
	else if (this->_year == d._year)
	{
		if (this->_month < d._month)
		{
			return true;
		}
		else if (this->_month == d._month)
		{
			if (this->_day < d._day)
			{
				return true;
			}
		}
	}

	return false;
}

// '>' 重载
bool Date::operator>(const Date & d)
{
	return !((*this < d || *this == d));
}

// '<='
bool Date::operator<=(const Date & d)
{
	return !(*this > d);
}

// '>=' 
bool Date::operator>=(const Date & d)
{
	return !(*this < d);
}

// '+' 加天数
Date Date::operator+(int days)
{
	Date tmp(*this);

	if (days<0)
	{
		return *this - (-days);
	}

	tmp._day += days;

	while (tmp._day > GetMonthDay(tmp._year, tmp._month))
	{
		tmp._day -= GetMonthDay(tmp._year, tmp._month);

		if (tmp._month == 12)
		{
			tmp._year++;
			tmp._month = 1;
		}
		else
		{
			tmp._month++;
		}
	}

	return tmp;
}

// '-' 减天数
Date Date::operator-(int days)
{
	Date tmp(*this);

	if (days < 0)
	{
		return *this + (-days);
	}

	tmp._day -= days;

	while (tmp._day <= 0)
	{
		if (tmp._month == 1)
		{
			tmp._year--;
			tmp._month = 12;
		}
		else
		{
			tmp._month--;
		}

		tmp._day += GetMonthDay(_year, _month);
	}
	return tmp;
}

// '+='
Date& Date::operator+=(int days)
{
	return (*this = *this + days);
}

// '-='
Date& Date::operator-=(int days)
{
	return (*this = *this - days);
}

// '++' 前置
Date& Date::operator++()
{
	return (*this = *this + 1);
}

// '--' 前置
Date& Date::operator--()
{
	return (*this = *this - 1);
}

// '++' 后置
Date Date::operator++(int)
{
	Date tmp(*this);
	tmp = tmp + 1;
	return tmp;
}

// '--' 后置
Date Date::operator--(int)
{
	Date tmp(*this);
	tmp = tmp - 1;
	return tmp;
}

//两个日期相差的天数
int Date::operator-(const Date& d)
{
	Date maxDate(*this);
	Date minDate(d);
	int dayNum = 0;
	int flag = 1;
	if (*this < d)
	{
		maxDate = d;
		minDate = *this;
		flag = -1;
	}
	while (maxDate != minDate)
	{
		++minDate;
		++dayNum;
	}
	return dayNum*flag;
}

// << 插入运算符重载
ostream & operator<<(ostream & out, const Date & d)
{
	out << d._year << "-" << d._month << "-" << d._day << endl;
	return out;
}

// >> 提取运算符重载
istream & operator>>(istream & in, Date & d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}

// 定义静态成员函数，获取拷贝构造调用次数
void Date::showCount()
{
	cout << "拷贝构造函数调用次数："<< count << endl;
}
//类外，对静态成员进行初始化
int Date::count = 0;


int main()
{
	Date d1(2017, 1, 1);
	d1.showtime();

	// = 测试
	//Date d2;
	//Date d3;
	//d3 = d2 = d1;
	//d2.showtime();
	//d3.showtime();

	// < 测试
	//Date d2(2018, 9, 9);
	//cout <<( d1 < d2 )<< endl;

	// > 测试
	//Date d2(2018, 7, 7);
	//cout << (d1 > d2) << endl;

	// + 测试
	//d1 = d1 + (-1);
	//d1.showtime();

	// - 测试  
	//d1 = d1 - 32;
	//d1.showtime();

	// += 测试
	//d1 += 31;
	//d1.showtime();

	// -= 测试
	//d1 -= 32;
	//d1.showtime();

	// 前置 ++ 测试
	//++d1;
	//d1.showtime();

	// 前置 -- 测试
	//--d1;
	//d1.showtime();

	// 后置 ++ 测试
	//Date d2 = d1++;
	//d2.showtime();
	//d1.showtime();

	// 后置 -- 测试
	//Date d2 = d1--;
	//d2.showtime();
	//d1.showtime();

	//两个日期之差
	//Date d2(2017, 2, 1);
	//d2.showtime();
	//int num = 0;
	//num = d2 - d1;
	//cout << num << endl;
	//Date::showCount();
	
	// << 测试
	//cin >> d1;
	// >> 测试
	//cout << d1;

	system("pause");
	return 0;
}