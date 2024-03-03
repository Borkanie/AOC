from math import sqrt

a = -1
b = 38677673
c = -234102711571236
tmin = int((-b + sqrt(b*b - 4 * a * c))/(2*a)+1)
max = int(b/2)
print(int(tmin))
print(b*b/2)
print(c)
print("Result  = ")
print( b - tmin)
print( tmin)
print( b - tmin*2 +1)
