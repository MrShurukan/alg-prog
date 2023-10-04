#include <cstdlib>
#include <iostream>

using namespace std;

int Vysokosnije_goda(int year) //проверяет высокосность года, возвращает 1, если да
{
  if (year % 4 == 0)
  {
    if (year % 100 == 0)
    {
      if (year % 400 == 0)
      {
        return 1;
      }
      else 
      {
        return 0;
      }
    }
    else
    {
      return 1;
    }
  }
  else
  {
    return 0;
  }
}

int Vysokosnij_1_god(int year, int month1, int month2) //проверяет, лежат ли 2 даты по разные стороны от 28 февраля или нет, возвращает 1, есл и да
{
  if (month1<3 && month2<3)
  {
    return 0;
  }
  else if (month1 > 2 && month2 > 2)
  {
    return 0;
  }
  else
  {
    return Vysokosnije_goda(year);
  }
  
}

int Dnej_s_nachala_do_mesaca(int month) //вычисляет количество дней полных месяцов
{
  int Year[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
  int d=0;
  for (int i = 0; i < month; i++)
  {
    d += Year[i];
  }
  return d;
}

int Vysokos_optimalno(int year1, int year2) //оптимально проверяет выскосность
{
  int y_4 = 0, y_100 = 0, y_400 = 0;
  y_4 = -(1 + year1 / 4) * 4 + ((year2 / 4) * 4);
  y_100 = -(1 + year1 / 100) * 100 + ((year2 / 100) * 100);
  y_400 = -(1 + year1 / 400) * 400 + ((year2 / 400) * 400);
  if (y_4<0)
  {
    y_4 = 0;
  }
  if (y_100 < 0)
  {
    y_100 = 0;
  }
  if (y_400 < 0)
  {
    y_400 = 0;
  }
  return y_4/4 - y_100/100 + y_400/400;
}



int main()
{
  //cerr << "Hey there, Geek! :: cerr" << endl; // штука для улавливания ошибок

  int day1, month1, year1, day2, month2, year2, answer = 0;
  cin >> day1 >> month1 >> year1;
  cout << endl;
  cin >> day2 >> month2 >> year2;
    cout << endl;
  if (year2 - year1 == 0 && month2 - month1 == 0) //если динаковые год и месяц
  {
    answer = abs(day2 - day1);
  }
  else if (year2 - year1 == 0) //если одинаковый год
  {
    //вычисляет количество дней в полных месяцах, прибавляет колечство дней, добавляет 1, если год высокосный
    answer = abs((Dnej_s_nachala_do_mesaca(month2 - 1) + day2 - (Dnej_s_nachala_do_mesaca(month1 - 1) + day2)) + Vysokosnij_1_god(year1, month1, month2));
  }
  else //рандомные 2 даты, совпадений нет
  {
    if (year1 > year2)
    {
      int temp_d = 0, temp_m = 0, temp_y = 0; //меняем, чтобы 2 была больше
      temp_d = year1;
      temp_m = month1;
      temp_y = year1;
      year1 = year2;
      month1 = month2;
      day1 = day2;
      year2 = temp_m;
      month2 = temp_m;
      day2 = temp_d;
    }
    int dni = 0, goda = year2 - year1, vysokosnye_dni = 0;
    //for (int i = year1; i < year2-1; i++) //моё решение, проверяет в лоб
    //{
    //  vysokosnye_dni += Vysokosnije_goda(i);
    //}
    vysokosnye_dni = Vysokos_optimalno(year1, year2 - 2)+1; //оптимальное, но +1
    dni = 365 - (Dnej_s_nachala_do_mesaca(month1 - 1) + day1 + Vysokosnij_1_god(year1, 1, month1)) + Dnej_s_nachala_do_mesaca(month2 - 1) + day2 + Vysokosnij_1_god(year1, 1, month2); //считает количество дней, т.к. 2 последних года не полные
    answer = (year2 - year1-1) * 365 + vysokosnye_dni + dni;
  }
  cout << answer;
  cout << endl;
  return 0;
}
