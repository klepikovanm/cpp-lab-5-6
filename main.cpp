#include <iostream>
using namespace std;

//лаб 5
class Human {
private://спецификатор доступа, в котором лежат переменные - элементы данных, доступ к которым есть только у методов класса
    string name;
    string gender;
    string race;
    int age;
    string country;
    float IQ;
public://спецификатор доступа, который позволяет вызывать другим функциям методы класса

    //конструктор без параметров
    Human() {
        name = "Имя";
        gender = "Пол";
        race = "Раса";
        age = 0;
        country = "Страна";
        IQ = 0;
    }
    //конструктор с параметрами
    Human(string h_name, string h_gender, string h_race, int h_age, string h_country, float h_IQ) {
        name = h_name;
        gender = h_gender;
        race = h_race;
        age = h_age;
        country = h_country;
        IQ = h_IQ;
    }
    //конструктор копирования
    Human(const Human & copy) {
        name = copy.name;
        gender = copy.gender;
        race = copy.race;
        age = copy.age;
        country = copy.country;
        IQ = copy.IQ;
    }
    //Деструктор
    ~Human() {
    
    }
    
    //Функции для вывода на экран каждого поля
    //get-функции позволяют посмотреть значения элементов данных
    void getName() {
        cout << "ФИО: " << name << endl;
    }
    void getGender() {
        cout << "Пол: " << gender << endl;
    }
    void getRace() {
        cout << "Раса: " << race << endl;
    }
    void getAge() {
        cout << "Возраст: " << age << endl;
    }
    void getCountry() {
        cout << "Страна проживания: " << country << endl;
    }
    void getIQ() {
        cout << "Уровень IQ: " << IQ << endl;
    }
    void getAll() {
        cout << "ФИО: " << name << endl;
        cout << "Пол: " << gender << endl;
        cout << "Раса: " << race << endl;
        cout << "Возраст: " << age << endl;
        cout << "Страна проживания: " << country << endl;
        cout << "Уровень IQ: " << IQ << endl;
    }
    //функции для редактирования каждого поля
    //set-функции инициализируют элементы данных
    void setName(string h_name) {
        name = h_name;
    }
    void setGender(string h_gender) {
        gender = h_gender;
    }
    void setRace(string h_race) {
        race = h_race;
    }
    void setAge(int h_age) {
        age = h_age;
    }
    void setCountry(string h_country) {
        country = h_country;
    }
    void setIQ(float h_IQ) {
        IQ = h_IQ;
    }
    void setAll(string h_name, string h_gender, string h_race, int h_age, string h_country, float h_IQ) {
        name = h_name;
        gender = h_gender;
        race = h_race;
        age = h_age;
        country = h_country;
        IQ = h_IQ;
    }

    //лаб 6
    //функции для возвращения значений
    string backName() {
        return name;
    }
    string backGender() {
        return gender;
    }
    string backRace() {
        return race;
    }
    int backAge() {
        return age;
    }
    string backCountry() {
        return country;
    }
    float backIQ() {
        return IQ;
    }
    //1)функция среднего IQ для конкретной расы
    float averageIQforRace(Human* humans, int count, string race) {
       float all_IQ = 0;
       int k_humans = 0;
       for (int i=0; i<count; i++) {
            if (humans[i].backRace() == race) {
                all_IQ += humans[i].backIQ();
                k_humans +=1;
            }
        }
        return all_IQ/k_humans;
    }
    //2)функция среднего возраста людей с IQ > N
    float averageAgeforIQ(Human* humans, int count, int N) {
        int all_Age = 0;
        int k_humans = 0;
        for (int i=0; i<count; i++) {
            if (humans[i].backIQ() > N) {
                all_Age += humans[i].backAge();
                k_humans += 1;
            }
        }
        return all_Age/k_humans;
    }
    //функция среднего IQ для конкретной страны, нужна для функции 3
    float averageIQforCountry(Human* humans, int count, string country) {
        float all_IQ = 0;
        int k_humans = 0;
        for (int i=0; i<count; i++) {
            if (humans[i].backCountry() == country) {
                all_IQ += humans[i].backIQ();
                k_humans += 1;
            }
        }
        return all_IQ/k_humans;
    }
    //3)функия списка стран по убыванию среднего IQ населения
    string* IQinCountries(Human* humans, int count) {
        //создание списков для стран и срелнего IQ
        string* countries = new string[count];
        float* averageIQ = new float[count];
        for (int i=0; i<count; i++) {
            countries[i] = humans[i].backCountry();
            averageIQ[i] = humans[i].averageIQforCountry(humans, count, humans[i].backCountry());
        }
        //сортировка по убыванию
        for (int i=0; i<count; i++) {
            for (int j=0; j<count-1; j++) {
                float temp_IQ = 0;
                string temp_countries = " ";
                if (averageIQ[j] < averageIQ[j+1]) {
                    temp_IQ = averageIQ[j];
                    temp_countries = countries[j];

                    averageIQ[j] = averageIQ[j+1];
                    countries[j] = countries[j+1];

                    averageIQ[j+1] = temp_IQ;
                    countries[j+1] = temp_countries;
                }
            }
        }
        //отбрасывание повторяющихся стран
        //для этого сначала посчитаем сколько их всего
        int k_countries = 0;
        for (int i=0; i<count-1; i++) {
            if (countries[i] != countries[i+1]) {
                k_countries += 1;
            }
        }
        //создаем итоговый список
        string* result = new string[k_countries];
        for (int i=0; i<k_countries; i++) {
            for (int j=i; j<count-1; j++) {
                if (countries[j] != countries[j+1]) {
                    result[i] = countries[j];
                    break;
                }
            }
        }
        result[k_countries] = countries[count]; //заполняем последнюю страну, до которой могли не дойти в цикле
        
        return result;
    }
};
int main() {
  
    //лаб 5
    Human one;//заполнился по умолчанию
    //меняем все по порядку
    one.setName("Николаев Николай Николаевич");
    one.setGender("Мужской");
    one.setRace("Европиоид");
    one.setAge(47);
    one.setCountry("Россия");
    one.setIQ(120);
    //выводим все по порядку
    one.getName();
    one.getGender();
    one.getRace();
    one.getAge();
    one.getCountry();
    one.getIQ();
    //объект через конструктор
    Human two("Мюллер Шарлотта", "Женский", "Европиоид", 25, "Германия", 135);
    //Копируем
    Human three(two);
    //Выводим все сразу
    three.getAll();
    //Меняем все сразу
    three.setAll("Сато Минато", "Мужской", "Монголоид", 33, "Япония", 112);
    //Выводим все сразу
    three.getAll();

    //лаб 6
    //выделяем память на массив объектов-человечков, создаем и заполняем его
    cout << "Введите количество людей: ";
    int count;
    cin >> count;
    Human* humans = new Human[count];
    for (int i=0; i<count; i++) {
        cout << i+1 << ")" << endl;

        cout << "Введите ФИО человека " << i+1 << ": "<< endl;
        string name;
        cin >> name;
        humans[i].setName(name);

        cout << "Введите пол человека " << i+1 << ": " << endl;
        string gender;
        cin >> gender;
        humans[i].setGender(gender);

        cout << "Введите расу человека " << i+1 << ": " << endl;
        string race;
        cin >> race;
        humans[i].setRace(race);

        cout << "Введите возраст человека " << i+1 << ": " << endl;
        int age;
        cin >> age;
        humans[i].setAge(age);

        cout << "Введите страну проживания человека " << i+1 << ": " << endl;
        string country;
        cin >> country;
        humans[i].setCountry(country);

        cout << "Введите уровень IQ человека " << i+1 << ": " << endl;
        float IQ;
        cin >> IQ;
        humans[i].setIQ(IQ);
    }
    //средний IQ для расы
    cout << "Введите расу, чтобы узнать ее средний IQ: ";
    string race;
    cin >> race;
    //cout << "Средний IQ для расы " << race << ": " << Human::averageIQforRace(humans, count, race);

    
    //чистим память
    delete[] humans;
    return 0;
}