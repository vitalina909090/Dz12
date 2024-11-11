#include <iostream>
#include <Windows.h>
using namespace std;

class Transport {
protected:
    double speed;
    double cost;
    double expenses;

public:
    Transport(double speedP, double costP, double expensesP)
        : speed(speedP), cost(costP), expenses(expensesP) {
        if (speed <= 0 || cost < 0 || expenses < 0) {
            throw "Некоректний ввід";
        }
    }

    double time(double length) {
        if (length <= 0) throw "Відстань має бути більше нуля";
        return length / speed;
    }

    virtual void costDetermination(double length) {
        if (length <= 0) throw "Відстань має бути більше нуля";
        double totalCost = (length / 100.0) * expenses * cost;
        cout << "Вартість = " << totalCost << " грн" << endl;
    }

    virtual void print(double length) {
        cout << "Швидкість: " << speed << " км/год, "
            << "Вартість бензину на 100 км: " << cost << " грн " << endl;
    }

    virtual void passengers(int numPassengers) {}
    virtual void payload(double cargo) {}
};

class Car : public Transport {
private:
    int maxPassengers;
    double maxPayload;
    string fuelType;

public:
    Car(double speedP, double costP, double expensesP, int maxPassengersP, double maxPayloadP, string fuelTypeP)
        : Transport(speedP, costP, expensesP), maxPassengers(maxPassengersP), maxPayload(maxPayloadP), fuelType(fuelTypeP) {
        if (maxPassengers <= 0 || maxPayload < 0) {
            throw "Некоректний ввід для авто";
        }
    }

    void passengers(int numPassengers, double length) {
        if (numPassengers > maxPassengers) {
            throw "Перевищена максимальна кількість пасажирів";
        }
        costDetermination(length);
    }

    void payload(double cargo, double length) {
        if (cargo > maxPayload) {
            throw "Перевищена максимальна вага вантажу";
        }
        costDetermination(length);
    }

    void print(double length) {
        Transport::print(length);
        cout << "Макс. пасажири: " << maxPassengers << ", "
            << "Макс. вантаж: " << maxPayload << " кг, "
            << "Тип пального: " << fuelType << endl;
        cout << "Час: " << time(length) << " год" << endl;
        costDetermination(length);
    }
};

class Bicycle : public Transport {
private:
    double maxWeightBasket;
    bool hasBell;

public:
    Bicycle(double speedP, double maxWeightBasketP, bool hasBellP)
        : Transport(speedP, 0, 0), maxWeightBasket(maxWeightBasketP), hasBell(hasBellP) {
        if (maxWeightBasket < 0) {
            throw "Некоректна максимальна вага кошика";
        }
    }

    void payload(double cargo) {
        if (cargo > maxWeightBasket) {
            throw "Перевищена максимальна вага вантажу для кошика";
        }
    }

    void print(double length) {
        Transport::print(length);
        cout << "Макс. вага кошика: " << maxWeightBasket << " кг, "
            << "Наявність дзвоника: " << (hasBell ? "Так" : "Ні") << endl;
        cout << "Час: " << time(length) << " год" << endl;
        costDetermination(length);
    }
};

class Cart : public Transport {
private:
    double maxKilogram;
    int horsePower;
    string material;
    double foodCost;

public:
    Cart(double speedP, double maxKilogramP, int horsePowerP, string materialP, double foodCostP)
        : Transport(speedP, 0, 0), maxKilogram(maxKilogramP), horsePower(horsePowerP), material(materialP), foodCost(foodCostP) {
        if (maxKilogram < 0 || horsePower <= 0 || foodCost < 0) {
            throw "Некоректний ввід для возу!";
        }
    }

    void costDetermination(double length) {
        if (length <= 0) throw "Відстань має бути більше нуля";
        double totalCost = (length / 100.0) * expenses * cost + foodCost;
        cout << "Вартість = " << totalCost << " грн (включно з їжею)" << endl;
    }

    void print(double length) {
        Transport::print(length);
        cout << "Макс. вага: " << maxKilogram << " кг, "
            << "Кінські сили: " << horsePower << ", "
            << "Матеріал: " << material << ", "
            << "Витрати на їжу: " << foodCost << " грн" << endl;
        cout << "Час: " << time(length) << " год" << endl;
        costDetermination(length);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        Car car(90, 6, 8, 4, 300, "Бензин");
        Bicycle bicycle(15, 3, true);
        Cart cart(10, 500, 2, "Дерево", 250);

        double length;
        cout << "Введіть відстань для перевезення (км): ";
        cin >> length;

        if (length <= 0) throw "Відстань має бути більше нуля";

        cout << "Автомобіль:\n";
        car.print(length);
        cout << "\nВелосипед:\n";
        bicycle.print(length);
        cout << "\nВіз:\n";
        cart.print(length);
    }
    catch (const char* error) {
        cerr << "Помилка: " << error << endl;
    }

    return 0;
}
