#ifndef STUDENT_H
#define STUDENT_H

// Максимальная длина строкового поля
#define MAX_FIELD 64

// Класс, представляющий студента
class student {
public:
    char last_name[MAX_FIELD];    // Фамилия
    char first_name[MAX_FIELD];   // Имя
    char middle_name[MAX_FIELD];  // Отчество
    int age;                      // Возраст
    char gender[MAX_FIELD];       // Пол

    student() = default;         // Конструктор по умолчанию
    void print() const;          // Метод для вывода информации о студенте
};

// Реализация конструктора по умолчанию
student::student() {
    // Инициализация всех строковых полей пустыми строками
    last_name[0] = first_name[0] = middle_name[0] = gender[0] = '\0';
    age = 0;  // Инициализация возраста нулем
}

// Реализация метода print
inline void student::print() const {
    // Вывод информации о студенте в формате CSV
    printf("%s;%s;%s;%d;%s\n", last_name, first_name, middle_name, age, gender);
}

#endif // STUDENT_H