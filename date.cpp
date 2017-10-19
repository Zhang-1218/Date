#include <iostream>
#include <assert.h>
using namespace std;
class Date
{
public:

	Date(int year = 1949, int month = 10, int day = 1)	//���캯��
		: _year(year),
		_month(month),
		_day(day)
	{
		if (year < 0 || month<0 || month>12 || day < 0 || day > 31)
		{
			cout << "���ڴ���" << endl;
		}
	}

	Date(const Date& d)  // �������캯��
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
		count++;
	}

	~Date()  //��������
	{}
	friend ostream & operator<<(ostream & out, const Date & d);
	friend istream & operator>>(istream & cin, Date & d);
	int GetMonthDay(int year,int month);//��ȡÿ������
	Date& operator=(const Date & d);	// '=' ����
	bool operator==(const Date& d);  	// '==' ����
	bool operator!=(const Date& d);     // '!=' ����
	bool operator<(const Date & d);     // '<' ����
	bool operator>(const Date & d);     // '>' ����
	bool operator<=(const Date & d);	// '<='
	bool operator>=(const Date & d);	// '>='
	Date operator+(int days);	        // '+' ������
	Date operator-(int days);	        // '-' ������
	Date& operator+=(int days);         // '+=' 
	Date& operator-=(int days);         // '-='
	Date& Date::operator++();           // ǰ��++
	Date& Date::operator--();           // ǰ��--
	Date operator++(int);               // ���� ++
	Date operator--(int);				// ���� --
	int operator-(const Date& d);       //���������������

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

//��ȡÿ���µ�����
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

// '=' ����
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

// '==' ����
bool Date::operator==(const Date& d)
{
	return (_year == d._year
		&& _month == d._month
		&& _day == d._day);

}

// '!=' ����
bool Date::operator!=(const Date& d)
{
	return !(*this == d);
}

// '<' ����
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

// '>' ����
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

// '+' ������
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

// '-' ������
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

// '++' ǰ��
Date& Date::operator++()
{
	return (*this = *this + 1);
}

// '--' ǰ��
Date& Date::operator--()
{
	return (*this = *this - 1);
}

// '++' ����
Date Date::operator++(int)
{
	Date tmp(*this);
	tmp = tmp + 1;
	return tmp;
}

// '--' ����
Date Date::operator--(int)
{
	Date tmp(*this);
	tmp = tmp - 1;
	return tmp;
}

//����������������
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

// << �������������
ostream & operator<<(ostream & out, const Date & d)
{
	out << d._year << "-" << d._month << "-" << d._day << endl;
	return out;
}

// >> ��ȡ���������
istream & operator>>(istream & in, Date & d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}

// ���徲̬��Ա��������ȡ����������ô���
void Date::showCount()
{
	cout << "�������캯�����ô�����"<< count << endl;
}
//���⣬�Ծ�̬��Ա���г�ʼ��
int Date::count = 0;


int main()
{
	Date d1(2017, 1, 1);
	d1.showtime();

	// = ����
	//Date d2;
	//Date d3;
	//d3 = d2 = d1;
	//d2.showtime();
	//d3.showtime();

	// < ����
	//Date d2(2018, 9, 9);
	//cout <<( d1 < d2 )<< endl;

	// > ����
	//Date d2(2018, 7, 7);
	//cout << (d1 > d2) << endl;

	// + ����
	//d1 = d1 + (-1);
	//d1.showtime();

	// - ����  
	//d1 = d1 - 32;
	//d1.showtime();

	// += ����
	//d1 += 31;
	//d1.showtime();

	// -= ����
	//d1 -= 32;
	//d1.showtime();

	// ǰ�� ++ ����
	//++d1;
	//d1.showtime();

	// ǰ�� -- ����
	//--d1;
	//d1.showtime();

	// ���� ++ ����
	//Date d2 = d1++;
	//d2.showtime();
	//d1.showtime();

	// ���� -- ����
	//Date d2 = d1--;
	//d2.showtime();
	//d1.showtime();

	//��������֮��
	//Date d2(2017, 2, 1);
	//d2.showtime();
	//int num = 0;
	//num = d2 - d1;
	//cout << num << endl;
	//Date::showCount();
	
	// << ����
	//cin >> d1;
	// >> ����
	//cout << d1;

	system("pause");
	return 0;
}