
typedef class Person
{
private:
    string name;
    int id;
    Book* takenBook;
public:
    Person(string n, int i) : name(n), id(i), takenBook(nullptr){}
    void displayInfo(void) {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        if(takenBook)
            cout << "Book: " << takenBook->getTitle() << endl;
        else
            cout << "Book: not taken" << endl;
    }
    string getName(void) {
        return name;
    }
    bool operator<(const Person& other)const{
        if(id < other.id)
            return true;
        else
            return false;
    }
    void setTakenBook(Book& b){
        takenBook = &b;
    }
    Book* getTakenBook(void){
        return takenBook;
    }
}Person;
