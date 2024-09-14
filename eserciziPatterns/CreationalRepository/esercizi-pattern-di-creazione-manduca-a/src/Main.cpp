#include <iostream>
#include <unordered_map>

using namespace std;

// Interfaccia del prototipo
class Shape {
public:
    virtual Shape* clone() const = 0;
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// Implementazione concreta 
class Circle : public Shape {
public:
    Circle(double radius) : radius_(radius) {}

    Shape* clone() const override {
        return new Circle(*this);
    }

    void draw() const override {
        cout << "Cerchio avente raggio " << radius_ << "cm" << endl;
    }

private:
    double radius_;
};

// Implementazione concreta 
class Square : public Shape {
public:
    Square(double side) : side_(side) {}

    Shape* clone() const override {
        return new Square(*this);
    }

    void draw() const override {
        cout << "Quadrato con lato " << side_ << "cm" << endl;
    }

private:
    double side_;
};

// Gestore dei prototipi
class ShapeManager {
public:
    void addPrototype(const string& key, Shape* prototype) {
        prototypes_[key] = prototype;                           //aggiunge il prototipo alla lista(mappa)
    }

    Shape* getPrototype(const string& key) const {
        auto it = prototypes_.find(key);                //se si trova una forma del tipo specificato nella chiave si fa il clone
        if (it != prototypes_.end()) {
            return it->second->clone();
        }
        return nullptr;
    }

private:
    unordered_map<string, Shape*> prototypes_;
};

int main() {
    cout << "Creazione di alcuni prototipi di forme" << endl;
    ShapeManager manager;
    manager.addPrototype("Circle", new Circle(5.0));
    manager.addPrototype("Square", new Square(4.0));

    cout << "Creazione di nuove forme utilizzando i prototipi" << endl;
    for (int i = 0; i < 10; i++)
    {
        Shape* shape1 = manager.getPrototype("Circle");

        // Disegno delle forme
        if (shape1) {
            shape1->draw();
            delete shape1;
        }
        
        Shape* shape2 = manager.getPrototype("Square");

        if (shape2) {
            shape2->draw();
            delete shape2;
        }
    }
    return 0;
}
