#!/usr/bin/env python

import math as M
import sys

abc = sys.argv[1:]

a = float(abc[0])
b = float(abc[1])
c = float(abc[2])

s1 = '-'
s2 = '-'

if b > 0:
	s1 = '+'

if c > 0:
	s2 = '+'

print a,'* x^2',s1, abs(b),'* x',s2,abs(c)

d = b * b - 4 * a * c
x1 = (-b + M.sqrt(d)) / (2*a)
x2 = (-b - M.sqrt(d)) / (2*a)

print d
print x1
print x2
