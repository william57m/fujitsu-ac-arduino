# Analyze last IR sequence

(0=regular, 1=on)
(0=auto, 1=cool, 2=dry, 3=fan)
(0=auto, 1=high, 2=med, 3=low, 4=quiet)

MODE           ADDITION MODE     BINARY VALUE FROM THE SEQUENCE

auto/auto      0+0 = 0           0 0 0 0 = 0

auto/high      0+1 = 1           1 1 1 1 = 15
auto/med       0+2 = 2           0 1 1 1 = 14
auto/low       0+3 = 3           1 0 1 1 = 13
auto/quiet     0+4 = 4           0 0 1 1 = 12 

cool/auto      1+0 = 1           1 1 1 1 = 15
cool/high      1+1 = 2           0 1 1 1 = 14
cool/med       1+2 = 3           1 0 1 1 = 13
cool/low       1+3 = 4           0 0 1 1 = 12
cool/quiet     1+4 = 5           1 1 0 1 = 11   

dry/auto       2+0 = 2           0 1 1 1 = 14   

fan/auto       3+0 = 3           1 0 1 1 = 13
fan/high       3+1 = 4           0 0 1 1 = 12
fan/med        3+2 = 5           1 1 0 1 = 11
fan/low        3+3 = 6           0 1 0 1 = 10
fan/quiet      3+4 = 7           1 0 0 1 = 9   

on/auto/auto   1+0+0 = 1         1 1 1 1 = 15
on/auto/high/  1+0+1 = 2         0 1 1 1 = 14
on/auto/med/   1+0+2 = 3         1 0 1 1 = 13
on/auto/low/   1+0+3 = 4         0 0 1 1 = 12
on/auto/quiet  1+0+4 = 5         1 1 0 1 = 11

on/cool/auto   1+1+0 = 2         0 1 1 1 = 14
on/cool/high   1+1+1 = 3         1 0 1 1 = 13
on/cool/med    1+1+2 = 4         0 0 1 1 = 12
on/cool/low    1+1+3 = 5         1 1 0 1 = 11
on/cool/quiet  1+1+4 = 6         0 1 0 1 = 10

The binary value is always the same for the sum of the mode.
