#include <bits/stdc++.h>
using namespace std;

class Car {
private:
    string carId;
    string brand;
    string model;
    double basePricePerDay;
    bool isAvailable;

public:
    Car(string carId, string brand, string model, double basePricePerDay)
        : carId(carId), brand(brand), model(model), basePricePerDay(basePricePerDay), isAvailable(true) {}

    string getCarId() const {
        return carId;
    }

    string getBrand() const {
        return brand;
    }

    string getModel() const {
        return model;
    }

    double calculatePrice(int rentalDays) const {
        return basePricePerDay * rentalDays;
    }

    bool isCarAvailable() const {
        return isAvailable;
    }

    void rentCar() {
        isAvailable = false;
    }

    void returnCar() {
        isAvailable = true;
    }
};

class Customer {
private:
    string customerId;
    string name;

public:
    Customer(string customerId, string name)
        : customerId(customerId), name(name) {}

    string getCustomerId() const {
        return customerId;
    }

    string getName() const {
        return name;
    }
};

class Rental {
private:
    Car* car;
    Customer* customer;
    int days;

public:
    Rental(Car* car, Customer* customer, int days)
        : car(car), customer(customer), days(days) {}

    Car* getCar() const {
        return car;
    }

    Customer* getCustomer() const {
        return customer;
    }

    int getDays() const {
        return days;
    }
};

class CarRentalSystem {
private:
    vector<Car*> cars;
    vector<Customer*> customers;
    vector<Rental*> rentals;

public:
    CarRentalSystem() {}

    void addCar(Car* car) {
        cars.push_back(car);
    }

    void addCustomer(Customer* customer) {
        customers.push_back(customer);
    }

    void rentCar(Car* car, Customer* customer, int days) {
        if (car->isCarAvailable()) {
            car->rentCar();
            rentals.push_back(new Rental(car, customer, days));
        } else {
            std::cout << "Car is not available for rent." << std::endl;
        }
    }

    void returnCar(Car* car) {
        car->returnCar();
        for (auto it = rentals.begin(); it != rentals.end(); ++it) {
            if ((*it)->getCar() == car) {
                rentals.erase(it);
                break;
            }
        }
    }

    void menu() {
        while (true) {
            cout << "\n===== Car Rental System =====" << std::endl;
            cout << "1. Rent a Car" << std::endl;
            cout << "2. Return a Car" << std::endl;
            cout << "3. Exit" << std::endl;
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;
            cin.ignore(); // Clear buffer

            if (choice == 1) {
                cout << "\n== Rent a Car ==" << endl;
                cout << "Enter your name: ";
                string customerName;
                getline(cin, customerName);

                cout << "\nAvailable Cars:" << endl;
                for (Car* car : cars) {
                    if (car->isCarAvailable()) {
                        cout << car->getCarId() << " - " << car->getBrand() << " " << car->getModel() << endl;
                    }
                }

                cout << "Enter the car ID you want to rent: ";
                string carId;
                getline(cin, carId);

                cout << "Enter the number of days for rental: ";
                int rentalDays;
                cin >> rentalDays;
                cin.ignore(); // Clear buffer

                Customer* newCustomer = new Customer("CUS" + to_string(customers.size() + 1), customerName);
                addCustomer(newCustomer);

                Car* selectedCar = nullptr;
                for (Car* car : cars) {
                    if (car->getCarId() == carId && car->isCarAvailable()) {
                        selectedCar = car;
                        break;
                    }
                }

                if (selectedCar != nullptr) {
                    double totalPrice = selectedCar->calculatePrice(rentalDays);
                    cout << "\n== Rental Information ==" << endl;
                    cout << "Customer ID: " << newCustomer->getCustomerId() << endl;
                    cout << "Customer Name: " << newCustomer->getName() << endl;
                    cout << "Car: " << selectedCar->getBrand() << " " << selectedCar->getModel() << endl;
                    cout << "Rental Days: " << rentalDays << endl;
                    cout << "Total Price: $" << totalPrice << endl;

                    cout << "\nConfirm rental (Y/N): ";
                    string confirm;
                    getline(cin, confirm);

                    if (confirm == "Y" || confirm == "y") {
                        rentCar(selectedCar, newCustomer, rentalDays);
                        std::cout << "\nCar rented successfully." << std::endl;
                    } else {
                        std::cout << "\nRental canceled." << std::endl;
                    }
                } else {
                    std::cout << "\nInvalid car selection or car not available for rent." << std::endl;
                }
            } else if (choice == 2) {
                std::cout << "\n== Return a Car ==" << std::endl;
                std::cout << "Enter the car ID you want to return: ";
                std::string carId;
                std::getline(std::cin, carId);

                Car* carToReturn = nullptr;
                for (Car* car : cars) {
                    if (car->getCarId() == carId && !car->isCarAvailable()) {
                        carToReturn = car;
                        break;
                    }
                }

                if (carToReturn != nullptr) {
                    Customer* customer = nullptr;
                    for (Rental* rental : rentals) {
                        if (rental->getCar() == carToReturn) {
                            customer = rental->getCustomer();
                            break;
                        }
                    }

                    if (customer != nullptr) {
                        returnCar(carToReturn);
                        std::cout << "Car returned successfully by " << customer->getName() << std::endl;
                    } else {
                        std::cout << "Car was not rented or rental information is missing." << std::endl;
                    }
                } else {
                    std::cout << "Invalid car ID or car is not rented." << std::endl;
                }
            } else if (choice == 3) {
                break;
            } else {
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
            }
        }

        std::cout << "\nThank you for using the Car Rental System!" << std::endl;
    }
};

int main() {
    CarRentalSystem rentalSystem;

    Car car1("C001", "Toyota", "Camry", 60.0);
    Car car2("C002", "Honda", "Accord", 70.0);
    Car car3("C003", "Mahindra", "Thar", 150.0);
    Car car4("C004", "Mahindra", "Scorpio-S6", 100.0);

    rentalSystem.addCar(&car1);
    rentalSystem.addCar(&car2);
    rentalSystem.addCar(&car3);
    rentalSystem.addCar(&car4);

    rentalSystem.menu();

    return 0;
}
