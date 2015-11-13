#!/usr/bin/python
import math

print "{",

for num in range(0,181):
        print("%d," % int(round(math.sin(math.radians(180-num))*158) )),

print "}"
print ""

print "{",

for num in range(0,181):
        print("%d," % int(round(math.cos(math.radians(181-num))*158)+160 )),

print "}",
