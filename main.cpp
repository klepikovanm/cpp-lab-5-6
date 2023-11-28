#include <iostream>
using namespace std;

//лаб 5
class Human {
private://спецификатор доступа, в котором лежат переменные - элементы данных, доступ к которым есть только у методов класса
    const char* name;
    const char* gender;
    const char* race;
    int age;
    const char* country;
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
    Human(const char* h_name, const char* h_gender, const char* h_race, int h_age, const char* h_country, float h_IQ) {
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
        delete[] name;
        delete[] gender;
        delete[] race;
        delete[] country;
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
    void setName(const char* h_name) {
        name = h_name;
    }
    void setGender(const char* h_gender) {
        gender = h_gender;
    }
    void setRace(const char* h_race) {
        race = h_race;
    }
    void setAge(int h_age) {
        age = h_age;
    }
    void setCountry(const char* h_country) {
        country = h_country;
    }
    void setIQ(float h_IQ) {
        IQ = h_IQ;
    }
    void setAll(const char* h_name, const char* h_gender, const char* h_race, int h_age, const char* h_country, float h_IQ) {
        name = h_name;
        gender = h_gender;
        race = h_race;
        age = h_age;
        country = h_country;
        IQ = h_IQ;
    }
    //лаб 6
    //функции для возвращения значений
    const char* backName()const {//пишем в конце const, так как метод не меняет содержимое класса
        return name;
    }
    const char* backGender()const {
        return gender;
    }
    const char* backRace()const {
        return race;
    }
    int backAge()const {
        return age;
    }
    const char* backCountry()const {
        return country;
    }
    float backIQ()const {
        return IQ;
    }
    //метод для того, чтобы сверять данные посимвольно, а не по адресам, которые будут переданы в последующие функции
    static bool equals(const char* first, const char* second) {
        int i = 0;
        while (true) {
            if (first[i] != second[i]) {//если хоть одно несовпадение
                return false;
            }
            if (first[i] == '\0' ) {//если все совпало и мы дошли до конца
                return true;
            }
            i++;
        }
    }
    //1)функция среднего IQ для конкретной расы
    //static, так как нестатическая для каждого экземпляра класса своя, и компилятор не знает какую выбрать
    //такая будет одинакова для всех экземпляров
    static float averageIQforRace(Human* humans, int count, const char* race) {
       float all_IQ = 0;
       int k_humans = 0;
       for (int i=0; i<count; i++) {
            if (equals(humans[i].backRace(), race)) {
                all_IQ += humans[i].backIQ();
                k_humans +=1;
            }
        }
        return all_IQ/k_humans;
    }
    //2)функция среднего возраста людей с IQ > N
    static float averageAgeforIQ(Human* humans, int count, int N) {
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
    static float averageIQforCountry(Human* humans, int count, const char* country) {
        float all_IQ = 0;
        int k_humans = 0;
        for (int i=0; i<count; i++) {
            if (equals(humans[i].backCountry(), country)) {
                all_IQ += humans[i].backIQ();
                k_humans += 1;
            }
        }
        return all_IQ/k_humans;
    }
    //3)функия списка стран по убыванию среднего IQ населения
    //int& k_countries - ссылка для того, чтобы можно было использовать переменную, посчитанную в функции, в main
    static const char** IQinCountries(Human* humans, int count, int& k_countries) {
        //создание списков для стран и среднего IQ
        const char** countries = new const char*[count];
        float* averageIQ = new float[count];
        for (int i=0; i<count; i++) {
            countries[i] = humans[i].backCountry();
            averageIQ[i] = humans[i].averageIQforCountry(humans, count, humans[i].backCountry());
        }
        //сортировка по убыванию
        for (int i=0; i<count; i++) {
            for (int j=0; j<count-1; j++) {
                //const char* temp_countries = nullptr; - нейтральное значение
                if (averageIQ[j] < averageIQ[j+1]) {
                    float temp_IQ = averageIQ[j];
                    const char* temp_countries = countries[j];

                    averageIQ[j] = averageIQ[j+1];
                    countries[j] = countries[j+1];

                    averageIQ[j+1] = temp_IQ;
                    countries[j+1] = temp_countries;
                }
            }
        }
        //отбрасывание повторяющихся стран
        //для этого сначала посчитаем сколько их всего
        k_countries = 1;
        for (int i=0; i<count-1; i++) {
            if (!equals(countries[i], countries[i+1])) {
                k_countries += 1;
            }
        }
        //создаем итоговый список
        const char** result = new const char*[k_countries];
        int k=0;
        for (int i=0; i<count; i++) {
            if (k>0 && equals(result[k-1], countries[i])) {//ищем первый другой и записываем его
                continue;
            }
            result[k] = countries[i];
            k++;
        }
        delete[] averageIQ;
        delete[] countries;
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
        char* name = new char[64];
        cin >> name;
        humans[i].setName(name);
        
        cout << "Введите пол человека " << i+1 << ": " << endl;
        char* gender = new char[16];
        cin >> gender;
        humans[i].setGender(gender);

        cout << "Введите расу человека " << i+1 << ": " << endl;
        char* race = new char[32];
        cin >> race;
        humans[i].setRace(race);

        cout << "Введите возраст человека " << i+1 << ": " << endl;
        int age;
        cin >> age;
        humans[i].setAge(age);

        cout << "Введите страну проживания человека " << i+1 << ": " << endl;
        char* country = new char[32];
        cin >> country;
        humans[i].setCountry(country);

        cout << "Введите уровень IQ человека " << i+1 << ": " << endl;
        float IQ;
        cin >> IQ;
        humans[i].setIQ(IQ);
    }
    
    //1)средний IQ для расы
    cout << "Введите расу, чтобы узнать ее средний IQ: ";
    char* race = new char[32];
    cin >> race;
    cout << "Средний IQ для расы " << race << ": " << Human::averageIQforRace(humans, count, race) << endl;
    
    //2)Средний возраст людей с IQ > N
    cout << "Введите уровень IQ и узнайте средний возраст людей с уровнем выше: ";
    float N;
    cin >> N;
    cout << "Средний возраст людей с IQ > " << N << ": " << Human::averageAgeforIQ(humans, count, N) << endl;
    
    //3)Список стран по убыванию среднего IQ населения
    cout << "Список стран по убыванию среднего IQ населения: " << endl;
    int k_countries;
    const char** result = Human::IQinCountries(humans, count, k_countries); //вызываем, чтоб посчиталось k_countries и мы получили список
    for (int i=0; i<k_countries; i++) {
        cout << i+1 << ") " << result[i] << " - " << Human::averageIQforCountry(humans, count, result[i])<< endl;
        delete[] result[i];//чистим память
    } 
    delete[] result;
    delete[] humans;
    return 0;
}