#include <cstdio>
#include <cstdlib>
#include <locale.h>
#include "student.h"

// Максимальное количество студентов
#define MAX_STUDENTS 1000
// Максимальная длина строки в CSV файле
#define MAX_LINE_LENGTH 512

// Функция для разбора строки CSV и заполнения объекта student
bool parse_csv_line(const char* line, student& s) {
    // Буфер для хранения 5 полей (все инициализированы нулями)
    char buf[5][MAX_FIELD] = { {0} };
    int col = 0, pos = 0;  // col - текущая колонка, pos - позиция в колонке

    // Проходим по всей строке до конца строки или символа новой строки
    for (int i = 0; line[i] != '\0' && line[i] != '\n'; ++i) {
        if (line[i] == ';') {
            // Завершаем текущее поле нуль-терминатором
            buf[col][pos] = '\0';
            ++col;  // Переходим к следующей колонке
            pos = 0;  // Сбрасываем позицию в колонке
            if (col >= 5) break;  // Защита от переполнения количества полей
        }
        else if (pos < MAX_FIELD - 1) {
            // Копируем символ в текущее поле, если есть место
            buf[col][pos++] = line[i];
        }
    }
    buf[col][pos] = '\0';  // Завершаем последнее поле

    // Проверяем, что получили ровно 5 полей (4 разделителя)
    if (col != 4) return false;

    // Копируем значения из буфера в поля класса student
    snprintf(s.last_name, MAX_FIELD, "%s", buf[0]);
    snprintf(s.first_name, MAX_FIELD, "%s", buf[1]);
    snprintf(s.middle_name, MAX_FIELD, "%s", buf[2]);
    s.age = atoi(buf[3]);  // Преобразуем строку в число для возраста
    snprintf(s.gender, MAX_FIELD, "%s", buf[4]);

    return true;  // Успешный разбор строки
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Проверка количества аргументов командной строки
    if (argc < 2) {
        printf("Использование: %s Group.csv\n", argv[0]);
        return 1;
    }

    // Открытие файла для чтения
    FILE* f = fopen(argv[1], "r");
    if (!f) {
        printf("Не удалось открыть файл: %s\n", argv[1]);
        return 1;
    }

    // Массив для хранения студентов
    student students[MAX_STUDENTS];
    int count = 0;  // Счетчик студентов
    char line[MAX_LINE_LENGTH];  // Буфер для чтения строк из файла

    // Чтение файла построчно
    while (fgets(line, sizeof(line), f)) {
        // Проверка на превышение максимального количества студентов
        if (count >= MAX_STUDENTS)
            break;

        // Пропускаем пустые строки
        if (line[0] == '\n' || line[0] == '\0')
            continue;

        student s;  // Создаем временный объект student
        if (parse_csv_line(line, s)) {
            // Если строка успешно разобрана, добавляем студента в массив
            students[count++] = s;
        }
    }
    fclose(f);  // Закрываем файл

    // Выводим информацию о всех студентах
    for (int i = 0; i < count; ++i) {
        students[i].print();
    }

    return 0;
}


