#include <iostream>
#include <memory>

using namespace std;

/*1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям. Перегрузите оператор вывода для данного класса.
Создайте два "умных" указателя today и date. Первому присвойте значение сегодняшней даты. Для него вызовите по отдельности методы доступа
к полям класса Date, а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода. Затем переместите ресурс,
которым владеет указатель today в указатель date. Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль.*/

class Date {
private:
    int day;
    int month;
    int year;
public:
    int getDay() const {
        return day;
    }

    void setDay(int d) {
        day = d;
    }

    int getMonth() const {
        return month;
    }

    void setMonth(int m) {
        month = m;
    }

    int getYear() const {
        return year;
    }

    void setYear(int y) {
        year = y;
    }

    friend ostream &operator<<(ostream &out, const Date &date);

};

ostream &operator<<(ostream &out, const Date &date) {
    out << date.getDay() << "." << date.getMonth() << "." << date.getYear();
    return out;
}

/*2. По условию предыдущей задачи создайте два умных указателя date1 и date2.
• Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает их между собой
 (сравнение происходит по датам). Функция должна вернуть более позднюю дату.
• Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в функцию в качестве параметров.

Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров.*/

unique_ptr<Date> &lastDate(unique_ptr<Date> &d1, unique_ptr<Date> &d2) {
    if (d1->getYear() > d2->getYear()) {
        return d1;
    }
    if (d1->getYear() == d2->getYear() && d1->getMonth() > d2->getMonth()) {
        return d1;
    }
    if (d1->getYear() == d2->getYear() && d1->getMonth() == d2->getMonth() && d1->getDay() > d2->getDay()) {
        return d1;
    } else
        return d2;
}

void exchangeDates(unique_ptr<Date> &d1, unique_ptr<Date> &d2) {
    unique_ptr<Date> tmp;
    tmp = move(d1);
    d1 = move(d2);
    d2 = move(tmp);
}

int main() {
    cout << "Task 1:" << endl;
    unique_ptr<Date> today(new Date);
    unique_ptr<Date> date(new Date);
    today->setDay(3);
    today->setMonth(8);
    today->setYear(2022);
    cout << *today << endl;
    cout << "today" << ((today == nullptr) ? " is nullptr" : " is not nullptr") << endl;

    date = move(today);
    cout << "today" << ((today == nullptr) ? " is nullptr" : " is not nullptr") << endl;
    cout << "date" << ((date == nullptr) ? " is nullptr" : " is not nullptr") << endl;

    cout << "Task 2:" << endl;
    unique_ptr<Date> date1(new Date);
    unique_ptr<Date> date2(new Date);
    date1->setDay(12);
    date1->setMonth(8);
    date1->setYear(1999);

    date2->setDay(4);
    date2->setMonth(6);
    date2->setYear(2022);

    cout << *date1 << "\t" << *date2 << endl;
    cout << "Last date: " << *(lastDate(date1, date2)) << endl;

    exchangeDates(date1, date2);
    cout << *date1 << "\t" << *date2 << endl;
    return 0;
}
