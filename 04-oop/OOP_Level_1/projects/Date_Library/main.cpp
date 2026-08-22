#include "clsDate.h"

using namespace std;

int main(void)
{
    cout << boolalpha;

    cout << "\n========== Constructors / Getters / Setters ==========\n";

    clsDate Date1;
    cout << "Default/System Date: ";
    Date1.Print();

    clsDate Date2("15/8/2026");
    cout << "String Constructor: ";
    Date2.Print();

    clsDate Date3(20, 12, 2025);
    cout << "Day/Month/Year Constructor: ";
    Date3.Print();

    Date3.SetDay(21);
    Date3.SetMonth(11);
    Date3.SetYear(2024);

    cout << "GetDay(): " << Date3.GetDay() << endl;
    cout << "GetMonth(): " << Date3.GetMonth() << endl;
    cout << "GetYear(): " << Date3.GetYear() << endl;


    cout << "\n========== System Date / Date To String ==========\n";

    clsDate SystemDate = clsDate::GetSystemDate();
    cout << "GetSystemDate(): " << clsDate::DateToString(SystemDate) << endl;
    cout << "Static DateToString(): " << clsDate::DateToString(Date2) << endl;
    cout << "Member DateToString(): " << Date2.DateToString() << endl;


    cout << "\n========== Leap Year ==========\n";

    cout << "isLeapYear(2024): " << clsDate::isLeapYear(2024) << endl;

    clsDate LeapDate(1, 1, 2024);
    cout << "Member isLeapYear(): " << LeapDate.isLeapYear() << endl;


    cout << "\n========== Year Calculations ==========\n";

    cout << "NumberOfDaysInAYear(2024): "
         << clsDate::NumberOfDaysInAYear(2024) << endl;
    cout << "Member NumberOfDaysInAYear(): "
         << LeapDate.NumberOfDaysInAYear() << endl;

    cout << "NumberOfHoursInAYear(2024): "
         << clsDate::NumberOfHoursInAYear(2024) << endl;
    cout << "Member NumberOfHoursInAYear(): "
         << LeapDate.NumberOfHoursInAYear() << endl;

    cout << "NumberOfMinutesInAYear(2024): "
         << clsDate::NumberOfMinutesInAYear(2024) << endl;
    cout << "Member NumberOfMinutesInAYear(): "
         << LeapDate.NumberOfMinutesInAYear() << endl;

    cout << "NumberOfSecondsInAYear(2024): "
         << clsDate::NumberOfSecondsInAYear(2024) << endl;
    cout << "Member NumberOfSecondsInAYear(): "
         << LeapDate.NumberOfSecondsInAYear() << endl;


    cout << "\n========== Month Calculations ==========\n";

    clsDate MonthDate(1, 2, 2024);

    cout << "NumberOfDaysInAMonth(2, 2024): "
         << clsDate::NumberOfDaysInAMonth(2, 2024) << endl;
    cout << "Member NumberOfDaysInAMonth(): "
         << MonthDate.NumberOfDaysInAMonth() << endl;

    cout << "NumberOfHoursInAMonth(2, 2024): "
         << clsDate::NumberOfHoursInAMonth(2, 2024) << endl;
    cout << "Member NumberOfHoursInAMonth(): "
         << MonthDate.NumberOfHoursInAMonth() << endl;

    cout << "NumberOfMinutesInAMonth(2, 2024): "
         << clsDate::NumberOfMinutesInAMonth(2, 2024) << endl;
    cout << "Member NumberOfMinutesInAMonth(): "
         << MonthDate.NumberOfMinutesInAMonth() << endl;

    cout << "NumberOfSecondsInAMonth(2, 2024): "
         << clsDate::NumberOfSecondsInAMonth(2, 2024) << endl;
    cout << "Member NumberOfSecondsInAMonth(): "
         << MonthDate.NumberOfSecondsInAMonth() << endl;


    cout << "\n========== Date Validation ==========\n";

    clsDate ValidDate(29, 2, 2024);
    clsDate InvalidDate(30, 2, 2024);

    cout << "IsValidDate(29/2/2024): "
         << clsDate::IsValidDate(ValidDate) << endl;
    cout << "IsValidDate(30/2/2024): "
         << clsDate::IsValidDate(InvalidDate) << endl;
    cout << "Member IsValid(): " << ValidDate.IsValid() << endl;


    cout << "\n========== Day Of Week / Names ==========\n";

    clsDate WeekDate(14, 8, 2026);

    cout << "DayOfWeekOrder(14, 8, 2026): "
         << clsDate::DayOfWeekOrder(14, 8, 2026) << endl;
    cout << "Member DayOfWeekOrder(): "
         << WeekDate.DayOfWeekOrder() << endl;

    cout << "DayShortName(5): "
         << clsDate::DayShortName(5) << endl;
    cout << "DayShortName(14, 8, 2026): "
         << clsDate::DayShortName(14, 8, 2026) << endl;
    cout << "Member DayShortName(): "
         << WeekDate.DayShortName() << endl;

    cout << "MonthShortName(8): "
         << clsDate::MonthShortName(8) << endl;
    cout << "Member MonthShortName(): "
         << WeekDate.MonthShortName() << endl;


    cout << "\n========== Calendars ==========\n";

    cout << "\nStatic PrintMonthCalendar(8, 2026):\n";
    clsDate::PrintMonthCalendar(8, 2026);

    cout << "\nMember PrintMonthCalendar():\n";
    WeekDate.PrintMonthCalendar();

    cout << "\nStatic PrintYearCalendar(2026):\n";
    clsDate::PrintYearCalendar(2026);

    cout << "\nMember PrintYearCalendar():\n";
    WeekDate.PrintYearCalendar();


    cout << "\n========== Day Order In Year ==========\n";

    cout << "DaysFromTheBeginingOfTheYear(14, 8, 2026): "
         << clsDate::DaysFromTheBeginingOfTheYear(14, 8, 2026) << endl;
    cout << "Member DaysFromTheBeginingOfTheYear(): "
         << WeekDate.DaysFromTheBeginingOfTheYear() << endl;

    clsDate DateFromOrder = clsDate::GetDateFromDayOrderInYear(226, 2026);
    cout << "GetDateFromDayOrderInYear(226, 2026): "
         << DateFromOrder.DateToString() << endl;


    cout << "\n========== Add Days ==========\n";

    clsDate AddDaysDate(14, 8, 2026);
    cout << "Before AddDays(10): " << AddDaysDate.DateToString() << endl;
    AddDaysDate.AddDays(10);
    cout << "After AddDays(10): " << AddDaysDate.DateToString() << endl;


    cout << "\n========== Date Comparison ==========\n";

    clsDate CompareDate1(10, 8, 2026);
    clsDate CompareDate2(20, 8, 2026);
    clsDate CompareDate3(10, 8, 2026);

    cout << "IsDate1BeforeDate2(): "
         << clsDate::IsDate1BeforeDate2(CompareDate1, CompareDate2) << endl;
    cout << "Member IsDateBeforeDate2(): "
         << CompareDate1.IsDateBeforeDate2(CompareDate2) << endl;

    cout << "IsDate1EqualDate2(): "
         << clsDate::IsDate1EqualDate2(CompareDate1, CompareDate3) << endl;
    cout << "Member IsDateEqualDate2(): "
         << CompareDate1.IsDateEqualDate2(CompareDate3) << endl;

    cout << "IsDate1AfterDate2(): "
         << clsDate::IsDate1AfterDate2(CompareDate2, CompareDate1) << endl;
    cout << "Member IsDateAfterDate2(): "
         << CompareDate2.IsDateAfterDate2(CompareDate1) << endl;


    cout << "\n========== Last Day / Last Month ==========\n";

    clsDate LastDayDate(31, 8, 2026);

    cout << "IsLastDayInMonth(): "
         << clsDate::IsLastDayInMonth(LastDayDate) << endl;
    cout << "Member IsLastDayInMonth(): "
         << LastDayDate.IsLastDayInMonth() << endl;
    cout << "IsLastMonthInYear(12): "
         << clsDate::IsLastMonthInYear(12) << endl;


    cout << "\n========== Add One Day ==========\n";

    clsDate OneDayDate(31, 12, 2025);
    clsDate NextDate = clsDate::AddOneDay(OneDayDate);
    cout << "Static AddOneDay(31/12/2025): "
         << NextDate.DateToString() << endl;

    OneDayDate.AddOneDay();
    cout << "Member AddOneDay(): "
         << OneDayDate.DateToString() << endl;


    cout << "\n========== Swap Dates ==========\n";

    clsDate SwapDate1(1, 1, 2025);
    clsDate SwapDate2(31, 12, 2026);

    cout << "Before Swap: " << SwapDate1.DateToString()
         << " | " << SwapDate2.DateToString() << endl;

    clsDate::SwapDates(SwapDate1, SwapDate2);

    cout << "After Swap:  " << SwapDate1.DateToString()
         << " | " << SwapDate2.DateToString() << endl;


    cout << "\n========== Difference In Days ==========\n";

    clsDate DiffDate1(1, 8, 2026);
    clsDate DiffDate2(14, 8, 2026);

    cout << "Static GetDifferenceInDays(): "
         << clsDate::GetDifferenceInDays(DiffDate1, DiffDate2) << endl;
    cout << "Static GetDifferenceInDays(include end day): "
         << clsDate::GetDifferenceInDays(DiffDate1, DiffDate2, true) << endl;
    cout << "Member GetDifferenceInDays(): "
         << DiffDate1.GetDifferenceInDays(DiffDate2) << endl;


    cout << "\n========== Age In Days ==========\n";

    clsDate BirthDate(1, 1, 2000);
    cout << "CalculateMyAgeInDays(1/1/2000): "
         << clsDate::CalculateMyAgeInDays(BirthDate) << endl;


    cout << "\n========== Increase Dates ==========\n";

    clsDate IncreaseDate1(1, 1, 2026);
    clsDate::IncreaseDateByOneWeek(IncreaseDate1);
    cout << "Static IncreaseDateByOneWeek(): "
         << IncreaseDate1.DateToString() << endl;

    clsDate IncreaseDate2(1, 1, 2026);
    IncreaseDate2.IncreaseDateByOneWeek();
    cout << "Member IncreaseDateByOneWeek(): "
         << IncreaseDate2.DateToString() << endl;

    clsDate IncreaseDate3(1, 1, 2026);
    IncreaseDate3.IncreaseDateByXWeeks(3, IncreaseDate3);
    cout << "IncreaseDateByXWeeks(3, Date): "
         << IncreaseDate3.DateToString() << endl;

    clsDate IncreaseDate4(1, 1, 2026);
    IncreaseDate4.IncreaseDateByXWeeks(3);
    cout << "Member IncreaseDateByXWeeks(3): "
         << IncreaseDate4.DateToString() << endl;

    clsDate IncreaseDate5(31, 1, 2026);
    IncreaseDate5.IncreaseDateByOneMonth(IncreaseDate5);
    cout << "IncreaseDateByOneMonth(Date): "
         << IncreaseDate5.DateToString() << endl;

    clsDate IncreaseDate6(31, 1, 2026);
    IncreaseDate6.IncreaseDateByOneMonth();
    cout << "Member IncreaseDateByOneMonth(): "
         << IncreaseDate6.DateToString() << endl;

    clsDate IncreaseDate7(1, 1, 2026);
    IncreaseDate7.IncreaseDateByXDays(10, IncreaseDate7);
    cout << "IncreaseDateByXDays(10, Date): "
         << IncreaseDate7.DateToString() << endl;

    clsDate IncreaseDate8(1, 1, 2026);
    IncreaseDate8.IncreaseDateByXDays(10);
    cout << "Member IncreaseDateByXDays(10): "
         << IncreaseDate8.DateToString() << endl;

    clsDate IncreaseDate9(1, 1, 2026);
    IncreaseDate9.IncreaseDateByXMonths(3, IncreaseDate9);
    cout << "IncreaseDateByXMonths(3, Date): "
         << IncreaseDate9.DateToString() << endl;

    clsDate IncreaseDate10(1, 1, 2026);
    IncreaseDate10.IncreaseDateByXMonths(3);
    cout << "Member IncreaseDateByXMonths(3): "
         << IncreaseDate10.DateToString() << endl;

    clsDate IncreaseDate11(1, 1, 2026);
    clsDate::IncreaseDateByOneYear(IncreaseDate11);
    cout << "Static IncreaseDateByOneYear(): "
         << IncreaseDate11.DateToString() << endl;

    clsDate IncreaseDate12(1, 1, 2026);
    IncreaseDate12.IncreaseDateByOneYear();
    cout << "Member IncreaseDateByOneYear(): "
         << IncreaseDate12.DateToString() << endl;

    clsDate IncreaseDate13(1, 1, 2026);
    IncreaseDate13.IncreaseDateByXYears(5, IncreaseDate13);
    cout << "IncreaseDateByXYears(5, Date): "
         << IncreaseDate13.DateToString() << endl;

    clsDate IncreaseDate13Member(1, 1, 2026);
    IncreaseDate13Member.IncreaseDateByXYears(5);
    cout << "Member IncreaseDateByXYears(5): "
         << IncreaseDate13Member.DateToString() << endl;

    clsDate IncreaseDate14(1, 1, 2026);
    IncreaseDate14.IncreaseDateByOneDecade(IncreaseDate14);
    cout << "IncreaseDateByOneDecade(Date): "
         << IncreaseDate14.DateToString() << endl;

    clsDate IncreaseDate15(1, 1, 2026);
    IncreaseDate15.IncreaseDateByOneDecade();
    cout << "Member IncreaseDateByOneDecade(): "
         << IncreaseDate15.DateToString() << endl;

    clsDate IncreaseDate16(1, 1, 2026);
    IncreaseDate16.IncreaseDateByXDecades(3, IncreaseDate16);
    cout << "IncreaseDateByXDecades(3, Date): "
         << IncreaseDate16.DateToString() << endl;

    clsDate IncreaseDate17(1, 1, 2026);
    IncreaseDate17.IncreaseDateByXDecades(3);
    cout << "Member IncreaseDateByXDecades(3): "
         << IncreaseDate17.DateToString() << endl;

    clsDate IncreaseDate18(1, 1, 2026);
    IncreaseDate18.IncreaseDateByOneCentury(IncreaseDate18);
    cout << "IncreaseDateByOneCentury(Date): "
         << IncreaseDate18.DateToString() << endl;

    clsDate IncreaseDate19(1, 1, 2026);
    IncreaseDate19.IncreaseDateByOneCentury();
    cout << "Member IncreaseDateByOneCentury(): "
         << IncreaseDate19.DateToString() << endl;

    clsDate IncreaseDate20(1, 1, 2026);
    IncreaseDate20.IncreaseDateByOneMillennium(IncreaseDate20);
    cout << "IncreaseDateByOneMillennium(Date): "
         << IncreaseDate20.DateToString() << endl;

    clsDate IncreaseDate21(1, 1, 2026);
    IncreaseDate21.IncreaseDateByOneMillennium();
    cout << "Member IncreaseDateByOneMillennium(): "
         << IncreaseDate21.DateToString() << endl;


    cout << "\n========== Decrease Dates ==========\n";

    clsDate DecreaseDate1(1, 1, 2026);
    clsDate PreviousDate = clsDate::DecreaseDateByOneDay(DecreaseDate1);
    cout << "Static DecreaseDateByOneDay(): "
         << PreviousDate.DateToString() << endl;

    clsDate DecreaseDate2(2, 1, 2026);
    DecreaseDate2.DecreaseDateByOneDay();
    cout << "Member DecreaseDateByOneDay(): "
         << DecreaseDate2.DateToString() << endl;

    clsDate DecreaseDate3(14, 1, 2026);
    clsDate::DecreaseDateByOneWeek(DecreaseDate3);
    cout << "Static DecreaseDateByOneWeek(): "
         << DecreaseDate3.DateToString() << endl;

    clsDate DecreaseDate4(14, 1, 2026);
    DecreaseDate4.DecreaseDateByOneWeek();
    cout << "Member DecreaseDateByOneWeek(): "
         << DecreaseDate4.DateToString() << endl;

    clsDate DecreaseDate5(1, 2, 2026);
    clsDate::DecreaseDateByXWeeks(2, DecreaseDate5);
    cout << "Static DecreaseDateByXWeeks(2): "
         << DecreaseDate5.DateToString() << endl;

    clsDate DecreaseDate6(1, 2, 2026);
    DecreaseDate6.DecreaseDateByXWeeks(2);
    cout << "Member DecreaseDateByXWeeks(2): "
         << DecreaseDate6.DateToString() << endl;

    clsDate DecreaseDate7(31, 3, 2026);
    clsDate::DecreaseDateByOneMonth(DecreaseDate7);
    cout << "Static DecreaseDateByOneMonth(): "
         << DecreaseDate7.DateToString() << endl;

    clsDate DecreaseDate8(31, 3, 2026);
    DecreaseDate8.DecreaseDateByOneMonth();
    cout << "Member DecreaseDateByOneMonth(): "
         << DecreaseDate8.DateToString() << endl;

    clsDate DecreaseDate9(20, 1, 2026);
    clsDate::DecreaseDateByXDays(10, DecreaseDate9);
    cout << "Static DecreaseDateByXDays(10): "
         << DecreaseDate9.DateToString() << endl;

    clsDate DecreaseDate10(20, 1, 2026);
    DecreaseDate10.DecreaseDateByXDays(10);
    cout << "Member DecreaseDateByXDays(10): "
         << DecreaseDate10.DateToString() << endl;

    clsDate DecreaseDate11(1, 6, 2026);
    clsDate::DecreaseDateByXMonths(3, DecreaseDate11);
    cout << "Static DecreaseDateByXMonths(3): "
         << DecreaseDate11.DateToString() << endl;

    clsDate DecreaseDate12(1, 6, 2026);
    DecreaseDate12.DecreaseDateByXMonths(3);
    cout << "Member DecreaseDateByXMonths(3): "
         << DecreaseDate12.DateToString() << endl;

    clsDate DecreaseDate13(1, 1, 2026);
    clsDate::DecreaseDateByOneYear(DecreaseDate13);
    cout << "Static DecreaseDateByOneYear(): "
         << DecreaseDate13.DateToString() << endl;

    clsDate DecreaseDate14(1, 1, 2026);
    DecreaseDate14.DecreaseDateByOneYear();
    cout << "Member DecreaseDateByOneYear(): "
         << DecreaseDate14.DateToString() << endl;

    clsDate DecreaseDate15(1, 1, 2026);
    clsDate::DecreaseDateByXYears(5, DecreaseDate15);
    cout << "Static DecreaseDateByXYears(5): "
         << DecreaseDate15.DateToString() << endl;

    clsDate DecreaseDate16(1, 1, 2026);
    DecreaseDate16.DecreaseDateByXYears(5);
    cout << "Member DecreaseDateByXYears(5): "
         << DecreaseDate16.DateToString() << endl;

    clsDate DecreaseDate17(1, 1, 2026);
    clsDate::DecreaseDateByOneDecade(DecreaseDate17);
    cout << "Static DecreaseDateByOneDecade(): "
         << DecreaseDate17.DateToString() << endl;

    clsDate DecreaseDate18(1, 1, 2026);
    DecreaseDate18.DecreaseDateByOneDecade();
    cout << "Member DecreaseDateByOneDecade(): "
         << DecreaseDate18.DateToString() << endl;

    clsDate DecreaseDate19(1, 1, 2026);
    clsDate::DecreaseDateByXDecades(3, DecreaseDate19);
    cout << "Static DecreaseDateByXDecades(3): "
         << DecreaseDate19.DateToString() << endl;

    clsDate DecreaseDate20(1, 1, 2026);
    DecreaseDate20.DecreaseDateByXDecades(3);
    cout << "Member DecreaseDateByXDecades(3): "
         << DecreaseDate20.DateToString() << endl;

    clsDate DecreaseDate21(1, 1, 2026);
    clsDate::DecreaseDateByOneCentury(DecreaseDate21);
    cout << "Static DecreaseDateByOneCentury(): "
         << DecreaseDate21.DateToString() << endl;

    clsDate DecreaseDate22(1, 1, 2026);
    DecreaseDate22.DecreaseDateByOneCentury();
    cout << "Member DecreaseDateByOneCentury(): "
         << DecreaseDate22.DateToString() << endl;

    clsDate DecreaseDate23(1, 1, 2026);
    clsDate::DecreaseDateByOneMillennium(DecreaseDate23);
    cout << "Static DecreaseDateByOneMillennium(): "
         << DecreaseDate23.DateToString() << endl;

    clsDate DecreaseDate24(1, 1, 2026);
    DecreaseDate24.DecreaseDateByOneMillennium();
    cout << "Member DecreaseDateByOneMillennium(): "
         << DecreaseDate24.DateToString() << endl;


    cout << "\n========== Week / Business Day ==========\n";

    clsDate BusinessDate(14, 8, 2026);

    cout << "Static IsEndOfWeek(): "
         << clsDate::IsEndOfWeek(BusinessDate) << endl;
    cout << "Member IsEndOfWeek(): "
         << BusinessDate.IsEndOfWeek() << endl;

    cout << "Static IsWeekEnd(): "
         << clsDate::IsWeekEnd(BusinessDate) << endl;
    cout << "Member IsWeekEnd(): "
         << BusinessDate.IsWeekEnd() << endl;

    cout << "Static IsBusinessDay(): "
         << clsDate::IsBusinessDay(BusinessDate) << endl;
    cout << "Member IsBusinessDay(): "
         << BusinessDate.IsBusinessDay() << endl;

    cout << "Static DaysUntilTheEndOfWeek(): "
         << clsDate::DaysUntilTheEndOfWeek(BusinessDate) << endl;
    cout << "Member DaysUntilTheEndOfWeek(): "
         << BusinessDate.DaysUntilTheEndOfWeek() << endl;

    cout << "Static DaysUntilTheEndOfMonth(): "
         << clsDate::DaysUntilTheEndOfMonth(BusinessDate) << endl;
    cout << "Member DaysUntilTheEndOfMonth(): "
         << BusinessDate.DaysUntilTheEndOfMonth() << endl;

    cout << "Static DaysUntilTheEndOfYear(): "
         << clsDate::DaysUntilTheEndOfYear(BusinessDate) << endl;
    cout << "Member DaysUntilTheEndOfYear(): "
         << BusinessDate.DaysUntilTheEndOfYear() << endl;


    cout << "\n========== Business / Vacation Days ==========\n";

    clsDate VacationFrom(1, 8, 2026);
    clsDate VacationTo(14, 8, 2026);

    cout << "CalculateBusinessDays(): "
         << clsDate::CalculateBusinessDays(VacationFrom, VacationTo) << endl;
    cout << "CalculateVacationDays(): "
         << clsDate::CalculateVacationDays(VacationFrom, VacationTo) << endl;

    clsDate VacationReturnDate =
        clsDate::CalculateVacationReturnDate(VacationFrom, 10);

    cout << "CalculateVacationReturnDate(): "
         << VacationReturnDate.DateToString() << endl;


    cout << "\n========== CompareDates Enum ==========\n";

    cout << "Static CompareDates(Date1, Date2): "
         << clsDate::CompareDates(CompareDate1, CompareDate2) << endl;
    cout << "Member CompareDates(Date2): "
         << CompareDate1.CompareDates(CompareDate2) << endl;


    return (0);
}
