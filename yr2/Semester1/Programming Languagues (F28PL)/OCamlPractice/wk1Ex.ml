let twice n = n+n

let rec fact n = 
	if n = 0
	then n + 1
	else n * fact (n - 1)
	
	???
let rec loop _ = loop ()
	
let explode _ = 1 + explode ()	

let divides m n = 
	n mod m = 0
	
let rec gcd m n =
	if n = 0
	then m
	else gcd n (m mod n)



Excersises

1) skipped

2) 
let isEven x = 
	if x mod 2 = 0
	then true
	else false

let isOdd x = 
	if isEven x = false
	then true 
	else false
	
3) skipped

4)
let myOr p q = 
	if p 
	then true 
	else q;;

let myAnd p q =
	if p and q
	then true
	else false;;
	
let myNot p =
	if p
	then false
	else p;;
	
let myXor p q =
	if p 
	then 
		if q
		then false
		else true
	else
		if q
		then true
		else false;;
		
5)
let rec collatz n =
	if n = 1
	then 1
	else
		if n mod 2 = 0
		then collatz (n/2)
		else collatz (3*n + 1);;
		
6)
let rec lcm x y =
		
		
		
		
		
		
		
