' Here is a solution in QB64, or FreeBASIC (using -lang qb):
' Does not prompt for the seed, since BASIC has a built-in function for this.
' find the minimum value in an array of integers
' a recursive solution in C
' ed davis - 4/6/22
const ARR_SIZE = 16
dim arr(0 to ARR_SIZE) as integer
declare function randnum%(min as integer, max as integer)
declare function minarr%(arr() as integer, n as integer)
declare function minf%(x as integer, y as integer)
randomize timer
for i = 0 to ARR_SIZE
arr(i) = randnum(-100, 100)
print arr(i);
next
print
print minarr(arr(), ARR_SIZE)
function randnum%(min as integer, max as integer)
dim n as integer
n = rnd * (max - min + 1)
randnum% = (n mod (((max) + 1) - (min))) + min
end function
function minarr%(arr() as integer, n as integer)
if n = 0 then minarr% = arr(0) else minarr% = minf%(arr(n - 1), minarr%(arr(), n - 1))
end function
function minf%(x as integer, y as integer)
if x < y then minf% = x else minf% = y
end function

