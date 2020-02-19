#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

enum class month{January=1, February, March, April, May, June, July, August, September, October, November, December,};//////////////////////

class Date{
private:
    /*****************/
    /*PRIVATE MEMBERS*/
    /*****************/
    unsigned int _day;
    unsigned int _year;
    //enum class month{January=1, February, March, April, May, June, July, August, September, October, November, December,};////////////////////
    month _month;
    bool _leap;
    
    /**************************/
    /*PRIVATE MEMBER FUNCTIONS*/
    /**************************/
    
    //Private method which adds a single _day
    //  +INPUT: NONE
    //  +OUTPUT: NONE
    void add_single_day(){
        switch(_month){
            case month::January: case month::March: case month::May: case month::July: case month::August: case month::October:
                if(_day == 31)
                {
                    _day = 1;
                    _month=static_cast<month>(static_cast<unsigned int>(_month)+1); //month++
                }
                else
                    _day++;
                break;
            case month::December:
                if(_day == 31)
                {
                    _day = 1;
                    _month=month::January;
                    _year++;
                    _leap = is_leap();
                }
                else
                    _day++;
                break;
            case month::April: case month::June: case month::September: case month::November:
                
                if(_day == 30)
                {
                    _day = 1;
                    _month=static_cast<month>(static_cast<unsigned int>(_month)+1); //month++
                }
                else
                    _day++;
                break;
            case month::February:
                if(_leap)
                {
                    if(_day == 29)
                    {
                        _day = 1;
                        _month=static_cast<month>(static_cast<unsigned int>(_month)+1); //month++
                    }
                    else
                        _day++;
                }
                else
                {
                    if(_day == 28)
                    {
                        _day = 1;
                        _month=static_cast<month>(static_cast<unsigned int>(_month)+1); //month++
                    }
                    else
                        _day++;
                }
                break;
        }
        return;
    }
    
    //Private method which determines if a year is lear or not
    //  +INPUT: NONE
    //  +OUTPUT: const bool (leap = true, not leap = false)
    const bool is_leap() const{
        return (_year%4==0) & (!(_year%100==0) | (_year%400==0));
    }

public:
    
    /*************************/
    /*PUBLIC MEMBER FUNCTIONS*/
    /*************************/
    
    void print() const;
    Date();
    Date(const unsigned int year, const string month, const unsigned int day);
    Date(const unsigned int myday, const unsigned int mymonth, const unsigned int myyear);
    
    //Public method which returns the day as unsigned int
    //  +INPUT: NONE
    //  +OUTPUT: const unsigned int, day.
    const unsigned int myday() const
    {
        return _day;
    }
    
    //Public method which returns the year as unsigned int
    //  +INPUT: NONE
    //  +OUTPUT: const unsigned int, year.
    const unsigned int myyear() const
    {
        return _year;
    }
    
    //Public method which returns the month as a string
    //  +INPUT: NONE
    //  +OUTPUT: const string, name of the month.
    const string mymonth() const
    {
        switch(_month){
            case month::January:
                return "January";
            case month::February:
                return "February";
            case month::March:
                return "March";
            case month::April:
                return "April";
            case month::May:
                return "May";
            case month::June:
                return "June";
            case month::July:
                return "July";
            case month::August:
                return "August";
            case month::September:
                return "September";
            case month::October:
                return "October";
            case month::November:
                return "November";
            case month::December:
                return "December";
            default:
                return "November";
        }
    }
    
    //Public method which returns the month as an unsigned int
    //  +INPUT: NONE
    //  +OUTPUT: unsigned int, number corrispondent to the month
    const unsigned int nummonth() const
    {
        return static_cast<unsigned int>(_month);
    }
    
    //Public method which add a certain unbers of day to the date.
    //  +INPUT: n, unsigned int; amount of days to be added
    //  +OUTPUT: NONE
    void add_days(const unsigned int n)
    {
        for(unsigned int i{0}; i<n;i++)
            add_single_day();
        
            return;
    }
    
    //Public method which fix a month using a string as input. In the name is not correct, is set as default (November)
    //  +INPUT: 
    //      -name, string: string which contains the name of the month
    //  +OUTPUT: NONE
    void set_month(string name)
    {
        if(name == "February")
            _month = month::February;
        else if(name == "March")
            _month = month::March;
        else if(name == "April")
            _month = month::April;
        else if(name == "May")
            _month = month::May;
        else if(name == "June")
            _month = month::June;
        else if(name == "August")
            _month = month::August;
        else if(name == "September")
            _month = month::September;
        else if(name == "October")
            _month = month::October;
        else if(name == "January")
            _month = month::January;
        else if(name == "December")
            _month = month::December;
        else
            _month = month::November;
        
        return;
    }
    
};

//CLASS: Date
//Custom CONSTRUCTOR. Initializes the values by using the month as string
//  +INPUT: 
//      -oneyear, const unsigned int; year to be set.
//      -onemonth, const string; month to be set
//      -oneday, const unsigned int; day to be set.
Date::Date(const unsigned int oneyear, const string onemonth, const unsigned int oneday) 
    :   _day{oneday},
        _year{oneyear}
{
        _leap = is_leap();
        set_month(onemonth);
}

//CLASS: Date
//Custom CONSTRUCTOR. Initializes the values by using the month as an unsigned int
//  +INPUT: 
//      -myyear, const unsigned int; year to be set.
//      -mymonth, const unsigned int; month to be set
//      -myday, const unsigned int; day to be set.
Date::Date(const unsigned int myday, const unsigned int mymonth, const unsigned int myyear) :
    _day{myday},
    _month{month(mymonth)},
    _year{myyear}
{
        _leap = is_leap();
        return;
}

//CLASS: Date
//DEFAULT CONSTRUCTOR. Set the default date to my birth date.
Date::Date() :
    _day{3},
    _month{month::November},
    _year{1995}
{
    _leap = false;
    return;
}

//CLASS: Date
//Public method which print on stdin a date
    //  +INPUT: NONE
    //  +OUTPUT: NONE
void Date::print() const
{
    cout << myday() << " " << mymonth() << " " << myyear();
    return;
}

//CLASS: Date
//Overload of operator<< which print a date in a similar way as Date::print()
//  +INPUT: 
//      -std::ostream& os, standard output
//      -const Date& mydate, date which is printed
//  +OUTPUT: os, standard output buffer
std::ostream& operator<<(std::ostream& os, const Date& mydate) {
    os << mydate.myday() << " " << mydate.mymonth() << " " << mydate.myyear();
    return os;
}

//CLASS: Date
//Overload of operator== which compares two Date types
//  +INPUT: 
//      -const Date& lhs, one of the two dates to be compared
//      -const Date& rhs, the other date
//  +OUTPUT: if dates are equal, it return true
bool operator==(const Date& lhs, const Date& rhs)
{
    return ((lhs.myday() == rhs.myday()) && (lhs.mymonth() == rhs.mymonth()) && lhs.myyear() == rhs.myyear());
}

//CLASS: Date
//Overload of operator== which compares two Date types
//  +INPUT: 
//      -const Date& lhs, one of the two dates to be compared
//      -const Date& rhs, the other date
//  +OUTPUT: if dates are equal, it return false
bool operator!=(const Date& lhs, const Date& rhs)
{
    return !(lhs == rhs);
}


/***************
 *MAIN FUNCTION*
 ***************/
int main(void)
{
    Date birth{};
    
    cout << "->Default date: " << endl;
    //cout << birth << endl;
    birth.print();
    cout << endl << endl;
    
    cout << "->Default date + 1: " << endl;
    birth.add_days(1);
    birth.print();
    cout << endl << endl;
    
    cout << "->40 days more: " << endl;
    birth.add_days(39);
    birth.print();
    cout << endl << endl;
    
    cout << "->100 days more: " << endl;
    birth.add_days(100);
    birth.print();
    cout << endl << endl;
    
    cout << "->Custom constructor leap: " << endl;
    Date date1{28,02,2020};
    date1.print();
    cout << endl << endl;
    
    cout << "->One day mote: " << endl;
    date1.add_days(1);
    date1.print();
    cout << endl << endl;
    
    cout << "->Custom constructor not leap: " << endl;
    Date date2{28,02,2019};
    date2.print();
    cout << endl << endl;
    
    cout << "->One day mote: " << endl;
    date2.add_days(1);
    date2.print();
    cout << endl << endl;
    
    cout << "->Custom constructor ultimo dell'anno: " << endl;
    Date date3{31,12,2019};
    date3.print();
    cout << endl << endl;
    
    cout << "->One day mote: " << endl;
    date3.add_days(1);
    date3.print();
    cout << endl << endl;
    
    cout << "->Method << prove: " << endl << date3 << endl << endl;
    
    cout << "dateB = dateA+1; dateB == dateA+1?" << endl;
    Date dateA{30,12,2019};
    Date dateB{31,12,2019};
    dateA.add_days(1);
    cout << (dateA == dateB) << endl << endl;
    
    cout << "dateA = dateB+1; dateB == dateA?" << endl;
    dateA.add_days(1);
    cout << (dateA == dateB) << endl << endl;
    
    cout << "dateA = dateB+1; dateB != dateA?" << endl;
    cout << (dateA != dateB) << endl << endl;
    
    
    
    cout << endl;
}
