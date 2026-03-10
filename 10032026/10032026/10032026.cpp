#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
почему Builder лучше, чем один большой конструктор Burger с параметрами
Ответ: Читается лучше, проще понять и прочитать, легко кастомизировать и расширять
Помогает избегать пергрузку конструктора

*/

class Burger {
private:
    string bun;
    int countBun = 0;
    string patty;
    int countPatty = 0;
    string chees;
    int countChees = 0;
    string veggies;
    int countVeggies = 0;
    string sauce;
    int countSauce = 0;
    string drink;
    int countDrink = 0;
public:
    void setBun(const string& bun) {
        countBun++;
        this->bun = bun;
        // проверка булка одна и таже
    }
    void setPatty(const string& patty) {
        countPatty++;
        this->patty = patty;
    }
    void setChees(const string& chees) {
        countChees++;
        this->chees = chees;
    }
    void setVeggies(const string& veggies) {
        countVeggies++;
        this->veggies = veggies;
    }
    void setSauce(const string& sauce) {
        countSauce++;
        this->sauce = sauce;
    }
    void setDrink(const string& drink) {
        countDrink++;
        this->drink = drink;
    }

    void showOrder() const {
        cout << "Состав бурнера: " << endl;
        cout << "\t- Булочка: " << "x" << countBun << " " << bun << endl;
        cout << "\t- котлета: " << "x" << countPatty << " " << patty << endl;
        cout << "\t- Сыр: " << "x" << countChees << " " << chees << endl;
        cout << "\t- Овощи: " << "x" << countVeggies << " " << veggies << endl;
        cout << "\t- Соус: " << "x" << countSauce << " " << sauce << endl;
        cout << "\t- Напиток: " << "x" << countDrink << " " << drink << endl;
    }

};

class BurgerBuilder {
protected:
    Burger* burger = nullptr;
public:
    virtual ~BurgerBuilder(){}
    void createBurger() { if (burger == nullptr) burger = new Burger(); }
    Burger* getBurger() { return burger; }
    virtual void buildBun() = 0;
    virtual void buildPatty() = 0;
    virtual void buildChees() = 0;
    virtual void buildVeggies() = 0;
    virtual void buildSauce() = 0;
    virtual void buildDrink() = 0;
};

class ClassicBurger : public BurgerBuilder {
public:
    void buildBun() override { burger->setBun(" Классическая с кунжутом"); }
    void buildPatty() override { burger->setPatty("Говяжая котлета"); }
    void buildChees() override { burger->setChees("Чеддер"); }
    void buildVeggies() override { burger->setVeggies("Салат, помидор, огурец"); }
    void buildSauce() override { burger->setSauce("Кетчуп и майонез"); }
    void buildDrink() override { burger->setDrink("Кола"); }
    
};

class VeganBurger : public BurgerBuilder {
public:
    void buildBun() override { burger->setBun(" Цельнозерновая"); }
    void buildPatty() override { burger->setPatty("Соевая котлета"); }
    void buildChees() override { burger->setChees("Веганский сыр"); }
    void buildVeggies() override { burger->setVeggies("Авокадо, шпинат, грибы"); }
    void buildSauce() override { burger->setSauce("Веган майонез и горчица"); }
    void buildDrink() override { burger->setDrink("Зеленый чай"); }

};

class SpicyBurgerBuilder : public BurgerBuilder {
public:
    void buildBun() override { burger->setBun(" Острая булка с перцем"); }
    void buildPatty() override { burger->setPatty("Куриная котлета с чили"); }
    void buildChees() override { burger->setChees("Пеппер джек"); }
    void buildVeggies() override { burger->setVeggies("Халапеньо, лук, салат"); }
    void buildSauce() override { burger->setSauce("Острый соус"); }
    void buildDrink() override { burger->setDrink("Острый лимонад"); }
};

class Cashier {
private:
    BurgerBuilder* builder;
public:
    void setBurger(BurgerBuilder* builder) { this->builder = builder; }
    Burger* assemble(bool extraVeggies = false) {
        if (!builder) return nullptr;

        builder->createBurger();
        builder->buildBun();
        builder->buildPatty();
        builder->buildChees();
        builder->buildVeggies();
        if (extraVeggies) {
            builder->buildVeggies();
        }
        builder->buildSauce();
        return builder->getBurger();
    }
};


int main()
{
    setlocale(0, "");
    Cashier cashier;

    ClassicBurger classicBurger;
    cashier.setBurger(&classicBurger);
    Burger* classicBurger2 = cashier.assemble();
    classicBurger2->showOrder();

    VeganBurger veganBurger;
    cashier.setBurger(&veganBurger);
    Burger* veganBurger2 = cashier.assemble();
    veganBurger2->showOrder();

    SpicyBurgerBuilder spicyBurgerBuilder;
    cashier.setBurger(&spicyBurgerBuilder);
    Burger* spicyBurgerBuilder2 = cashier.assemble();
    spicyBurgerBuilder2->showOrder();

    ClassicBurger classicExtraBuilder;
    cashier.setBurger(&classicExtraBuilder);
    Burger* classicDoubleVeggies = cashier.assemble(true);

    classicDoubleVeggies->showOrder();

    delete classicBurger2, veganBurger2, spicyBurgerBuilder2, classicDoubleVeggies;


}

