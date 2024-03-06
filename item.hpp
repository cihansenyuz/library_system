#include <string>

using namespace std;

typedef class Item
{
private:
    string title;
    string author;
    long long int ISBN;
public:
    Item(string t, string a, long long int i):title(t),author(a),ISBN(i){}
    virtual void displayInfo(void) = 0;
    string getTitle(void){
        return title;
    }
    string getAuthor(void){
        return author;
    }
    long long int getISBN(void){
        return ISBN;
    }
}Item;