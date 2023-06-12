#include "Customer.h"

Customer::Customer(int id, int phone): m_id(id), m_phone(phone), m_isMember(false), m_expenses(0.0) {}

bool Customer::isMember()
{
    return m_isMember;
}

int Customer::getId()
{
    return m_id;
}

int Customer::getPhone()
{
    return m_phone;
}

double Customer::getExpenses()
{
    return m_expenses;
}

void Customer::pay(double expense)
{
    if (m_isMember)
    {
        m_expenses+=expense;
    }
    
}

void Customer::discount(double amount)
{
    if (m_isMember)
    {
        m_expenses-=amount;
    }
    
}

void Customer::resetExpenses()
{
    m_expenses = 0;
}

void Customer::makeMember()
{
    m_isMember = true;
    m_expenses = 0;
}