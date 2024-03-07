
typedef class Person
{
private:
    string name;
    int id;
    Book* takenBook;
public:
    Person(string n, int i) : name(n), id(i), takenBook(nullptr){}
    void displayInfo(void) const{
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        if(takenBook)
            cout << "Book: " << takenBook->getTitle() << endl;
        else
            cout << "Book: not taken" << endl;
    }
    string getName(void) const{
        return name;
    }
    bool operator<(const Person& other)const{
        if(id < other.id)
            return true;
        else
            return false;
    }
    void takeBook(string bookTitle){

    }
}Person;
