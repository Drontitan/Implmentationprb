#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<string, int> mp;
priority_queue<pair<int, pair<string, vector<pair<string, int>>>>, vector<pair<int, pair<string, vector<pair<string, int>>>>>, greater<pair<int, pair<string, vector<pair<string, int>>>>>> q;
int order_id = 0;

class Ecommerce
{
public:
    void Addinventory()
    {
        cout << "Enter the number of the Inventory u want" << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            string str;
            cin >> str;
            int a;
            cin >> a;
            mp[str] = a;
        }
    }

    void SHOW_INVENTORY()
    {
        for (auto ele : mp)
        {
            cout << ele.first << " " << ele.second << endl;
        }
    }

    void CREATE_ORDER()
    {
        cout << "Order created with id " << q.size() + 1 << endl;
    }

    void ADD_ORDERLINE()
    {
        int id;
        cout << "Enter the oder id " << endl;
        cin >> id;
        if (id > q.size() + 1 || id < 0)
        {
            cout << "U have entered the wrong order id pls enter again" << endl;
            return;
        }
        string str;
        cout << "Enter the product name" << endl;
        cin >> str;
        int quantity;
        if (mp.find(str) == mp.end())
        {
            cout << "The item is not in the inventory" << endl;
            return;
        }
        cout << "Enter the quantity of the product" << endl;
        cin >> quantity;
        if (mp[str] < quantity)
        {
            cout << "The quantity of the " << str << " is " << mp[str] << " pls enter it withing the limit" << endl;
            return;
        }
        if (q.size() < id)
        {
            vector<pair<string, int>> vec;
            vec.push_back({str, quantity});
            pair<int, pair<string, vector<pair<string, int>>>> p = {id, {"DRAFT", vec}};
            q.push(p);
        }
        else
        {
            priority_queue<pair<int, pair<string, vector<pair<string, int>>>>> temp;
            pair<int, pair<string, vector<pair<string, int>>>> p;
            while (!q.empty())
            {
                p = q.top();
                q.pop();
                if (p.first == id)
                    break;
                temp.push(p);
            }
            p.second.second.push_back({str, quantity});
            temp.push(p);
            while (!temp.empty())
            {
                q.push(temp.top());
                temp.pop();
            }
        }

        cout << quantity << " " << str << " "
             << "added to order " << id << endl;
    }

    void SHOW_ORDER()
    {
        int n;
        cout << "Enter the order id " << endl;
        cin >> n;

        if (n > q.size())
            cout << "Invalid order id";
        priority_queue<pair<int, pair<string, vector<pair<string, int>>>>> temp;
        pair<int, pair<string, vector<pair<string, int>>>> p;
        while (!q.empty())
        {
            p = q.top();
            q.pop();
            temp.push(p);
            if (p.first == n)
                break;
        }
        while (!temp.empty())
        {
            q.push(temp.top());
            temp.pop();
        }

        string status = p.second.first;
        vector<pair<string, int>> vec = p.second.second;
        int total = 0;
        for (auto ele : vec)
            total += ele.second;
        cout << "Order " << n << " " << status << " " << total << endl;
        for (auto ele : vec)
        {
            cout << ele.first << " " << ele.second << " " << status << endl;
        }
    }

    void SHOW_ORDERS()
    {

        priority_queue<pair<int, pair<string, vector<pair<string, int>>>>> temp;
        pair<int, pair<string, vector<pair<string, int>>>> p;
        while (!q.empty())
        {
            p = q.top();
            q.pop();
            temp.push(p);
            string status = p.second.first;
            vector<pair<string, int>> vec = p.second.second;
            int total = 0;
            for (auto ele : vec)
                total += ele.second;
            cout << "Order " << p.first << " " << status << " " << total << endl;
            for (auto ele : vec)
            {
                cout << ele.first << " " << ele.second << " " << status << endl;
            }
        }

        while (!temp.empty())
        {
            q.push(temp.top());
            temp.pop();
        }
    }

    bool IS_ORDER_BOOKABLE()
    {
        int id;
        cout << "Enter the id of the order" << endl;
        cin >> id;
        if (id > q.size())
        {
            cout << "Enter the correct id of the order" << endl;
            return false;
        }
        priority_queue<pair<int, pair<string, vector<pair<string, int>>>>> temp;
        pair<int, pair<string, vector<pair<string, int>>>> p;
        while (!q.empty())
        {
            p = q.top();
            q.pop();
            temp.push(p);
            if (p.first == id)
                break;
        }
        while (!temp.empty())
        {
            q.push(temp.top());
            temp.pop();
        }
        string status = p.second.first;
        if (status == "BOOKED")
            return false;
        return true;
    }
    void BOOK_ORDER()
    {
        int id;
        cout << "Enter the id of the order" << endl;
        cin >> id;
        if (id > q.size())
        {
            cout << "Enter the correct id of the order" << endl;
            return;
        }
        priority_queue<pair<int, pair<string, vector<pair<string, int>>>>> temp;
        pair<int, pair<string, vector<pair<string, int>>>> p;
        while (!q.empty())
        {
            p = q.top();
            q.pop();
            if (p.first == id)
                break;
            temp.push(p);
        }

        string status = p.second.first;
        bool flag = false;
        if (status == "DRAFT")
        {
            for (auto ele : p.second.second)
            {
                auto item = ele.first;
                auto item_quantity = ele.second;
                if (mp[item] >= item_quantity)
                    mp[item] -= item_quantity;
                else
                {
                    cout << "Error booking order " << id << endl;
                    cout << item << "in inventory are " << mp[item] << "but" << item << "required for order booking is " << item_quantity << endl;
                    flag = true;
                    break;
                }
            }
            if (flag)
                return;
            p.second.first = "BOOKED";
            temp.push(p);
            while (!temp.empty())
            {
                q.push(temp.top());
                temp.pop();
            }
        }
        else
        {
            temp.push(p);
            while (!temp.empty())
            {
                q.push(temp.top());
                temp.pop();
            }
            cout << "The order isnt drafted first" << endl;
            return;
        }
        cout << "Order" << id << "booked" << endl;
    }

    void CANCEL_ORDER()
    {
        int id;
        cout << "Enter the id of the order" << endl;
        cin >> id;
        priority_queue<pair<int, pair<string, vector<pair<string, int>>>>> temp;
        pair<int, pair<string, vector<pair<string, int>>>> p;
        while (!q.empty())
        {
            p = q.top();
            q.pop();
            if (p.first == id)
                break;
            temp.push(p);
        }

        string status = p.second.first;
        if (status == "BOOKED")
        {
            p.second.first = "CANCELLED";
            temp.push(p);
            while (!temp.empty())
            {
                q.push(temp.top());
                temp.pop();
            }
        }
        else
        {
            temp.push(p);
            while (!temp.empty())
            {
                q.push(temp.top());
                temp.pop();
            }
            cout << "The order wasnt booked first";
            return;
        }
        cout << "Cancelled booked orderlines for order " << id << endl;
    }
    void CANCEL_ORDER_LINE()
    {
        int id;
        cout << "Enter the id of the order" << endl;
        cin >> id;
        string str;
        cout << "Enter the product name" << endl;
        cin >> str;
        priority_queue<pair<int, pair<string, vector<pair<string, int>>>>> temp;
        pair<int, pair<string, vector<pair<string, int>>>> p;
        while (!q.empty())
        {
            p = q.top();
            q.pop();
            if (p.first == id)
                break;
            temp.push(p);
        }

        string status = p.second.first;
        vector<pair<string, int>> vec = p.second.second;
        vector<pair<string, int>> copy;
        for (auto ele : vec)
        {
            if (ele.first == str)
                continue;
            else
                copy.push_back({ele.first, ele.second});
        }
        p.second.second = copy;
        temp.push(p);
        while (!temp.empty())
            q.push(temp.top());

        cout << "CANCEL_ORDER_LINE" << id << " " << str << endl;
    }
};

int main()
{

    Ecommerce e;

    cout << "Welcome to the online shopping :" << endl;

    do
    {
        cout << "Enter the choice from the following options :-1)Addinventory 2)SHOW_INVENTORY 3)CREATE_ORDER  4)ADD_ORDERLINE  \n 5)SHOW_ORDER 6)SHOW_ORDERS 7)IS_ORDER_BOOKABLE 8)BOOK_ORDER exit(presss -1)" << endl;
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            e.Addinventory();
            break;

        case 2:
            e.SHOW_INVENTORY();
            break;
        case 3:
            e.CREATE_ORDER();
            break;
        case 4:
            e.ADD_ORDERLINE();
            break;
        case 5:
            e.SHOW_ORDER();
            break;
        case 6:
            e.SHOW_ORDERS();
            break;
        case 7:
            if (e.IS_ORDER_BOOKABLE())
                cout << "True" << endl;
            else
                cout << "False" << endl;
            break;
        case 8:
            e.BOOK_ORDER();
            break;

        default:
            break;
        }

        if (ch == -1)
            break;

    } while (true);

    return 0;
}