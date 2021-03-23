/*
11. Create a class called Restaurant. Give it the necessary structure, variables, and
functions, and create a pure virtual function called menu. Create a class called
Italian_Restaurant, Greek_Restaurant, and Chinese_Restaurant as derived classes.
Use the parent classes constructor as well as any other variables that need to be
created. Create a templated class called Reader_Robot. It should take in any kind of
restaurant and use polymorphism to read the menu (that you overrode). Show how this
works in main.
*/

#include <iostream>
#include <string>
using namespace std;
template<class T> void Reader_Robot (T a); //reader robot declaration

//==========BASE CLASS===========
class Restaurant{
protected: 
    //protected variables can be accessed by derived classes
    string name;
    string cuisine;//type of restaurant
    int menuSize;//# items in a menu
    string* menuArr; //menu arr is a string array of menu items

public:
    Restaurant(string Name = "Name", int MenuSize = 0): name(Name),menuSize(MenuSize){
        menuArr = new string[menuSize]; //create an array to store menu items
        cuisine = "Cuisine"; //cuisine for the restaurant is set by derived classes
    }//default constructor


    virtual void menu(){  //create virtual function to be overriden in derived classes
        cout << "Called Restaurant::menu()." << endl; 
    }


    //getters and setters
    string getName(){return name;}
    string getCuisine(){return cuisine;}
    string* getMenu() {return menuArr;} 
    int getMenuSize(){return menuSize;}
    void setName(string name){this->name = name;}
    void setCuisine(string cuisine){this->cuisine = cuisine;}
    void setMenu() { //takes in menu items
        cout << "Creating Menu for " << this->cuisine << " Restaurant." << endl;
        for(int i =0; i<menuSize; i++){
            cout <<"Enter Item #" << i+1 << " of " << menuSize << ": ";
            cin >> menuArr[i];
        }//setMenu
    }

    //Rule of 5
    Restaurant(const Restaurant& r){ //take in a constant reference to a restaurant
        //cout << "Copy Constructor Called" << endl;
        this->name = r.name; //give this object the values of the restaurant to be copied
        this->cuisine = r.cuisine;
        this->menuSize = r.menuSize;
        this->menuArr = new string[menuSize]; 
        for(int i = 0; i < menuSize; i++){ this->menuArr[i] = r.menuArr[i]; } //set elements of this to equal elements of restaurant being copied
    }//copy constructor 

    Restaurant& operator = (const Restaurant& r){ //take in a constant reference to a restaurant, and return a reference to a restaurant
        //cout << "Copy Assignment Operator Called" << endl;
        if (this != &r) { //check that we arent making object equal to itself
            if (menuSize > 0) {//if this object has a menu
                delete[] menuArr; //delete it 
            }
        this->name = r.name; //assign variables of provided restaurant to this object
        this->cuisine = r.cuisine;
        this->menuSize = r.menuSize;
        this->menuArr = new string[menuSize];
        for(int i = 0; i < menuSize; i++){ this->menuArr[i] = r.menuArr[i]; } //assign the menu
        return *this; //return a reference to the restaurant
        }
    }//copy assignment operator

    Restaurant(Restaurant&& r){ //accept r-values
        //cout << "Move Constructor Called" << endl;

        this->name = r.name;        //set elements of this to elements of r, then delete pointers to r
        this->cuisine= r.cuisine;
        this->menuSize=r.menuSize;
        this->menuArr = r.menuArr;
        r.menuArr = nullptr; //remove pointer to data because r is an r-value
    }//move constructor

    Restaurant& operator=(Restaurant&& r){
        //cout << "Move Assignment Operator  Called" << endl;

        this->name = r.name;
        this->cuisine = r.cuisine;
        this->menuSize = r.menuSize;
        delete[] menuArr; //delete menu of this object
        this->menuArr = r.menuArr; //set menu of this object to menu of object being moved
        r.menuArr = nullptr;//set menu of object that was moved to null because it will no longer be used
        return *this; //return the moved restaurant
    }//move assignment operator

    ~Restaurant(){
        cout << "Destructor called" << endl;
        delete[] menuArr;//when a restaurant is no longer being used, delete its menu to deallocate the storage
    }//destructor
    
    
};


//=======DERIVED CLASSES=========
class Italian_Restaurant: public Restaurant{
public:
    Italian_Restaurant(string name = " ",int menuSize = 0): Restaurant(name,menuSize){ 
        cuisine = "Italian"; //set cuisine for objects of this class
        menuArr = new string[menuSize]; //declare menuArr for object
    }//default constructor
    

    //menu prints the menu of the restaurant
    void menu() override{
    cout << "Reading using Italian_Restaurant::menu" << endl;
    cout << name << " serves Italian food and has the following menu items: " << endl;
    for(int i =0; i<menuSize; i++){ cout <<menuArr[i] << "   ";}
    cout << endl;
}//overridden menu function
};

class Mexican_Restaurant: public Restaurant{
public:
    Mexican_Restaurant(string name = " ",int menuSize = 0): Restaurant(name,menuSize){ 
        cuisine = "Mexican"; //set cuisine for objects of this class
        menuArr = new string[menuSize];
    }

    void menu() override{
        cout << "Reading using Mexican_Restaurant::menu" << endl;
        cout << name << " serves Mexican food and has the following menu items: " << endl;
        for(int i =0; i<menuSize; i++){ cout <<menuArr[i] << "   ";}
        cout << endl;
    }
};

class Ethiopian_Restaurant: public Restaurant{
public:
    Ethiopian_Restaurant(string name = " ",int menuSize = 0): Restaurant(name,menuSize){ 
        cuisine = "Ethiopian"; //set cuisine for objects of this class
        menuArr = new string[menuSize];
    }

    void menu() override{
        cout << "Reading using Ethiopian_Restaurant::menu" << endl;
        cout << name << " serves Ethiopian food and has the following menu items: " << endl;
        for(int i =0; i<menuSize; i++){ cout <<menuArr[i] << "   ";}
        cout << endl;
    }
};

template<class T> 
void Reader_Robot (T a){
    /*It should take in any kind of restaurant and use polymorphism to read the menu (that you overrode).*/
    a.menu();
}


//===============MAIN================
int main(){

Italian_Restaurant a("Pasta and More", 3);
a.setMenu();
Italian_Restaurant b(a); //copy constructor
Italian_Restaurant c = b; //copy  assignment


Mexican_Restaurant d("Taqueria", 2);
d.setMenu();
Ethiopian_Restaurant e("Noono's", 3);
e.setMenu();

//Reader robot calls the overriden menu() function in the corresponding derived classes, and prints the menu of that restaurant
Reader_Robot(c); //restaurant c was created using 
Reader_Robot(d);
Reader_Robot(e);

}

