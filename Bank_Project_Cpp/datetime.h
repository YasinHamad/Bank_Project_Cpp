#pragma once
#pragma warning(disable : 4996) // for removing the ctime() function warning

#include <ctime>
#include <iostream>
#include <string>
#include "manipulators.h"
using namespace std;

namespace datetime
{
	enum enDateTime { year, month, day, hour, minute, seconds, week_day, year_day, daylight_saving_time };
	enum enYearTime { Days, Hours, Minutes, Seconds };
	struct stDate {
		int day;
		int month;
		int year;
	};
	struct stPeriod {
		stDate starDate;
		stDate endDate;
	};

	char* GetCurrentTime() {
		time_t t = time(0);

		char* t_string = ctime(&t);

		return t_string;
	}

	char* GetGreenwichTime() {
		time_t t = time(0);
		char* t_string = NULL;

		tm* gmtm = gmtime(&t);
		t_string = asctime(gmtm);

		return t_string;
	}

	int GetDateTime(enDateTime _var) {

		time_t t = time(0);

		tm* now = localtime(&t);

		switch (_var)
		{
		case year:
			return now->tm_year + 1900;
		case month:
			return now->tm_mon + 1;
		case day:
			return now->tm_mday;
		case hour:
			return now->tm_hour;
		case minute:
			return now->tm_min;
		case seconds:
			return now->tm_sec;
		case week_day:
			return now->tm_wday;
		case year_day:
			return now->tm_yday;
		case daylight_saving_time:
			return now->tm_isdst;
		default:
			return -1;
		}
	}

	bool IsLeapYear(int year) {
		return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
	}


	int GetYearTime(int year, enYearTime time) {
		int year_days = IsLeapYear(year) ? 366 : 365;

		switch (time) {
		case enYearTime::Days: return year_days;
		case enYearTime::Hours: return year_days * 24;
		case enYearTime::Minutes: return year_days * 24 * 60;
		case enYearTime::Seconds: return year_days * 24 * 60 * 60;
		default: return -1;
		}
	}

	int NumberOfDaysInYear(int year) {
		return IsLeapYear(year) ? 366 : 365;
	}
	int NumberOfHoursInYear(int year) {
		return NumberOfDaysInYear(year) * 24;
	}
	int NumberOfMinutesInYear(int year) {
		return NumberOfHoursInYear(year) * 60;
	}
	int NumberOfSecondsInYear(int year) {
		return NumberOfMinutesInYear(year) * 60;
	}

	int GetDaysInMonth(int month, int year) {
		if (month <= 0 || month >= 13) return 0;
		int NumberOfDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : NumberOfDays[month - 1];
	}

	int GetHoursInMonth(int month, int year) {
		return GetDaysInMonth(month, year) * 24;
	}

	int GetMinutesInMonth(int month, int year) {
		return GetHoursInMonth(month, year) * 60;
	}

	int GetSecondsInMonth(int month, int year) {
		return GetMinutesInMonth(month, year) * 60;
	}

	// returns the name of the day
	string GetDayName(int number) {
		if (number >= 7 || number <= -1) return "";
		string days[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		return days[number];
	}

	// just returns the date to print
	string PrintDate(short day, short month, short year, string separator) {
		return to_string(day) + separator + to_string(month) + separator + to_string(year);
	}

	// returns the order of the day in week
	// 0->sunday, 1->monday
	short GetDayOrderInWeek(int day, int month, int year) {
		int a = (14 - month) / 12;
		int y = year - a;
		int m = month + 12 * a - 2;

		int d = (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12));

		return d % 7;
	}

	string GetMonthName(int month) {
		if (month <= 0 || month >= 13) return "";
		string months[12] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
		};

		return months[month - 1];
	}

	void PrintMonthCalender(short year, short month) {
		string month_name = GetMonthName(month);
		int month_days = GetDaysInMonth(month, year);
		int break_line = 1;

		cout << printers::PrintNameInMiddleOfDashes(40, month_name, "_");
		cout << "\n\n";

		string Days[7]{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fir", "Sat" };
		for (int i = 0; i < 7; i++) {
			cout << Days[i] << "  ";
		}
		cout << "\n";

		break_line = GetDayOrderInWeek(1, month, year);

		for (int i = 0; i < break_line; i++) {
			cout << printers::FormatedCout(3, "", printers::enPosition::left) << "  ";
		}

		for (int i = 1; i <= month_days; i++) {
			cout << printers::FormatedCout(3, to_string(i), printers::enPosition::left) << "  ";
			break_line++;
			if (break_line % 7 == 0) {
				cout << "\n";
				break_line = 0;
			}
		}
		cout << "\n";
		cout << printers::PrintDashes(40, "_");
		cout << "\n";
	}

	void PrintYearCalender(short year) {

		cout << printers::PrintDashes(40, "_") << "\n\n";
		cout << printers::FormatedCout(40, "Calender - " + to_string(year), printers::enPosition::center) << "\n";
		cout << printers::PrintDashes(40, "_") << "\n\n";

		for (int i = 1; i <= 12; i++) {
			PrintMonthCalender(year, i);
			cout << endl;
		}
	}

	short NumberOfDayInYear(short day, short month, short year) {
		int counter = 0;

		for (int i = 1; i < month; i++) {
			counter += GetDaysInMonth(i, year);
		}

		return (counter + day);
	}

	// just returns the date to print
	string PrintDate(stDate date, string separator) {
		return to_string(date.day) + separator + to_string(date.month) + separator + to_string(date.year);
	}

	// takes the number of day from the beggining of the year
	stDate GetDate(int number_of_day_from_beginning_of_year, int year) {
		stDate date;
		int counter = 0;
		for (int i = 1; i <= 12; i++) {
			number_of_day_from_beginning_of_year -= GetDaysInMonth(i, year);
			counter++;
			if (number_of_day_from_beginning_of_year <= 31) {
				counter++;
				break;
			}
		}
		date.day = number_of_day_from_beginning_of_year;
		date.year = year;
		date.month = counter;

		return date;
	}

	void FillCurrentMonth(stDate& date, int& days_to_add) {
		int current_month_days = GetDaysInMonth(date.month, date.year);
		int remaining_days_to_fill_month = current_month_days - date.day;

		if (days_to_add == 0) return;
		else if (days_to_add <= remaining_days_to_fill_month) {
			date.day += days_to_add;
			days_to_add = 0;
			return;
		}
		else {
			if (remaining_days_to_fill_month == 0) {
				if (date.month == 12) {
					date.month = 1;
					date.year++;
				}
				else {
					date.month++;
				}
				date.day = 0;
				FillCurrentMonth(date, days_to_add);
				return;
			}
			date.day += remaining_days_to_fill_month;
			days_to_add -= remaining_days_to_fill_month;
		}
	}

	void AddDaysToDate(stDate& date, int days_to_add) {
		while (days_to_add != 0) {
			FillCurrentMonth(date, days_to_add);
		}
	}

	stDate CompareDates(stDate date1, stDate date2) {
		int year_diff = date2.year - date1.year;

		if (year_diff > 0) return date2;
		else if (year_diff < 0) return date1;
		else {
			int days_from_beggining1 = NumberOfDayInYear(date1.day, date1.month, date1.year);
			int days_from_beggining2 = NumberOfDayInYear(date2.day, date2.month, date2.year);
			int diff = days_from_beggining2 - days_from_beggining1;
			if (diff > 0) return date2;
			return date1;
		}
	}

	bool IsEqualDates(stDate date1, stDate date2) {
		return (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day);
	}

	bool IsLastDayInMonth(stDate date) {
		return (date.day == GetDaysInMonth(date.month, date.year));
	}
	bool IsLastMonthInYear(stDate date) {
		return (date.month == 12) ? true : false;
	}

	void IncreaseDateByOne(stDate& date) {
		if (IsLastDayInMonth(date)) {
			if (IsLastMonthInYear(date)) {
				date.month = 1;
				date.year++;
				date.day = 1;
			}
			else {
				date.month++;
				date.day = 1;
			}
		}
		else {
			date.day++;
		}
	}

	int DifferentBtwDatesInDays(stDate date1, stDate date2, bool include_last_day = false) {
		if (!IsEqualDates(date2, CompareDates(date1, date2))) {
			return -1 * DifferentBtwDatesInDays(date2, date1, include_last_day);
		}

		int counter = 0;
		while (!IsEqualDates(date1, date2)) {
			counter++;
			IncreaseDateByOne(date1);
		}

		return include_last_day ? counter + 1 : counter;
	}

	int GetDateInDays(stDate date) {
		int days = 0;
		while (date.year != 0) {
			days += NumberOfDaysInYear(date.year--);
		}
		days += NumberOfDayInYear(date.day, date.month, date.year);

		return days;
	}

	stDate GetSystemDate() {
		stDate current_date;
		current_date.year = GetDateTime(enDateTime::year);
		current_date.month = GetDateTime(enDateTime::month);
		current_date.day = GetDateTime(enDateTime::day);
		return current_date;
	}

	void IncreaseDateByXDays(int X, datetime::stDate& date) {
		while (X > 0) {
			datetime::IncreaseDateByOne(date);
			X--;
		}
	}

	void IncreaseDateByOneWeek(stDate& date) {
		IncreaseDateByXDays(7, date);
	}

	void IncreaseDateByXWeeks(int X, stDate& date) {
		while (X > 0) {
			IncreaseDateByOneWeek(date);
			X--;
		}
	}

	void IncreaseDateByOneMonth(datetime::stDate& date) {
		if (datetime::IsLastMonthInYear(date)) {
			date.year++;
			date.month = 1;
		}
		else {
			date.month++;
		}

		int current_month_days = datetime::GetDaysInMonth(date.month, date.year);
		if (date.day > current_month_days) {
			date.day = current_month_days;
		}
	}

	void IncreaseDateByXMonths(int X, datetime::stDate& date) {
		while (X > 0) {
			IncreaseDateByOneMonth(date);
			X--;
		}
	}

	void IncreaseDateByOneYear(datetime::stDate& date) {
		IncreaseDateByXMonths(12, date);
	}

	void IncreaseDateByXYears(int X, datetime::stDate& date) {
		while (X > 0) {
			IncreaseDateByOneYear(date);
			X--;
		}
	}

	void IncreaseDateByXYearsFaster(int X, datetime::stDate& date) {
		while (X > 0) {
			if (datetime::IsLeapYear(date.year + 1)) datetime::IncreaseDateByOne(date);
			date.year++;
			X--;
		}
	}

	void IncreaseDateByOneDecade(datetime::stDate& date) {
		IncreaseDateByXYears(10, date);
	}

	void IncreaseDateByXDecades(int X, datetime::stDate& date) {
		while (X > 0) {
			IncreaseDateByOneDecade(date);
			X--;
		}
	}

	void IncreaseDateByXDecadesFaster(int X, datetime::stDate& date) {
		IncreaseDateByXYearsFaster(X * 10, date);
	}

	void IncreaseDateByOneCentury(datetime::stDate& date) {
		IncreaseDateByXDecadesFaster(10, date);
	}

	void IncreaseDateByOneMillennuim(datetime::stDate& date) {
		for (int i = 1; i <= 10; i++) IncreaseDateByOneCentury(date);
	}

	void DecreaseDateByOne(datetime::stDate& date) {
		if (date.day == 1) {
			if (date.month == 1) {
				date.year--;
				date.month = 12;
				date.day = datetime::GetDaysInMonth(date.month, date.year);
			}
			else {
				date.month--;
				date.day = datetime::GetDaysInMonth(date.month, date.year);
			}
		}
		else {
			date.day--;
		}
	}

	void DecreaseDateByXDays(int X, datetime::stDate& date) {
		while (X > 0) {
			DecreaseDateByOne(date);
			X--;
		}
	}

	void DecreaseDateByOneWeek(datetime::stDate& date) {
		DecreaseDateByXDays(7, date);
	}

	void DecreaseDateByXWeeks(int X, datetime::stDate& date) {
		while (X > 0) {
			DecreaseDateByOneWeek(date);
			X--;
		}
	}

	void DecreaseDateByOneMonth(datetime::stDate& date) {
		if (date.month == 1) {
			date.year--;
			date.month = 12;
		}
		else {
			date.month--;
		}

		int current_month_days = datetime::GetDaysInMonth(date.month, date.year);
		if (date.day > current_month_days) {
			date.day = current_month_days;
		}
	}

	void DecreaseDateByXMonths(int X, datetime::stDate& date) {
		while (X > 0) {
			DecreaseDateByOneMonth(date);
			X--;
		}
	}

	void DecreaseDateByOneYear(datetime::stDate& date) {
		DecreaseDateByXMonths(12, date);
	}

	void DecreaseDateByXYears(int X, datetime::stDate& date) {
		while (X > 0) {
			DecreaseDateByOneYear(date);
			X--;
		}
	}

	void DecreaseDateByXYearsFaster(int X, datetime::stDate& date) {
		while (X > 0) {
			if (datetime::IsLeapYear(date.year - 1)) DecreaseDateByOne(date);
			date.year--;
			X--;
		}
	}

	void DecreaseDateByOneDecade(datetime::stDate& date) {
		DecreaseDateByXYears(10, date);
	}

	void DecreaseDateByXDecades(int X, datetime::stDate& date) {
		while (X > 0) {
			DecreaseDateByOneDecade(date);
			X--;
		}
	}

	void DecreaseDateByXDecadesFaster(int X, datetime::stDate& date) {
		DecreaseDateByXYearsFaster(X * 10, date);
	}

	void DecreaseDateByOneCentury(datetime::stDate& date) {
		DecreaseDateByXDecadesFaster(10, date);
	}

	void DecreaseDateByOneMillennuim(datetime::stDate& date) {
		for (int i = 1; i <= 10; i++) DecreaseDateByOneCentury(date);
	}

	int DayOfWeekOrder(datetime::stDate date) {
		return datetime::GetDayOrderInWeek(date.day, date.month, date.year);
	}

	string PrintDateLong(datetime::stDate date) {
		return datetime::GetDayName(DayOfWeekOrder(date)) + " , " + datetime::PrintDate(date, "/");
	}

	bool IsEndOfWeek(datetime::stDate date) {
		return DayOfWeekOrder(date) == 6;
	}

	bool IsItWeekend(datetime::stDate date) {
		int day_order = DayOfWeekOrder(date);
		return (day_order == 6 || day_order == 5);
	}

	bool IsBusinessDay(datetime::stDate date) {
		return !IsItWeekend(date);
	}

	int DaysUntilTheEndOfWeek(datetime::stDate date) {
		return (6 - DayOfWeekOrder(date));
	}

	int DaysUntilTheEndOfMonth(datetime::stDate date) {
		datetime::stDate last_day_date;

		last_day_date.day = datetime::GetDaysInMonth(date.month, date.year);
		last_day_date.month = date.month;
		last_day_date.year = date.year;

		return datetime::DifferentBtwDatesInDays(date, last_day_date, true);
	}

	int DaysUntilTheEndOfYear(datetime::stDate date) {
		return (datetime::NumberOfDaysInYear(date.year) - datetime::NumberOfDayInYear(date.day, date.month, date.year));
	}

	int GetWeekendDays(datetime::stDate date1, datetime::stDate date2) {
		if (!datetime::IsEqualDates(date2, datetime::CompareDates(date1, date2))) return 0;

		int weekend_days = 0;

		while (!datetime::IsEqualDates(date1, date2)) {
			if (datetime::IsItWeekend(date1)) weekend_days++;
			datetime::IncreaseDateByOne(date1);
		}
		return weekend_days;
	}

	int GetBusinessDays(datetime::stDate date1, datetime::stDate date2) {
		return datetime::DifferentBtwDatesInDays(date1, date2) - GetWeekendDays(date1, date2);
	}

	int GetVacationDays(datetime::stDate date1, datetime::stDate date2) {
		return GetBusinessDays(date1, date2);
	}

	datetime::stDate EndOfVacation(datetime::stDate startDate, short duration) {
		datetime::stDate end_date = startDate;

		while (duration != datetime::GetVacationDays(startDate, end_date))
			datetime::IncreaseDateByOne(end_date);

		return end_date;
	}

	bool IsDate1AfterDate2(datetime::stDate date1, datetime::stDate date2) {
		return (!datetime::IsEqualDates(date1, date2) && datetime::IsEqualDates(date1, datetime::CompareDates(date1, date2)));
	}

	bool IsDate1BeforeDate2(datetime::stDate date1, datetime::stDate date2) {
		return (!datetime::IsEqualDates(date1, date2) && datetime::IsEqualDates(date2, datetime::CompareDates(date1, date2)));
	}

	int CompareDates2(datetime::stDate date1, datetime::stDate date2) {
		return datetime::IsEqualDates(date1, date2) ? 0 :
			datetime::IsDate1AfterDate2(date1, date2) ? 1 : -1;
	}
	bool IsOverlapedPeriods(stPeriod period1, stPeriod period2) {
		return !(datetime::IsDate1BeforeDate2(period1.endDate, period2.starDate) ||
			datetime::IsDate1BeforeDate2(period2.endDate, period1.starDate));
	}

	string PrintPeriod(stPeriod period) {
		return datetime::PrintDate(period.starDate, "/") + " ~~ " + datetime::PrintDate(period.endDate, "/");
	}

	stPeriod ReadPeriod() {
		stPeriod period;
		cout << "Filling a period:" << "\n";
		cout << "Filling start date:" << "\n\n";

		cout << "Enter a date: ";
		cin >> period.starDate.day;

		cout << "Enter a month: ";
		cin >> period.starDate.month;

		cout << "Enter a year: ";
		cin >> period.starDate.year;
		cout << "\n";

		cout << "Filling end date:" << "\n\n";

		cout << "Enter a date: ";
		cin >> period.endDate.day;

		cout << "Enter a month: ";
		cin >> period.endDate.month;

		cout << "Enter a year: ";
		cin >> period.endDate.year;
		cout << "\n";

		return period;
	}

	int PeriodLengthInDays(datetime::stPeriod period, bool include_last_day = false) {
		return datetime::DifferentBtwDatesInDays(period.starDate, period.endDate, include_last_day);
	}

	bool IsDateWithinPeriod(datetime::stDate date, datetime::stPeriod period) {
		return !(datetime::IsDate1BeforeDate2(date, period.starDate) || datetime::IsDate1AfterDate2(date, period.endDate));
	}

	// this function calculate approximatly the diff btw the years
	int PeriodLengthInYears(datetime::stPeriod period) {
		return abs(period.starDate.year - period.endDate.year);
	}

	void SwitchPeriods(datetime::stPeriod& period1, datetime::stPeriod& period2) {
		datetime::stPeriod aux_period = period1;
		period1 = period2;
		period2 = aux_period;
	}

	int CountOverlapDays(datetime::stPeriod period1, datetime::stPeriod period2) {
		if (!datetime::IsOverlapedPeriods(period1, period2)) return 0;

		int years_length1 = PeriodLengthInYears(period1);
		int years_length2 = PeriodLengthInYears(period2);

		if (years_length1 > years_length2) SwitchPeriods(period1, period2);


		datetime::stDate date = period1.starDate;
		int overlaped_days = 0;


		while (!datetime::IsEqualDates(date, period1.endDate)) {
			if (datetime::IsDateWithinPeriod(date, period2)) overlaped_days++;
			datetime::IncreaseDateByOne(date);
		}
		if (datetime::IsDateWithinPeriod(date, period2)) overlaped_days++;

		return overlaped_days;
	}

	stDate ReadDate() {
		stDate date;
		date.day = readers::ReadNumber("Enter the day: ");
		date.month = readers::ReadNumber("Enter the month: ");
		date.year = readers::ReadNumber("Enter the year: ");
		return date;
	}

	bool ValidateDate(datetime::stDate date) {
		if (!(date.month >= 1 && date.month <= 12)) return false;
		if (date.year <= 0) return false;
		if (!(date.day >= 1 && date.day <= GetDaysInMonth(date.month, date.year))) return false;
		return true;
	}
	datetime::stDate StringToDate(string str_date) {
		vector<string> vec_date = manipulators::string_utilities::Split(str_date, "/");

		datetime::stDate date;
		date.day = stoi(vec_date[0]);
		date.month = stoi(vec_date[1]);
		date.year = stoi(vec_date[2]);

		return date;
	}

	string DateToString(datetime::stDate date) {
		return datetime::PrintDate(date, "/");
	}

	datetime::stDate ReadDateAsString() {
		string str_date = "";
		datetime::stDate date;

		cout << "Please enter date dd/mm/yyyy: ";
		cin >> str_date;

		date = StringToDate(str_date);
		return date;
	}

	enum enFormatString {
		day_month_year_forward_slash,
		year_day_month_forward_slash,
		month_day_year_forward_slash,
		day_month_year_dash,
		year_day_month_dash,
		month_day_year_dash,
		details
	};
	string FormatDate(datetime::stDate date, enFormatString format) {
		switch (format) {
		case enFormatString::day_month_year_forward_slash: return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
		case enFormatString::year_day_month_forward_slash: return to_string(date.year) + "/" + to_string(date.day) + "/" + to_string(date.month);
		case enFormatString::month_day_year_forward_slash: return to_string(date.month) + "/" + to_string(date.day) + "/" + to_string(date.year);
		case enFormatString::day_month_year_dash: return to_string(date.day) + "-" + to_string(date.month) + "-" + to_string(date.year);
		case enFormatString::year_day_month_dash: return to_string(date.year) + "-" + to_string(date.day) + "-" + to_string(date.month);
		case enFormatString::month_day_year_dash: return to_string(date.month) + "-" + to_string(date.day) + "-" + to_string(date.year);
		default: return "Day:" + to_string(date.month) + ", Month:" + to_string(date.day) + ", Year:" + to_string(date.year);
		};
	}

	string FormatDate(datetime::stDate date, string date_formated = "dd/mm/yyyy") {
		date_formated = manipulators::string_utilities::ReplaceWordInStringWithBuiltInFunction(date_formated, "dd", to_string(date.day));
		date_formated = manipulators::string_utilities::ReplaceWordInStringWithBuiltInFunction(date_formated, "mm", to_string(date.month));
		date_formated = manipulators::string_utilities::ReplaceWordInStringWithBuiltInFunction(date_formated, "yyyy", to_string(date.year));
		return date_formated;
	}
}