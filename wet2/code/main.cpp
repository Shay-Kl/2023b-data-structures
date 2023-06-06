#include "utilesWet2.h"
#include "Customer.h"
#include "AVLtree.h"
#include "MemberTree.h"
#include "recordsCompany.h"
#include "RecordsPile.h"

void discountTest();
void unionFindTest();
void testin();

int main()
{
    testin();
    return 0;
}

void st(StatusType st)
{
    switch (st)
    {
    case SUCCESS:
        cout << "SUCCESS" << endl;
        break;
    case StatusType::ALLOCATION_ERROR:
        cout << "ALLOCATION_ERROR" << endl;
        break;
    case StatusType::ALREADY_EXISTS:
        cout << "ALREADY_EXISTS" << endl;
        break;
    case StatusType::DOESNT_EXISTS:
        cout << "DOESNT_EXISTS" << endl;
        break;
    case StatusType::FAILURE:
        cout << "FAILURE" << endl;
        break;
    case StatusType::INVALID_INPUT:
        cout << "INVALID_INPUT" << endl;
        break;
    }
}

void testin()
{
    RecordsCompany c;
    st(c.addCostumer(45115, 1108));
    st(c.addCostumer(18904, 94069));
    cout << c.getPhone(18904).ans() << endl;
    int* stock = new int[40]{19,16, 5, 10, 5 ,2 ,9 ,5, 8, 9, 15, 8, 8, 8, 11, 14, 4, 19, 9, 16, 2, 11, 3 ,6 ,7, 4 ,17, 10, 11, 4 ,17 ,12, 7 ,3 ,6, 4 ,5 ,1 ,5 ,4};
    st(c.newMonth(stock, 40));
    st(c.makeMember(18904));
    cout << ((c.isMember(45115).ans()) ? "TRUE" : "FALSE") << endl;
    st(c.makeMember(45115));
    st(c.buyRecord(18904, 32));
    st(c.buyRecord(45115, 5));
    cout << c.getExpenses(18904).ans() << endl;
    st(c.addPrize(28543, 50000, 45));
    cout << c.getExpenses(45115).ans() << endl;
    st(c.putOnTop(3, 28));
    st(c.putOnTop(28, 37));
    int height = 0, column = 0;
    st(c.getPlace(3, &column, &height));
    cout << "c:" << column << " h:" << height << endl;
    st(c.getPlace(28, &column, &height));
    cout << "c:" << column << " h:" << height << endl;
    st(c.getPlace(37, &column, &height));
    cout << "c:" << column << " h:" << height << endl;
}


//Identical to test.in test
void unionFindTest()
{
    int* stock = new int[40]{19,16, 5, 10, 5 ,2 ,9 ,5, 8, 9, 15, 8, 8, 8, 11, 14, 4, 19, 9, 16, 2, 11, 3 ,6 ,7, 4 ,17, 10, 11, 4 ,17 ,12, 7 ,3 ,6, 4 ,5 ,1 ,5 ,4};
    cout << "3: " << stock[3] << ", 28: " << stock[28] << ", 37: " << stock[37] << endl;
    RecordsPile pile = RecordsPile(stock, 40);
    pile.pileOnTop(3, 28);
    pile.pileOnTop(28, 37);
    cout << pile.getHeight(3) << ", " << pile.getHeight(28) << ", " << pile.getHeight(37) << endl; //12,1,0
    cout << pile.getColumn(3) << ", " << pile.getColumn(28) << ", " << pile.getColumn(37); //37,37,37
}

void discountTest()
{
    MemberTree tree;
    for (int i = 0; i < 10; i++)
    {
        Customer* c = new Customer(i, 0);
        tree.insert(c);
    }

    tree.addPrize(2, 7, 5);
    tree.addPrize(-20, 4, 3);

    cout << tree;

    tree.resetExpenses();

    cout << tree;
}