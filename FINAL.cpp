#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

class login
{

public:
    string password, filename, name, user, pass;
    string username;
    int bill;
    bool flag = false;

    //char *ptr=username;
    bool check = false;
    bool flagToMain = false;
    ofstream ofile;
    ifstream ifile;

    void OldUser()
    {
        cout << "Enter your username:";
        cin >> username;
        cout << "\nEnter your password:";
        cin >> password;
        filename = username + ".txt";
        ifile.open(filename.c_str());
        if (!ifile.is_open() && ifile.fail())
        {
            cout << "\nYou are not registered, please register before logging in.\n";
            ifile.close();
        }
        getline(ifile, user);
        getline(ifile, pass);
        if (username == user && password == pass)
        {
            cout << "\nYou are successfully logged in\n";
            system("cls");
            cout << "Welcome " << username << endl;
            flag = true;

            //interface1();

            ifile.close();
        }
        else
        {
            system("cls");
            cout << "\nWrong username or password!\nPlease try Again.\n";
            LoginInterface();
        }
        cout << endl;
    }

    int valid(string username)
    {

        ifstream i_file;
        i_file.open(username + ".txt");
        if (!i_file.is_open() && i_file.fail())
        {
            check = true;
            i_file.close();
        }
        else
        { //file  found
            check = false;
        }
    }
    void NewUser()
    {
        cout << "\nCreate a username:";
        cin >> username;
        valid(username);
        if (check == false)
        {
            system("cls");
            cout << " User already exists, kindly register yourself / login again ! " << endl;
            LoginInterface();
        }
        else
        {
            cout << "\nCreate a password:";
            cin >> password;
            filename = username + ".txt";
            ofile.open(filename.c_str());

            ofile << username << endl
                  << password << endl;
            ofile.close();
            ofile.open(username + ".txt", ios::app);
            ofile << " 200 " << endl
                  << "CART=" << endl;
            ofile.close();
            system("cls");
            cout << "\nYou are successfully registered" << endl;
            cout << "";
            cin.ignore();

            cout << "Welcome " << username << endl;
            flag = true;
            //interface1();
        }
    }

    // STARTING SCREEN OF THE PROGRAM

    void LoginInterface()
    {
        cout << setw(20) << "*Welcome to the app*" << endl;
        cout << setw(10) << "     Login to continue\n\n";
        cout << setw(10) << "1.Already have an account: Login\n";
        cout << setw(10) << "2.New User? Create an account\n";
        int choiceLogin;
        cout << "Enter a choice" << endl;
        cin >> choiceLogin;
        switch (choiceLogin)
        {
        case 1:
            OldUser();
            break;

        case 2:
            NewUser();
            break;

        default:
            cout << "Enter a valid choice" << endl;
            flag = false;
            LoginInterface();
        }
    }
    int viewwallet()
    {
        fstream obj;
        obj.open(username + ".txt", ios::in);
        string str[4];
        int wallet;
        for (int i = 0; i < 3; i++)
        {
            getline(obj, str[i]);
        }
        wallet = stoi(str[2]);

        obj.close();
        return wallet;
    }
    void clearcart()
    {
        fstream clear;
        string str[3];

        clear.open(username + ".txt");
        for (int i = 0; i < 3; i++)
        {
            getline(clear, str[i]);
        }
        clear.close();
        clear.open(username + ".txt", ios::out | ios::trunc);
        for (int i = 0; i < 3; i++)
        {
            clear << str[i] << "\n";
        }
        clear << "CART="
              << "\n";
        clear.close();
    }
    string substring(string line, int i, int j)
    {
        string word = "";
        for (int k = i; k <= j; k++)
        {
            word += line[k];
        }
        return word;
    }

    int displayBill()
    {
        ifstream cart(username + ".txt");
        string line;
        string price = "Price: ";
        char *search = &price[0]; //Base pointer
        int total = 0;
        while (getline(cart, line))
        {
            if (line.find(search, 0) != string::npos)
            {
                for (int i = 0; i < line.length() - 7; i++)
                {
                    int j = 6 + i;
                    if (substring(line, i, j) == price)
                    {
                        string tempPrice = "";
                        while (j < line.length())
                        {
                            if (line[j] != '/')
                            {
                                tempPrice += line[j];
                                j++;
                            }
                            else
                                break;
                        }
                        total += stoi(tempPrice);
                    }
                }
            }
        }
        cart.close();

        // cout << setw(20) << "Your total Bill is: " << total << endl;
        // cout << setw(25) << "Thank you!!!";
        bill = total;
        return total;
        clearcart();
    }

    void addtocart()
    {
        fstream a, temp;
        string str;
        char c, p;
        int x = 0, z = 0, x1 = 0, z1 = 0, quantity;
        ///////////////////////////////cart///////////////////////////////////////
        cout << "Enter the index of product you want to add in cart" << endl;
        int choice;
        cin >> choice;

        temp.open("temp.txt", ios::in);
        for (int i = 0; !temp.eof(); i++)
        {

            temp.get(p);
            if (p == '.')
            {
                x1++;
            }

            if (x1 == choice)
            {
                a.open(username + ".txt", ios::app);

                getline(temp, str);
                a << str;
                getline(temp, str);
                a << str;

                a << endl;
                a.close();
            }
        }
        a.open(username + ".txt", ios::app);

        cout << "Enter the number of units" << endl;
        cin >> quantity;
        a << "Unit: " << quantity << endl;

        a.close();
        temp.close();
    }

    bool viewcart()
    {

        char c;
        int pos = 0, x = 0, z = 0, shop, temp;
        ifstream view;
        bool print = false, empty = true;
        string line;

        view.open(username + ".txt");

        while (getline(view, line))
        {
            if (line == "CART=")
                print = true;
            else if (print)
            {
                cout << line;
                empty = false;
            }
            cout << endl;
        }
        if (empty)
        {
            system("cls");
            cout << "         ****Cart is empty!****" << endl;
            cout << "You can shop from the following menu\n";
            getch();
            view.close();
            return false;
        }
        else
        {
            view.close();
            cout << "1.To Place order\n2.Go back to main menu\nEnter your choice: ";
            cin >> temp;
            if (temp == 1)
            {
                return true;
            }
            else if (temp == 2)
            {
                system("cls");
                flagToMain = true;
            }
            else
            {
                system("cls");
                cout << "Enter a valid option\n";
                viewcart();
            }
        }
    }
    void placeorder()
    {
        viewcart();
        displayBill();
    }
};

////// For showing products and handling cart  and adding product same as handling cart
class products
{

public:
    int acc_choice;
    int makeupchoice;
    int skinchoice;
    int index, cart_choice;
    char a;

    static bool flag_p;
    static bool flag_cart;

    //string username;
    ofstream fp;

    void displayaccesories()
    {

        cout << setw(5) << "\t\tACCESSORIES\n\n";
        cout << setw(5) << "\t1.Wristwatch" << endl
             << setw(5) << "\t2.Backpack" << endl
             << setw(5) << "\t3.Go Back to Main Menu" << endl;
        cout << "Enter Your Choice: ";
        cin >> acc_choice;
        if (acc_choice == 1 || acc_choice == 2 || acc_choice == 3)
        {
            acc_product(acc_choice);
        }

        else if (acc_choice == 4)
        {
            flag_p = true;
            system("cls");
        }
        else
        {
            cout << "Enter a valid option" << endl;
            displayaccesories();
        }
    }
    void acc_product(int acc_choice)
    {
        ifstream in;
        string str;
        char c;
        int pointer;
        int x = 0, z = 0;

        fstream temp("temp.txt", ios::out);
        in.open("acc.txt");
        for (int i = 0; !in.eof(); i++)
        {
            in.get(c);
            if (c == '@')
            {
                x++;
                z = 1;
            }
            if (x == acc_choice && z == 0)
            {
                cout << c;
                temp << c;
            }
            if (x == acc_choice && z == 1)
            {
                z = 0;
            }
        }
        in.close();
        temp.close();
        cout << setw(5) << "Do you want to enter anything in the cart\n1.Yes\n.2.No\n";
        cin >> cart_choice;
        switch (cart_choice)
        {
        case 1:
            flag_cart = true;
            break;
        case 2:
            system("cls");

            break;
        default:
            cout << "Enter a valid option\n";
            break;
        }
    }
    void displaymakeup()
    {
        cout << setw(5) << "\t\tMAKEUP\n\n"
             << endl;
        cout << setw(5) << "\t1.Nails\n"
             << setw(5) << "\t2.Face" << endl
             << setw(5) << "\t3.Go Back to Main Menu" << endl;
        cout << "Enter Your Choice: ";
        cin >> makeupchoice;

        if (makeupchoice == 1 || makeupchoice == 2)
        {
            makeup_products(makeupchoice);
        }

        else if (makeupchoice == 3)
        {
            flag_p = true;
            system("cls");
        }
        else
        {
            cout << "Enter a valid option" << endl;
            displaymakeup();
        }
    }
    void makeup_products(int makeupchoice)
    {
        ifstream in;
        string str;
        char c;
        int pointer;
        int x = 0, z = 0;
        in.open("makeup.txt");

        fstream temp("temp.txt", ios::out);

        for (int i = 0; !in.eof(); i++)
        {
            in.get(c);
            if (c == '@')
            {
                x++;
                z = 1;
            }
            if (x == makeupchoice && z == 0)
            {

                cout << c;
                temp << c;
            }
            if (x == makeupchoice && z == 1)
            {
                z = 0;
            }
        }

        in.close();
        temp.close();
        cout << "Do you want to enter anything in the cart\n1.Yes\n2.No\n";
        cin >> cart_choice;
        switch (cart_choice)
        {
        case 1:
            flag_cart = true;
            break;
        case 2:
            system("cls");

            break;

        default:
            cout << "Enter a valid option\n";
            break;
        }
    }

    void displayskincare()
    {
        cout << setw(5) << "\t\tSKINCARE\n\n ";
        cout << setw(5) << "\t1.Moisturizer" << endl;
        cout << setw(5) << "\t2.Serum" << endl;
        cout << setw(5) << "\t3.Face Mask" << endl;
        cout << setw(5) << "\t4.Go Back to Main Menu";
        cout << "Enter Your Choice: ";
        cin >> skinchoice;
        if (skinchoice == 1 || skinchoice == 2 || skinchoice == 3)
        {
            skincareproducts(skinchoice);
        }

        else if (skinchoice == 4)
        {
            flag_p = true;
            system("cls");
        }
        else
        {
            cout << "Enter a valid option" << endl;
            displayskincare();
        }
    }
    void skincareproducts(int skinchoice)
    {
        ifstream in;
        string str;
        char c;
        int pointer;
        int x = 0, z = 0;
        in.open("skincare.txt");

        fstream temp("temp.txt", ios::out);

        for (int i = 0; !in.eof(); i++)
        {
            in.get(c);
            if (c == '@')
            {
                x++;
                z = 1;
            }

            if (x == skinchoice && z == 0)
            {
                cout << c;
                temp << c;
            }
            if (x == skinchoice && z == 1)
            {
                z = 0;
            }
        }
        in.close();
        temp.close();
        cout << "Do you want to enter anything in the cart\n1.Yes\n.2.To go to main menu\n";
        cin >> cart_choice;
        switch (cart_choice)
        {
        case 1:
            flag_cart = true;
            cout << flag_cart;
            break;
        case 2:

            system("cls");

            break;

        default:
            cout << "Enter a valid option\n";
            break;
        }
    }
};
bool products::flag_cart = false;
bool products::flag_p = false;

class menu
{

    int size;
    string color;

public:
    int choose, temp;
    login l;
    menu(){};
    menu(string u1)
    {
        l.username = u1;
    }
    int shopstart()
    {
        //// SECOND SCREEN AFTER LOGGING IN
        //// Showing the 3 major categories...above one shows categories under them
        products p1;

        system("cls");
        cout << "Kindly choose your category from below mentioned choices : " << endl;
        cout << setw(10) << "1. MAKEUP ";
        cout << setw(10) << "\n2. SKINCARE ";
        cout << setw(10) << "\n3. ACCESSORIES ";
        cout << setw(10) << "\n4.Go Back to previous menu\n";
        cout << "\nEnter your choice: " << endl;

        cin >> choose;
        switch (choose)
        {
        case 1:

            p1.displaymakeup();
            break;
        case 2:

            p1.displayskincare();
            break;
        case 3:

            p1.displayaccesories();
            break;

        case 4:
            system("cls");
            interface1();
            break;

        default:
            cout << "ERROR, TRY AGAIN !!!!!!!!!!!";
            shopstart();

            break;
        }

        return choose;
    }
    void addcoins()
    {
        ifstream read(l.username + ".txt");
        int availablecoins = 0;
        int bill = l.displayBill();
        string line;
        int curLine = 1;
        while (getline(read, line))
        {
            if (curLine == 3)
            {
                availablecoins = stoi(line);
                break;
            }
            else
            {
                curLine++;
                continue;
            }
        }
        availablecoins += (0.1) * bill;
        read.close();
        ofstream modify("tempBill.txt");
        ifstream org(l.username + ".txt");
        curLine = 1;
        while (getline(org, line))
        {
            if (curLine == 3)
            {
                modify << availablecoins << endl;
            }
            else
            {
                modify << line << endl;
            }
            curLine++;
        }
        string newFile = "tempBill.txt";
        string orgFile = l.username + ".txt";
        modify.close();
        org.close();
        char *a = &orgFile[0];
        char *b = &newFile[0];
        remove(a);
        rename(b, a);

        cout << "Coins earned: " << 0.1 * bill << endl;
    }

    void redeem()
    {
        ifstream read(l.username + ".txt");
        int redeemAvail = 0;
        int bill = l.displayBill();
        string line;
        int curLine = 1;

        while (getline(read, line))
        {
            if (curLine == 3)
            {
                redeemAvail = stoi(line);
                break;
            }
            else
            {
                curLine++;
                continue;
            }
        }
        read.close();
        if (redeemAvail == 0)
        {
            getch();
            system("cls");
            cout << "Your Bill is " << bill << endl;
            cout << "Thanks for shopping" << endl;
            addcoins();
            l.clearcart();
        }
        if (redeemAvail != 0)
        {
            char c;
            cout << "You have " << redeemAvail << " redeemable amount!" << endl;
            cout << "Do you wish to redeem it? (Y/N)" << endl;
            c = getch();
            if (c == 'Y' || c == 'y')
            {
                system("cls");
                cout << "Net Amount: " << bill << endl;
                cout << "Redeemed: " << redeemAvail << endl;
                if (bill >= redeemAvail)
                    cout << "Ammount Payable: " << bill - redeemAvail << endl;
                else
                    cout << "Ammount Payable: 0" << endl;
                ofstream modify("tempBill.txt");
                ifstream org(l.username + ".txt");
                curLine = 1;
                while (getline(org, line))
                {
                    int amount_payable = bill - redeemAvail;
                    if (curLine == 3)
                    {
                        if (redeemAvail > bill)
                        {
                            modify << redeemAvail - bill << endl;
                        }
                        else
                        {
                            modify << 0 << endl;
                        }
                    }
                    else
                    {
                        modify << line << endl;
                    }
                    curLine++;
                }
                string newFile = "tempBill.txt";
                string orgFile = l.username + ".txt";
                modify.close();
                org.close();
                char *a = &orgFile[0];
                char *b = &newFile[0];
                remove(a);
                rename(b, a);
                l.clearcart();
            }
            if (c == 'N' || c == 'n')
            {
                addcoins();
                cout << "Your bill is " << bill << endl;
                l.clearcart();
            }
        }
    }

    ////  FIRST SCREEN AFTER LOGGING IN
    int interface1(void)
    {
        menu welcome;
        int i;
        cout << "\n*** WELCOME TO SHOPPING CENTER *** \n";
        cout << "\n\n\n";
        cout << "                 1.SHOP \n\n";
        cout << "                 2.View Cart\n\n";
        cout << "                 3.Place Order\n\n";
        cout << "                 4.View Balance in cart\n\n";
        cout << "                 5.Exit\n\n";
        cout << "                 Please Enter Required Option: ";

        int choice1;
        cin >> choice1;
        switch (choice1)
        {
        case 1:
            shopstart();

            break;

        case 2:

            if (l.viewcart())
            {
                redeem();
            }
            else
            {
                shopstart();
            }
            break;
        case 3:
            if (l.viewcart())
            {
                cout << "Do you want to shop for anything else?" << endl;
                cout << "1.yes\n2.No\nEnter your choice: ";
                cin >> i;
                if (i == 1)
                {
                    shopstart();
                }
                else if (i == 2)
                {
                    redeem();
                }
                else
                {
                    // cout << "Enter a valid choice" << endl;
                }
            }
            else
            {
                cout << "Cart is empty\n";
                interface1();
            }

            return 0;
            break;
        case 4:
            system("cls");
            cout << "        Balance in wallet is: " << l.viewwallet();
            interface1();
            break;

        case 5:
            cout << "Are you sure you want to exit\n";
            cout << "1.Yes \n2.No\nEnter your choice: ";
            int returnchoice;
            cin >> returnchoice;
            if (returnchoice == 1)
            {
                cout << "Thank you for using the system";
            }
            else
            {
                system("cls");
                interface1();
            }

            break;

        default:
            cout << "Enter a valid choice\n";
            system("cls");
            interface1();
        }
        return choice1;
    }
};

int main()
{
    login user1;
    products p;
    menu m;

    ifstream f1, f2;
    int num;

    user1.LoginInterface();
    menu m1(user1.username);
    if (user1.flag)
    {
        m1.interface1();
    }
    if (p.flag_p == true)
    {
        system("cls");
        m1.shopstart();
    }
cart:

    if (p.flag_cart == true)
    {
        user1.addtocart();
        p.flag_cart = false;
        cout << "Do you want to add anything ?" << endl
             << "1.Yes\n2.No\n";
        cin >> num;
        switch (num)
        {
        case 1:
            m1.shopstart();
            break;
        case 2:
            m1.interface1();
        default:

             cout << "Enter a valid choice\n";
        }
    }
    if (p.flag_cart == true)
    {
        goto cart;
    }
    if (user1.flagToMain)
    {
        m1.interface1();
    }

    return 0;
}