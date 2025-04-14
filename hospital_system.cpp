#include <iostream>
#include <fstream> //for reading from file and writing from file
#include <vector> //an array-like structure that holds a set of direct-access elements of the same kinds
#include <string>
#include <sstream>
#include <ctime> //for measuring time and date
#include <algorithm>
#include <iomanip> // manipulators for controlling the formatting of input and output streams for example setprecision and setw
#include <limits> // for information for arthmetic types(either integer or double)
#include <functional>//provides a set of predefined class templates for function objects,
                      //  including operations for arithmetic, comparisons, and logic.

using namespace std;

// ——————————————————————————————————————————————————————————————
// Safe input for int, double, and nonempty string - Error Handling
// ——————————————————————————————————————————————————————————————

int readInt(const string &prompt) {
    while (true) {
        cout << prompt;
        int x;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //implementation of library <limit>
            return x;
        }
        cout << "Please enter a valid integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double readDouble(const string &prompt) {
    while (true) {
        cout << prompt;
        double x;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cout << "Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readNonEmpty(const string &prompt) {
    while (true) {
        cout << prompt;
        string s;
        getline(cin, s);
        if (!s.empty()) return s;
        cout << "Input cannot be empty.\n";
    }
}

// ——————————————————————————————————————————————————————————————
//  Usecase of  Split, Clear Screen Funcionality- creativity
// ——————————————————————————————————————————————————————————————

vector<string> split(const string& s, char delim) {
    vector<string> out; string token; istringstream ss(s);
    while (getline(ss, token, delim)) out.push_back(token);
    return out;
}

//_______________________________________________________________
// Usecase of current time and datefunctionality - creativity 
//__________________________________________________________________
string nowStr() {
    time_t t = time(nullptr);
    tm* lt = localtime(&t);
    ostringstream o;
    o << (1900 + lt->tm_year) << '-'
      << setw(2) << setfill('0') << (1 + lt->tm_mon) << '-'
      << setw(2) << setfill('0') << lt->tm_mday << ' '
      << setw(2) << setfill('0') << lt->tm_hour << ':'
      << setw(2) << setfill('0') << lt->tm_min << ':'
      << setw(2) << setfill('0') << lt->tm_sec;
    return o.str();
}

//_______________________________________________________________
//  interface clearing functionality for both window and linux
//______________________________________________________________
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}



// ——————————————————————————————————————————————————————————————
// Login page
// ——————————————————————————————————————————————————————————————

bool login() {
    clearScreen();
    const string ADMIN_EMAIL    = "admin@hospital.com";
    const string ADMIN_PASSWORD = "admin123";

    string email, password;
    cout << "\t\t\t\t SHAHI HOSPITAL-(Your Health, Our Commitment) \t\t\t\t\t\t\n";
    
    cout << "\t\t\t\t\t================= ADMIN LOGIN ==============\t\t\t\t\t\t\n";
    cout << "\t\t\t\t\t Email: "; 
    cin >> email ;
    cout << "\t\t\t\t\t Password: ";
    cin >> password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (email == ADMIN_EMAIL && password == ADMIN_PASSWORD) {
        cout << "Login successful!\n";
        return true;
    }
    cout << "Invalid email or password.\n";
    return false;
}

//_____________________________________________________________________________________________
// Base Class : person (------Inheritance------) and implementation of ------ABSTRACTION------
//_____________________________________________________________________________________________

class Person {
protected:
    string name, contact;
public:
    Person(string n = "", string c = ""): name(n), contact(c) {} //constructor
    virtual void display() const = 0;  //abstraction
    virtual ~Person() {}               //destruction

    string getName() const {
         return name;
        }
    string getContact() const {
         return contact;
        }
};



// ____________________________________________________________________________________________________-
// Doctor attributes and methods and -----------derived class--------- and Implementation of ---P0LYMORPHISM-----
// __________________________________________________________________________________________________

class Patient : public Person {
    string id, gender, address;
    int age; 
    double weight;

public:
    Patient(string i = "", string n = "", string c = "", int a = 0, string g = "", double w = 0, string addr = "")
     : Person(n, c), id(i), gender(g), address(addr), age(a), weight(w) {}
    void display() const override {  //Polymorphism
        cout << left
             << setw(8) << id  //atribute
             << setw(20) << name
             << setw(8) << gender
             << setw(4) << age
             << setw(8) << fixed << setprecision(1) << weight
             << setw(15) << contact
             << address
             << "\n";
    }

    string getId() const{    //getter/method
        return id;
    }
    string getGender() const{
         return gender;
    }
    int getAge() const{ 
        return age;
    }
    double getWeight() const{
         return weight;
    }
    string getAddress() const{ 
        return address;
    }
};

//__________________________________________________________________________
// class-Doctor: attribute and methods and implementation of -----ENCAPULATION----
//____________________________________________________________________________

class Doctor : public Person {
    string id, spec;
    double fee;
    vector<string> times;

public:
    Doctor(string i = "", string n = "", string c = "", string s = "", double f = 0, vector<string> ts = {})
     : Person(n, c), id(i), spec(s), fee(f), times(ts) {}

    void display() const override {
        cout << left
             << setw(8) << id
             << setw(20) << name
             << setw(15) << spec
             << "Rs" << setw(7) << fixed << setprecision(2) << fee
             << contact << "\n  Times:";
        for (auto &t : times) cout << " " << t;
        cout << "\n";

    }

    string getId() const{
         return id; 
    }
    string getSpecialization() const{
         return spec;
    }
    double getFee() const{
         return fee;
    }
    vector<string> getAvailableTimes() const{
         return times;
    }
};


// ——————————————————————————————————————————————————————————————
// Services entities and methods
// ——————————————————————————————————————————————————————————————

class Service {
    string name;
    double basePrice, discount;

public:
    Service(string n = "", double p = 0, double d = 0): name(n), basePrice(p), discount(d) {}
    void display() const {
        cout << left
             << setw(20) << name
             << "Rs" << setw(8) << fixed << setprecision(2) << getPrice()
             << "(" << setw(3) << int(discount*100) << "% off)"
             << "\n";
    }
    string getName() const{
         return name;
    }
    double getPrice() const { 
        return basePrice * (1 - discount);
    }
    double getBasePrice() const {
         return basePrice;
    }
    double getDiscount() const {
         return discount;
    }
};


// ——————————————————————————————————————————————————————————————
// Medicines entities and methods
// ——————————————————————————————————————————————————————————————

class Medicine {
    string code, name;
    double basePrice, discount;
public:
    Medicine(string c = "", string n = "", double p = 0, double d = 0)
     : code(c), name(n), basePrice(p), discount(d) {}
    void display() const {
        cout << left
             << setw(8) << code
             << setw(20) << name
             << "Rs" << setw(8) << fixed << setprecision(2) << getPrice()
             << "(" << setw(3) << int(discount*100) << "% off)"
             << "\n";
    }
    string getCode() const {
         return code;
    }
    string getName() const {
         return name;
    }
    double getPrice() const {
         return basePrice * (1 - discount);
    }
    double getBasePrice() const {
         return basePrice; 
    }
    double getDiscount() const {
         return discount; 
    }
};


// ——————————————————————————————————————————————————————————————
// Bill Struct & Storage
// ——————————————————————————————————————————————————————————————

struct Bill {
    string pid, did, datetime;
    vector<string> services, medicines;
    double total = 0;
    bool paid = false;
};
 vector<Bill> allBills;


// ——————————————————————————————————————————————————————————————
// FileManager Template & Overrides
// ——————————————————————————————————————————————————————————————

template<typename T>
class FileManager {
protected:
    string fn; vector<T> items;
    virtual T parse(const vector<string>&)=0;
    virtual string format(const T&)=0;


public:
    FileManager(string file): fn(file) { load(); }
    virtual ~FileManager() {}

    void load() {
        items.clear();
        ifstream in(fn);
        string line;

        while (getline(in, line)) {
            if (line.empty()) continue;
            auto v = split(line, ',');

            try {
                items.push_back(parse(v));

            } catch (...) {
                cerr << "Bad line in " << fn << ": " << line << "\n";
            }
        }
    }

    void save() {
        ofstream out(fn);
        for (auto &i : items) out << format(i) << "\n";
    }

    void add(const T& i) {
         items.push_back(i); save(); 
    }

    vector<T>& getAll() {
         return items; 
    }

    bool removeIf(function<bool(const T&)> pred) {
        auto before = items.size();
        items.erase(remove_if(items.begin(), items.end(), pred), items.end());
        if (items.size() < before) { 
            save(); return true;
    }
        return false;
    }
};



// ——————————————————————————————————————————————————————————————
// Patient Manager class, use of vector  to add patient in file
// ——————————————————————————————————————————————————————————————

class PatientManager : public FileManager<Patient> {
    Patient parse(const vector<string>& p) override {
        return Patient(p[0],
                       p[1],
                       p[2],
                       stoi(p[3]),
                       p[4],
                       stod(p[5]),
                       p[6]);
    }

    string format(const Patient& p) override {
        ostringstream o;
        o << p.getId()<< ","<< p.getName()<< ","<< p.getContact() << ","
          << p.getAge()<< ","<< p.getGender()<< ","<< p.getWeight()
          << "," << p.getAddress();

        return o.str();
    }

public:
    PatientManager(): FileManager("patients.txt") {}
};




// ——————————————————————————————————————————————————————————————
// Doctor Manage class
// ——————————————————————————————————————————————————————————————

class DoctorManager : public FileManager<Doctor> {
    Doctor parse(const vector<string>& p) override {
        vector<string> t;
        if (p.size() > 5) for (auto &x : split(p[5], ';')) t.push_back(x);
        return Doctor(p[0],
                      p[1],
                      p[2],
                      p[3],
                      stod(p[4]),
                      t);
    }
    string format(const Doctor& d) override {
        ostringstream o;
        o << d.getId() << ","<< d.getName()<< ","<< d.getContact()<< ","
          << d.getSpecialization()<< ","<< d.getFee()<< ",";

        auto times = d.getAvailableTimes();
        for (size_t i = 0; i < times.size(); i++)
            o << times[i] << (i+1 < times.size() ? ";" : "");


        return o.str();
    }

public:
    DoctorManager(): FileManager("doctors.txt") {}
};



// ——————————————————————————————————————————————————————————————
// Services Manager class
// ——————————————————————————————————————————————————————————————

class ServiceManager : public FileManager<Service> {
    Service parse(const vector<string>& p) override {
        return Service(p[0],
                       stod(p[1]),
                       stod(p[2]));
    }

    string format(const Service& s) override {
        ostringstream o;
        o << s.getName() << ","
          << fixed << setprecision(2) << s.getBasePrice() << ","
          << s.getDiscount();

        return o.str();
    }

public:
    ServiceManager(): FileManager("services.txt") {}
};



// ——————————————————————————————————————————————————————————————
// Medicine Manager class
// ——————————————————————————————————————————————————————————————

class MedicineManager : public FileManager<Medicine> {
    Medicine parse(const vector<string>& p) override {
        return Medicine(p[0], p[1], stod(p[2]), stod(p[3]));
    }
    string format(const Medicine& m) override {
        ostringstream o;
        o << m.getCode()<< ","
          << m.getName()<< ","
          << fixed<< setprecision(2)<< m.getBasePrice() << ","
          << m.getDiscount();
        return o.str();
    }

public:
    MedicineManager(): FileManager("medicines.txt") {}
};


// __________________________________________________________________________________________
// main() with Nested Menus:  Here is the program of to showing output and taking input from user
// __________________________________________________________________________________________

int main() {
    if (!login()) return 0;
    //____________________________________________________
    // proper implementation of -----OBJECT-----------
    //_____________________________________________________
    PatientManager pm;  //object
    DoctorManager  dm;
    ServiceManager sm;
    MedicineManager mm;


    while (true) {
        clearScreen();
        //___________________________________________________________________________________
        //Implementation of user-friendly,  menu drive console-base userinterface
        //____________________________________________________________________________________

        
        cout << "\t\t\t\tSHAHI HOSPITAL-(Your Health, Our Commitment) \t\t\t\n";
        cout << "\t\t\t\t=========== MAIN MENU =======\t\t\t\t\t\t\n"
        << "\t\t\t\t| 1) Patients                    |\t\t\t\t\t\t\n"
        << "\t\t\t\t| 2) Doctors                     |\t\t\t\t\t\t\n"   
        << "\t\t\t\t| 3) Services                    |\t\t\t\t\t\t\n"
        << "\t\t\t\t| 4) Medicines                   |\t\t\t\t\t\t\n"
        << "\t\t\t\t| 5) Billing                     |\t\t\t\t\t\t\n"                   
        << "\t\t\t\t| 0) Exit                        |\t\t\t\t\t\t\n";
        int choice = readInt("Choose section: ");
        if (choice == 0) break;


        switch (choice) {
            case 1: { // Patients
                while (true) {
                    clearScreen();
                    cout << "\t\t\t\t================PATIENTS SECTION===================\t\t\t\t\t\n"
                         << "\t\t\t\t\t| 1) View Patients                  |\t\t\t\t\t\t\n"
                         << "\t\t\t\t\t| 2) Add Patient                    |\t\t\t\t\t\t\n"
                         << "\t\t\t\t\t| 3) Delete Patient                 |\t\t\t\t\t\t\n"
                         << "\t\t\t\t\t| 0) Back                           |\t\t\t\t\t\t\n";
                    int c = readInt("Choice: ");
                    if (c == 0) break;

            
                    if (c == 1) {
                        clearScreen();
                        cout << "=======================PATIENTS DETALILS======================\n"
                             << left << setw(8)<<"ID"<<setw(20)<<"Name"
                             <<setw(8)<<"Gender"<<setw(4)<<"Age"
                             <<setw(8)<<"Weight"<<setw(15)<<"Contact"
                             << "Address\n"
                             << string(80,'-') << "\n";
                        for (auto &p : pm.getAll()) p.display();
                        cout << "\nPress Enter to continue..."; cin.get();
                    }


                    else if (c == 2) {
                        //______Functionality to Add patient with different attribut_______
                        string id = readNonEmpty("Enter Patient ID: ");
                        string name=readNonEmpty("Enter Patient Name: ");
                        string contact = readNonEmpty("Enter Contact: ");
                        string gender = readNonEmpty("Enter Gender: ");
                        int age = readInt("Enter Age: ");
                        double weight = readDouble("Enter Weight:");
                        string addr = readNonEmpty("Enter Address:");
                        pm.add(Patient(id, name, contact, age, gender, weight, addr));
                        cout << " Patient added!. Press Enter to continue....."; cin.get();
                    }


                    else if (c == 3) {
                        //_______Feature for Deleting Patient__________________________
                        string id = readNonEmpty("Enter Patient ID to delete:");
                        if (pm.removeIf([&](auto &p){ return p.getId()==id; }))
                            cout << "Patient Deleted.\n";
                        else
                            cout << "Not found.\n";
                        cout << "Press Enter to continue..."; cin.get();
                    }
                    else {
                        cout << "Invalid choice.\nPress Enter to continue..."; cin.get();
                    }
                }
                break;
            }

            
            case 2: { // Doctors
                while (true) {
                    clearScreen();
                    cout<< "\t\t\t\t\tTeam of Experienced & Dedicatet Doctor \t\t\t\t\t\t\t\n";
                    cout<<"\n";
                    cout << "\t\t\t\t============DOCTOR SECTION ===============\n"
                         << "\t\t\t\t\t| 1) View Doctors                        |\t\t\t\t\t\n"
                         << "\t\t\t\t\t| 2) Add Doctor                          |t\t\t\t\t\t\n"
                         << "\t\t\t\t\t| 3) Delete Doctor                       |\t\t\t\t\t\n"
                         << "\t\t\t\t\t| 0) Back                                |\t\t\t\t\tn";
                    int c = readInt("Choice: ");
                    if (c == 0) break;

            
                    if (c == 1) {
                        clearScreen();
                        cout << "==================== All Doctors ===================\n"
                             << left << setw(8)<<"ID"<<setw(20)<<"Name"
                             <<setw(15)<<"Specialty"<<setw(8)<<"Fee"
                             << setw(8)<<"Contact\n"
                             << string(80,'-') << "\n";
                        for (auto &d : dm.getAll()) d.display();
                        cout << "\nPress Enter to continue..."; cin.get();
                    }


                    else if (c == 2) {
                        //______Features to Add Doctor _______
                        string id    = readNonEmpty("Enter Doctor ID: ");
                        string name  = readNonEmpty("Enter Name: ");
                        string contact = readNonEmpty("Enter Contact: ");
                        string spec  = readNonEmpty("Enter Specialization: ");
                        double fee   = readDouble("Enter Fee: ");
                        int nTimes   = readInt("Number of available times: ");

                        // -------Bill with Time stamp-------
                        vector<string> times;
                        for (int i = 0; i < nTimes; i++)
                            times.push_back(readNonEmpty(" Time: "));
                        dm.add(Doctor(id, name, contact, spec, fee, times));
                        cout << "Doctor added. Press Enter to continue..."; cin.get();
                    }

                    //______features to delete doctor with different attribut_______
                    else if (c == 3) {
                        string id = readNonEmpty("Enter Doctor ID to delete: ");
                        if (dm.removeIf([&](auto &d){ return d.getId()==id; }))
                            cout << "Deleted.\n";
                        else
                            cout << "Not found.\n";
                        cout << "Press Enter to continue..."; cin.get();
                    }
                    else {
                        cout << "Invalid choice.\nPress Enter to continue..."; cin.get();
                    }
                }
                break;
            }


            
            case 3: { // Services
                while (true) {
                    clearScreen();
                    cout << "\t\t\t\t\t\t\t==============Services =============\n"
                         << "\t\t\t\t\t\t\t| 1) View Services                  |\t\t\t\t\t\t\n"
                         << "\t\t\t\t\t\t\t| 2) Add Service                    |\t\t\t\t\t\t\n"
                         << "\t\t\t\t\t\t\t| 3) Delete Service                 |\t\t\t\t\t\t\n"
                         << "\t\t\t\t\t\t\t| 0) Back                           |\t\t\t\t\t\t\n";

                    int c = readInt("Choice: ");
                    if (c == 0) break;
            
                    if (c == 1) {
                        clearScreen();
                        cout << "================== All Services ===============\n"
                        <<left<< setw(15)<<"Name"<<setw(10)<<"Fee"<<setw(12)<<"Discount\n"
                        << string(80,'-')<<"\n";
                        for (auto &s : sm.getAll()) s.display();
                        cout << "\nPress Enter to continue..."; cin.get();
                    }

                    else if (c == 2) {
                        string name = readNonEmpty("Enter Service Name: ");
                        double price = readDouble("Enter Price: ");
                        double disc  = readDouble("Enter Discount (0-1 eg 0.01, 0.02): ");
                        sm.add(Service(name, price, disc));
                        cout << "Service added. Press Enter to continue..."; cin.get();
                    }


                    else if (c == 3) {
                        string name = readNonEmpty("Enter Service Name to delete: ");
                        if (sm.removeIf([&](auto &s){ return s.getName()==name; }))
                            cout << "Deleted.\n";
                        else
                            cout << "Not found.\n";
                        cout << "Press Enter to continue..."; cin.get();
                    }
                    else {
                        cout << "Invalid choice.\nPress Enter to continue..."; cin.get();
                    }
                }
                break;
            }

            
            case 4: { // Medicines
                while (true) {
                    clearScreen();
                    cout << "\t\t\t\t\t\t======= MEDICINES SECTIONS=======\t\t\t\t\t\t\n"
                         << "\t\t\t\t\t\t| 1) View Medicines                |\t\t\t\t\t\t\n"
                         << "\t\t\t\t\t\t|2) Add Medicine                   |\t\t\t\t\t\t\n"
                         << "\t\t\t\t\t\t|3) Delete Medicine                |\t\t\t\t\t\t\n"
                         << "\t\t\t\t\t\t|0) Back                           |\t\t\t\t\t\t\n";
                    int c = readInt("Choice: ");

                    if (c == 0) break;
            
                    if (c == 1) {
                        clearScreen();
                        cout << "=============== All Medicines ================\n"
                        <<left <<setw(10)<<"Med code" <<setw(18)<<"Medicine Name"
                        <<setw(10)<<"Price"<<setw(10)<<"Discount\n"
                        <<string(70,'-')<<"\n";
                        for (auto &m : mm.getAll()) m.display();
                        cout << "\nPress Enter to continue..."; cin.get();
                    }


                    else if (c == 2) {
                        string code = readNonEmpty("Enter Medicine Code: ");
                        string name = readNonEmpty("Enter Name: ");
                        double price = readDouble("Enter Price: ");
                        double disc  = readDouble("Enter Discount (0-1): ");
                        mm.add(Medicine(code, name, price, disc));
                        cout << "Medicine added. Press Enter to continue..."; cin.get();
                    }

                    else if (c == 3) {
                        string code = readNonEmpty("Enter Medicine Code to delete: ");
                        if (mm.removeIf([&](auto &m){ return m.getCode()==code; }))
                            cout << "Deleted.\n";
                        else
                            cout << "Not found.\n";
                        cout << "Press Enter to continue..."; cin.get();
                    }
                    else {
                        cout << "Invalid choice.\nPress Enter to continue..."; cin.get();
                    }
                }
                break;
            }

            
        case 5: {
            clearScreen();
            cout << "\t\t\t\t\t====BILLING SECTION====\t\t\t\t\n"
                 << "\t\t\t\t\t\t| 1) Make Bill                   |\t\t\t\t\t\t\n"
                 << "\t\t\t\t\t\t| 2) View Bills                  |\t\t\t\t\t\t\n"
                 << "\t\t\t\t\t\t| 0) Back                        |\t\t\t\t\t\t\n";
                 
                 int c = readInt("Choice: ");
                 
            if (c == 1) {
                Bill b;
                // Validate patient
                while (true) {
                    b.pid = readNonEmpty("Enter Patient ID: ");
                    if (any_of(pm.getAll().begin(), pm.getAll().end(),
                               [&](auto &p){ return p.getId()==b.pid; }))
                        break;
                    cout << "Patient not found.\n";
                }

                // Validate doctor
                while (true) {
                    b.did = readNonEmpty("Enter Doctor ID: ");
                    if (any_of(dm.getAll().begin(), dm.getAll().end(),
                               [&](auto &d){ return d.getId()==b.did; }))
                        break;
                    cout << "Doctor not found.\n";
                }
                b.datetime = nowStr();

                int ns = readInt("Number of services: ");
                for (int i = 0; i < ns; i++) {
                    string s = readNonEmpty(" Service name: ");
                    auto it = find_if(sm.getAll().begin(), sm.getAll().end(),
                                      [&](auto &sv){ return sv.getName()==s; });
                    if (it != sm.getAll().end()) {
                        b.services.push_back(s);
                        b.total += it->getPrice();
                    } else {
                        cout << "Service not found: " << s << "\n";
                        --i;
                    }
                }

                int nm = readInt("Number of medicines: ");
                for (int i = 0; i < nm; i++) {
                    string m = readNonEmpty(" Med code: ");
                    auto it = find_if(mm.getAll().begin(), mm.getAll().end(),
                                      [&](auto &md){ return md.getCode()==m; });
                    if (it != mm.getAll().end()) {
                        b.medicines.push_back(m);
                        b.total += it->getPrice();
                    } else {
                        cout << "Medicine not found: " << m << "\n";
                        --i;
                    }
                }
                b.paid = (readNonEmpty("Mark paid now? (y/n): ")[0] == 'y');
                allBills.push_back(b);
                cout << "Bill created. Total: $" << fixed<<setprecision(2)<< b.total << "\n";
                cout << "Press Enter to continue..."; cin.get();
            }


                else if (c == 2) {
                    clearScreen();

                    cout << "================ Patient Invoice ==============\n\n";
                    for (auto &b : allBills){
                        cout<< "Patient ID:" << b.pid<<"\n";
                        cout<< "Doctor ID:" << b.did<<"\n";

                        cout<<"|---------------------------------|\n";
                        
                        // Showing Services with Prices
                        cout << "Services:\n";
                        for (auto &sName : b.services) {
                            
                            auto it = find_if(sm.getAll().begin(), sm.getAll().end(),
                                              [&](auto &sv){ return sv.getName() == sName; });
                            double price = (it != sm.getAll().end())
                                         ? it->getPrice()
                                         : 0.0;
                            cout << "    - " << sName 
                                 << ": Rs" << fixed << setprecision(2) << price << "\n";
                        }
                       
    
    
                        // Showing Medicines with Prices
                        cout << "  Medicines:\n";
                        for (auto &mCode : b.medicines) {
                          
                            auto it = find_if(mm.getAll().begin(), mm.getAll().end(),
                                              [&](auto &md){ return md.getCode() == mCode; });
                            double price = (it != mm.getAll().end())
                                         ? it->getPrice()
                                         : 0.0;
                            cout << "    - " << (it != mm.getAll().end() ? it->getName() : mCode)
                                 << ": Rs" << fixed << setprecision(2) << price << "\n";
                        }
                        cout<<"|---------------------------------|\n";
    
                        cout<< " Total:Rs" << fixed << setprecision(2) << b.total<<"\n";  //show total amount 
                        
                        cout<< " Status:" << (b.paid ? "Paid" : "Pending") << "\n";   //show statued paid or pending
                        
                        cout<< "Time:[" << b.datetime << "]\n ";                     //time-stamp when did the bill passed
                        
                        cout<<"|---------------------------------|\n";
                        
                        cout<<"Thank you for visiting our Hospital. Have a good day.\n";
                        cout<<"Your Health is our first priority";
                        cout<<"**************************";
                        cout<<"**************************";
                
                        cout << "\n";
                
                    }
                    cout << "Press Enter to continue..."; 
                    cin.get();
                  }
                  break;
                 }
                 default:
                    cout << "Invalid section.\nPress Enter to continue..."; cin.get();
                }
            }
            return 0;
        }
        
       

        












