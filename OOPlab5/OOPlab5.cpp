#include <iostream>
#include <stdexcept>

// Власний виняток для шаблону
class TemplateException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Template Exception";
    }
};

// Власний клас, який буде використовуватися як параметр шаблону
class MyClass {
private:
    int value;

public:
    explicit MyClass(int val) : value(val) {}

    MyClass() : value(0) {}  // Конструктор за замовчуванням

    MyClass(const MyClass& other) {
        value = other.value;
        std::cout << "Copy Constructor called" << std::endl;
    }

    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            value = other.value;
            std::cout << "Assignment Operator called" << std::endl;
        }
        return *this;
    }

    int getValue() const {
        return value;
    }

    void setValue(int val) {
        value = val;
    }

    void throwError() const {
        throw TemplateException();
    }
};

// Шаблонний клас
template <typename T>
class TemplateClass {
private:
    T data;

public:
    TemplateClass() : data() {}

    TemplateClass(const T& val) : data(val) {}

    TemplateClass(const TemplateClass& other) {
        data = other.data;
    }

    TemplateClass& operator=(const TemplateClass& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    T getData() const {
        return data;
    }

    void setData(const T& val) {
        data = val;
    }
};

int main() {
    try {
        // Тестування шаблону для стандартного типу даних
        TemplateClass<int> intTemplate;
        intTemplate.setData(10);
        std::cout << "Data: " << intTemplate.getData() << std::endl;

        TemplateClass<int> intTemplateCopy(intTemplate);
        std::cout << "Copied Data: " << intTemplateCopy.getData() << std::endl;

        TemplateClass<int> intTemplateAssign;
        intTemplateAssign = intTemplateCopy;
        std::cout << "Assigned Data: " << intTemplateAssign.getData() << std::endl;

        // Тестування винятків для шаблону
        TemplateClass<MyClass> classTemplate;
        MyClass obj(20);
        classTemplate.setData(obj);
        std::cout << "Class Data: " << classTemplate.getData().getValue() << std::endl;

        MyClass objCopy = classTemplate.getData();
        std::cout << "Copied Class Data: " << objCopy.getValue() << std::endl;

        classTemplate.getData().throwError(); // Генерує виняток
    }
    catch (const TemplateException& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
