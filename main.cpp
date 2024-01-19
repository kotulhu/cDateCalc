#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <locale>

std::tm parseDate(const std::string& dateString) {
    std::tm time = {0};

    std::istringstream ss(dateString);
    ss >> std::get_time(&time, "%d.%m.%Y");

    if (ss.fail()) {
        std::cout << "Got error during parsing string" << std::endl;
    }

    return time;
}

std::string getNumberDayOfYear(const std::string& dateStr) {
    std::tm time = parseDate(dateStr);
    if (!std::mktime(&time)) {
        return "Unacceptable";
    } else {
        int dayOfYear = time.tm_yday + 1;
        return "Number of day: " + std::to_string(dayOfYear);
    }
}

std::string betweenDates(const std::string& dateFrom, const std::string& dateTo) {
    std::tm time1 = parseDate(dateFrom);
    std::tm time2 = parseDate(dateTo);

    std::time_t start = std::mktime(&time1);
    std::time_t end = std::mktime(&time2);

    if (start == -1 || end == -1) {
        return "Unacceptable";
    } else if (start > end) {
        return "End date should be after the start date";
    } else {
        std::time_t difference = end - start;
        int days = difference / (60 * 60 * 24); // Џреобразуем разницу в секундах в дни
        return "Days between dates: " + std::to_string(days);
    }
}

std::string getFridays13(const std::string& year)
{
    std::string result;
    int yearInt = std::stoi(year);

     for (int month = 1; month <= 12; ++month) {

            std::tm timeinfo = {};
            timeinfo.tm_year = yearInt - 1900;
            timeinfo.tm_mon = month - 1;
            timeinfo.tm_mday = 13;


            std::time_t time = std::mktime(&timeinfo);
            std::tm* date = std::localtime(&time);


            if (date->tm_wday == 5) {
                char buffer[80];
                std::strftime(buffer, 80, "%Y-%m-%d", date);
                result += std::string(buffer) + "\n";
            }
        }
    return result;
}

std::string getNewYearDayOfTheWeek(const std::string& yearStr)
{
    int year = std::stoi(yearStr); // Преобразование строки года в целое число
    std::tm timeinfo = {}; // Здесь переменная timeinfo инициализируется пустыми значениями {}, чтобы обнулить все поля структуры.
    timeinfo.tm_year = year - 1900; // Установка года
    timeinfo.tm_mon = 0; // Установка января (месяц начинается с 0)
    timeinfo.tm_mday = 1; // Установка первого числа
    std::mktime(&timeinfo); // Преобразование в структуру времени
    const char* weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return weekdays[timeinfo.tm_wday];
}

std::string getLeapYears()
{
    int start = 2000;
    int stop = 2040;
    int period = 4;
    std::string result;
    for(int i = start; i < stop; i += 4){
        result += "\n" + std::to_string(i);
    }
    return result;
}

int main() {
    std::locale::global(std::locale(""));
    int choice;
    std::string input, input2;

    do {
        std::cout << "Menu:\n";
        std::cout << "1. Number of current day of the year or specified date\n";
        std::cout << "2. Days between dates\n";
        std::cout << "3. Fridays 13 list in specified year\n";
        std::cout << "4. New Year\'s day of the week year\n";
        std::cout << "5. List of leap years since 2000 to 2040\n";
        std::cout << "9. Exit\n";
        std::cout << "Choose operation: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Put date in specified format dd.mm.yyyy: ";
                std::cin >> input;
                std::cout << getNumberDayOfYear(input) << std::endl;
                break;
            case 2:
                std::cout << "Put start date in specified format dd.mm.yyyy: ";
                std::cin >> input;
                std::cout << "Put end date in specified format dd.mm.yyyy: ";
                std::cin >> input2;
                std::cout << betweenDates(input, input2) << std::endl;
                break;
            case 3:
                std::cout << "Put year yyyy: ";
                std::cin >> input;
                std::cout << "Fridays 13 in " << input << " year:\n" << getFridays13(input) << std::endl;
                break;
            case 4:
                std::cout << "Put year yyyy: ";
                std::cin >> input;
                std::cout << "New Year\'s day is " << getNewYearDayOfTheWeek(input) << std::endl;
                break;
            case 5:
                std::cout << "Leap years siince 2000 " << getLeapYears() << std::endl;
                break;
            case 9:
                std::cout << "Exit program\n";
                break;
            default:
                std::cout << "Invalid option\n";
                break;
        }
    } while (choice != 9);

    return 0;
}
