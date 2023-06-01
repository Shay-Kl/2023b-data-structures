#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__

class Customer
{
public:
    Customer(int id, int phone);

    //returns true if customer is a member
    bool isMember();

    //Returns customer's id
    int getId();

    //Returns customer's phone number
    int getPhone();

    //Returns customer's expenses total
    int getExpenses();

    //Increases expenses by a given amount if the customer is a member
    //Does nothing otherwise
    void pay(int amount);

    //Discounts expenses by given amount
    void discount(int amount);

    //Resets expenses to 0
    void resetExpenses();

    //Make customer a member
    void makeMember();

private:
    int m_id;
    int m_phone;
    bool m_isMember;
    int m_expenses;
};


#endif // __CUSTOMER_H__