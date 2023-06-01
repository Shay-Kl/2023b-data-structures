#include "utilesWet2.h"
#include "Customer.h"
#include "AVLtree.h"
#include "MemberTree.h"
#include "recordsCompany.h"

void discountTest();

int main()
{
    discountTest();
    return 0;
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