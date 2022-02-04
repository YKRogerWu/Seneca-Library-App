// Final Project Milestone 1 
// Date Module
// File	Date.cpp
// Version 1.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2021/10/29		   Preliminary release
// Roger              2021/11/20           See the note 1,2
// Roger              2021/11/27           3.Modify read()
// Roger              2021/11/29           4. Optimize read()
// -----------------------------------------------------------
// 1. Updated functions: systemYear, setToToday, read
// 2. Adding 4 global variables
// 3. read function turns istr into fail state if m_date invalid
// 4. read method is optimized to better match Book module
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include "Date.h"

using namespace std;
namespace sdds 
{
    bool sdds_test = false;
    int sdds_year = 2021;
    int sdds_mon = 12;
    int sdds_day = 25;

   bool Date::validate() {
      errCode(NO_ERROR);
      if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1) {
         errCode(YEAR_ERROR);
      }
      else if (m_mon < 1 || m_mon > 12) {
         errCode(MON_ERROR);
      }
      else if (m_day < 1 || m_day > mdays()) {
         errCode(DAY_ERROR);
      }
      return !bad(); //return false for invalid input
   }
   int Date::mdays()const { 
       //returns the number of days in current month (the month stored in m_mon attribute)
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
      mon--;
      return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
   }
   int Date::systemYear()const {
       int theYear = sdds_year;
       if (!sdds_test) {
           time_t t = time(NULL);
           tm lt = *localtime(&t);
           theYear = lt.tm_year + 1900;
       }
       return theYear;
   }
   void Date::setToToday() {
       if (sdds_test) {
           m_day = sdds_day;
           m_mon = sdds_mon;
           m_year = sdds_year;
       }
       else {
           time_t t = time(NULL);
           tm lt = *localtime(&t);
           m_day = lt.tm_mday;
           m_mon = lt.tm_mon + 1;
           m_year = lt.tm_year + 1900;
       }
       errCode(NO_ERROR);
   }
   int Date::daysSince0001_1_1()const {
       //returns number of days passed since the date 0001 / 1 / 1
      int ty = m_year;
      int tm = m_mon;
      if (tm < 3) {
         ty--;
         tm += 12;
      }
      return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
   }
   Date::Date() :m_CUR_YEAR(systemYear()) {
      setToToday();
   }
   Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear()) {
      m_year = year;
      m_mon = mon;
      m_day = day;
      validate();
   }
   const char* Date::dateStatus()const {
      return DATE_ERROR[errCode()];
   }
   int Date::currentYear()const {
      return m_CUR_YEAR;
   }
   void Date::errCode(int readErrorCode) {
      m_ErrorCode = readErrorCode;
   }
   int Date::errCode()const {
      return m_ErrorCode;
   }
   bool Date::bad()const {
      return m_ErrorCode != 0;
   }
   istream& Date::read(istream& is)
   {       
       errCode(NO_ERROR);
       //prompt user to input a date and start reading from the buffer
       is >> m_year;
       is.ignore();
       is >> m_mon;
       is.ignore();
       is >> m_day;
       is.ignore();

           
       if (is.fail()) {
           errCode(CIN_FAILED);
           is.clear();
       }
       if (!validate()) {
           is.setstate(ios::failbit);
       }       
       return is;
   }
   ostream& Date::write(ostream& os)const
   {
       if (bad()){
           os << dateStatus();
       }
       else {
           os << m_year;
           os << '/';
           os << setw(2) << setfill('0') << m_mon;
           os << '/';
           os << setw(2) << setfill('0') << m_day;
       }
       return os;
   }

   bool Date::operator!() {
       return m_ErrorCode != 0;
   }
   int Date::operator-(const Date& right)const {
       return daysSince0001_1_1() - right.daysSince0001_1_1();
   }
   bool Date::operator==(const Date& right)const{
       return daysSince0001_1_1() - right.daysSince0001_1_1() == 0;
   }
   bool Date::operator!=(const Date& right)const{
       return !operator==(right);
   }
   bool Date::operator>(const Date& right)const{
       return daysSince0001_1_1() - right.daysSince0001_1_1() > 0;
   }
   bool Date::operator>=(const Date& right)const{
       return operator>(right) || operator==(right);
   }
   bool Date::operator<(const Date& right)const{
       return operator>=(right) == false;
   }
   bool Date::operator<=(const Date& right)const{
       return operator>(right) == false;
   }
   ostream& operator<<(ostream& os, const Date& RO){
      return RO.write(os);
   }
   istream& operator>>(istream& is, Date& RO){
      return RO.read(is);
   }

}
