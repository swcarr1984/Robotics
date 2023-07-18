
# MEC4406

# 1 Function that writes your name and counts to favourite number squared

def myFunction(name,fav_number):
    print("My name is", name)
    count = 0
    for i in range(fav_number*fav_number):
        count = count+1
        if count == fav_number**2:
            print("My favourite number is",fav_number,'when squared it equals',i)
    
myFunction('Scott', 27)

class Engineer:
    def __init__(self,name, type, years_of_experience):
        self.skill = "problem solver"
        self.name = name
        self.type = type
        self.years_of_experience = years_of_experience

    def getName(self):
        return self.name
    def getType(self):
        return self.type
    def getskill(self):
        return self.skill
    def getyears_of_experience(self):
        return self.years_of_experience

eng1 = Engineer("Jim","Instrument",2)
print(eng1.getName(),":",eng1.getskill(),":",eng1.getType(),":",eng1.getyears_of_experience())

eng2 = Engineer("Johan","Computer",4)
print(eng2.getName(),":",eng2.getskill(),":",eng2.getType(),":",eng2.getyears_of_experience())







