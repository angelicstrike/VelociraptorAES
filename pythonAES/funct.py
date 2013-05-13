def changer(value, stuff):
    stuff = value
    stuff[0] += 1

value = [1,2,3]
stuff = [1,2,3]
print value
changer(value, stuff)
print value
print stuff

