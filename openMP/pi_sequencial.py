num_steps = 50000

soma = 0

step = 1 / num_steps

for i in range(num_steps):
    x = (i + 0.5 ) * step
    soma = soma + 4 / (1 + x * x)
print(soma)
input()
pi = step * soma

print(pi)
