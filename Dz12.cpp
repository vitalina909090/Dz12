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
        : speed(speedP), cost(costP), expenses(expensesP) {}

    double time(double length) {
        return length / speed;
    }

    virtual void costDetermination(double length) {
        double totalCost = (length / 100.0) * expenses * cost;
        cout << "Вартість = " << totalCost << " грн" << endl;
    }

    virtual void print(double length) {
        cout << "Швидкість: " << speed << " км/год, " << "Вартість бензину на 100 км: " << cost << " грн " << endl;
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
        : Transport(speedP, costP, expensesP), maxPassengers(maxPassengersP), maxPayload(maxPayloadP), fuelType(fuelTypeP) {}

    void passengers(int numPassengers, double length) {
        if (numPassengers <= maxPassengers) {
            costDetermination(length);
        }
    }

    void payload(double cargo, double length) {
        if (cargo <= maxPayload) {
            costDetermination(length);
        }
    }

    void print(double length) {
        Transport::print(length);
        cout << "Макс. пасажири: " << maxPassengers << ", " << "Макс. вантаж: " << maxPayload << " кг, " << "Тип пального: " << fuelType << endl;
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
        : Transport(speedP, 0, 0), maxWeightBasket(maxWeightBasketP), hasBell(hasBellP) {}

    void passengers(int numPassengers) {
        if (numPassengers == 1) {
            return;
        }
    }

    void payload(double cargo) {
        if (cargo <= maxWeightBasket) {
            return;
        }
    }

    void print(double length) {
        Transport::print(length);
        cout << "Макс. вага кошика: " << maxWeightBasket << " кг, " << "Наявність дзвоника: " << (hasBell ? "Так" : "Ні") << endl;
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
        : Transport(speedP, 0, 0), maxKilogram(maxKilogramP), horsePower(horsePowerP), material(materialP), foodCost(foodCostP) {}

    void passengers(int numPassengers) {
        if (numPassengers <= horsePower * 2) {
            return;
        }
    }

    void payload(double cargo) {
        if (cargo <= maxKilogram) {
            return;
        }
    }

    void costDetermination(double length) {
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

    Car car(90, 6, 8, 4, 300, "Бензин");
    Bicycle bicycle(15, 3, true);
    Cart cart(10, 500, 2, "Дерево", 250);

    double length;
    cout << "Введіть відстань для перевезення (км): ";
    cin >> length;

    cout << "Автомобіль:\n";
    car.print(length);
    cout << "\nВелосипед:\n";
    bicycle.print(length);
    cout << "\nВіз:\n";
    cart.print(length);

    return 0;
}
