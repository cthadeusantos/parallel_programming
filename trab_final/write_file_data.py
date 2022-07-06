from random import randint

qtde = 15000000
f = open("data.txt", "w")
f.write(str(qtde) + '\n')
for x in range(qtde):
    integer = randint(0, qtde)
    f.write(str(integer) + '\n')
f.close()