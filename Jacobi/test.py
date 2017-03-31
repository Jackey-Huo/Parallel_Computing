#! /usr/bin/python
import random

t_step = random.randint(10, 50)
x_dim  = random.randint(10, 500)
y_dim  = random.randint(10, 500)
z_dim  = random.randint(10, 500)

print t_step
print x_dim
print y_dim
print z_dim


buff = [  ]

for z in range(z_dim):
    for y in range(y_dim):
        buff = [  ]
        for x in range(x_dim):
            buff.append(random.uniform(-100, 1000000.0))
        print(" ".join(map(str, buff)))
    print ' '

