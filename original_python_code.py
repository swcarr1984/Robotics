
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






