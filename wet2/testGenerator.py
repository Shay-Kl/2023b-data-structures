import random

id_range = 250

class Customer:
    def __init__(self, id,phone):
        self.id = id
        self.phone = phone
        self.expenses = 0
        self.member = False
        
class Record:
    def __init__(self, id, copies):
        self.id = id
        self.copies = copies
        self.cost = 100
        self.onTopOf = -1
        self.stackTop = self
    def root(self):
        if self.onTopOf == -1:
            return self
        else:
            return self.onTopOf.root()
    def height(self):
        if self.onTopOf == -1:
            return 0
        else:
            next = self.onTopOf
            return next.height() + next.copies

def newMonth(customers, records):
    input = "newMonth "
    output = "newMonth: "
    count = random.randint(5,40)
    
    for customer in customers.values():
        customer.expenses = 0
    records.clear()
    for i in range(0, count):
        record = Record(i, random.randint(1,20))
        records.append(record)
    output+="SUCCESS"
    input+=str(count)+" ["
    for i in range(0, count-1):
        input+= str(records[i].copies) + " "
    input+=str(records[count-1].copies)+"]"
    return input, output

def addCustomer(customers, records):
    input = "addCostumer "
    output = "addCostumer: "
    
    key = random.randint(-5, id_range)
    phone = random.randint(-5, id_range)
    input+=str(key)+" "+str(phone)
    if (key < 0) or (phone < 0):
        output+="INVALID_INPUT"
    elif key in customers.keys():
        output+="ALREADY_EXISTS"
    else:
        customers[key] = Customer(key, phone)
        output +="SUCCESS"
    return input, output

def getPhone(customers, records):
    input = "getPhone "
    output = "getPhone: "
    rand = random.random()
    if rand > 0.9:
        id = random.randint(0, id_range)
        while id in customers.keys():
            id = random.randint(0, id_range)
        output+="DOESNT_EXISTS"
    elif rand > 0.8:
        id = random.randint(-100, -1)
        output+="INVALID_INPUT"
    else:
        customer = random.choice(list(customers.values()))
        output+=str(customer.phone)
        id = customer.id
    input+=str(id)
    return input, output

def makeMember(customers, records):
    input = "makeMember "
    output = "makeMember: "
    rand = random.random()
    if rand > 0.9:
        id = random.randint(0, id_range)
        while id in customers.keys():
            id = random.randint(0, id_range)
        output+="DOESNT_EXISTS"
    elif rand > 0.8:
        id = random.randint(-100, -1)
        output+="INVALID_INPUT"
    else:
        customer = random.choice(list(customers.values()))
        if customer.member:
            output+="ALREADY_EXISTS"
        else:
            customer.member = True
            output+="SUCCESS"
        id = customer.id
    input+=str(id)
    return input, output

def isMember(customers, records):
    input = "isMember "
    output = "isMember: "
    rand = random.random()
    if rand > 0.9:
        id = random.randint(0, id_range)
        while id in customers.keys():
            id = random.randint(0, id_range)
        output+="DOESNT_EXISTS"
    elif rand > 0.8:
        id = random.randint(-100, -1)
        output+="INVALID_INPUT"
    else:
        customer = random.choice(list(customers.values()))
        output+=str(customer.member)
        id = customer.id
    input+=str(id)
    return input, output

def buyRecord(customers, records):
    input = "buyRecord "
    output = "buyRecord: "
    
    rand = random.random()
    if rand > 0.9:
        if rand > 0.95:
            cid = random.randint(0, id_range)
            while cid in customers.keys():
                cid = random.randint(0, id_range)
            rid = random.choice(records).id
        else:
            cid = random.choice(list(customers.values())).id
            rid = random.randint(len(records), len(records)+10)
        output+="DOESNT_EXISTS"
    elif rand > 0.8:
        if rand > 0.85:
            rid = random.choice(records).id
            cid = random.randint(-100, -1)
        else:
            cid = random.choice(list(customers.values())).id
            rid = random.randint(-100, -1)
        output+="INVALID_INPUT"
    else:
        customer = random.choice(list(customers.values()))
        record = random.choice(records)
        if customer.member:
            customer.expenses+=record.cost
        record.cost+=1
        cid = customer.id
        rid = record.id
        output+= "SUCCESS"
    input+=str(cid)+" "+str(rid)
    return input, output

def addPrize(customers, records):
    input = "addPrize "
    output = "addPrize: "
    
    low = random.randint(-20, id_range)
    high = random.randint(0, id_range+100)
    prize = random.randint(1, 100)
    
    input+=str(low)+" "+str(high)+" "+str(prize)
    
    if (low < 0) or (high < low) or (prize <= 0):
        output+="INVALID_INPUT"
    else:
        for customer in customers.values():
            if (customer.id >= low) and (customer.id < high) and (customer.member):
                customer.expenses-=prize
        output+="SUCCESS"
    return input, output

def getExpenses(customers, records):
    input = "getExpenses "
    output = "getExpenses: "
    rand = random.random()
    if rand > 0.9:
        id = random.randint(0, id_range)
        while id in customers.keys():
            id = random.randint(0, id_range)
        output+="DOESNT_EXISTS"
    elif rand > 0.8:
        id = random.randint(-100, -1)
        output+="INVALID_INPUT"
    else:
        customer = random.choice(list(customers.values()))
        if not customer.member:
            output+="DOESNT_EXISTS"
        else:
            output+=str(customer.expenses)
        id = customer.id
    input+=str(id)
    return input, output
        

def putOnTop(customers, records):
    input = "putOnTop "
    output = "putOnTop: "
    rec1 = random.randint(-1, len(records)+2)
    rec2 = random.randint(-1, len(records)+2)
    input+=str(rec1)+" "+str(rec2)
    if (rec1 < 0) or (rec2 < 0):
        output+="INVALID_INPUT"
    elif (rec1 >= len(records)) or (rec2 >= len(records)):
        output+="DOESNT_EXISTS"
    else:
        root1 = records[rec1].root()
        root2 = records[rec2].root()
        if root1==root2:
            output+="FAILURE"
        else:
            output+="SUCCESS"
            root1.onTopOf = root2.stackTop
            root2.stackTop = root1.stackTop
    return input, output

def getPlace(customers, records):
    input = "getPlace "
    output = "getPlace: "
    rec = random.randint(-2, len(records)+4)
    input+=str(rec)
    if rec<0:
        output+="INVALID_INPUT"
    elif rec >= len(records):
        output+="DOESNT_EXISTS"
    else:
        column = records[rec].root().id
        height = records[rec].height()
        output+="column="+str(column)+", hight="+str(height)
    return input,output

def generateTest(number, lines):
    customers = {}
    records = []
    
    input, output = newMonth(customers, records)
    
    for i in range(3):
        tempin, tempout = addCustomer(customers, records)
        input+="\n"+tempin
        output+="\n"+tempout
    
    commands = (addCustomer, getPhone, makeMember,
                isMember, buyRecord, addPrize,
                getExpenses, putOnTop, getPlace)
    for i in range(1,lines):
        if random.random() > 0.999:
            tempin, tempout = newMonth(customers, records)
            input+="\n"+tempin
            output+="\n"+tempout
        print(i)
        command = random.choice(commands)
        tempin, tempout = command(customers, records)
        input+="\n"+tempin
        output+="\n"+tempout
        

    with open("inFiles/test"+str(number)+".in", mode="w") as file:
        file.write(input+"\n")
    with open("outFiles/test"+str(number)+".out", mode="w") as file:
        file.write(output+"\n")
for i in range(1, 10):
    generateTest(i, 100)
for i in range(10, 50):
    generateTest(i, 1000)
for i in range(50, 100):
    generateTest(i, 5000)
