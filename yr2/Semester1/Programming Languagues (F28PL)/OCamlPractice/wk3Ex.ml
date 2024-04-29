ex
3 + 2x + 5x^2 + 7x^3
[0;3;2;5;7]

(*problem
Leading zero
there is always a leading zero that must be eliminated
*)



(*problem
As we dont know if 0 is part of the polynomial or not
the isPoly function below checks if it ends with a zero which shows if it is a polynomial*)

let rec isPoly p =
	let rec helper p b =
	match p with
	| [] -> not b
	| a :: p1 ->
		if a = 0
		then helper p1 true
		else helper p1 false
	in helper p false;;
	
	
	
let x = [1,2,3] in
	let rec checkNum x =
	match x with
	| [] -> "empty list"
	| 1 -> "1"
	| 2 -> "2"
	| 3 -> "3";;
	


(*Test*)
((4,2), [(4,2);(4,2)])

let x = (4,2) in
	(x,[x;x]);;
	
	
(*Excersises*)



let ys =
	match xs with
	| [] -> []
	| _ :: zs -> zs;;



0.1)let xs = zip [1;2] [true; false] in
	let ys =
	match xs with
	| [] -> []
	| _ :: zs -> zs
	in (xs, ys);;
	
1)
let take n xs = n :: xs;;

let rec drop n xs =
if n>0 then
	match xs with
	| [] -> []
	| _ :: xs -> drop (n-1) xs
else xs;;

2)
let rec isSorted xs =
match xs with
	| 1stElement :: 2ndElement :: [] -> if 1stElement <= 2ndElement then true else false
	| 1stElement :: 2ndElement :: tail -> if 1stElement <= 2ndElement then isSorted 2ndElement :: tail else false;;
(*Note literals nthElement invalid as starts with number*)
(*Note this is simple implementation of recursive functions*)

3)
(*Note integrate drop recursive function with length of list from tail to head taking sorted value held in a counter for each unsorted value, then analyze big-o notation to optimize*)

let rec insert e list =
	match list with
	| [] -> [e]
	| head :: tail -> if e >= head then
				e :: list 
			else 
				head :: (insert e tail);;

let rec insertSort list =
	match list with
	| head :: tail -> insert head (insertSort tail)
	| []->[];;

4)
(*try recursive function checking from end if elemets ==, then iterate down until either sublist ends or !==*)


(*must pass head of sublist to seperate match, try diff function*)


let rec headCheck xs ys =
	match ys with
	| [] -> []
	| head :: tail -> 
		if head = (tempAux xs ys)
		then headCheck xs tail
		
		else false
		
		;;



(*must pass number of iterations, to ensure that the greater list is compared when recursivelyu called instead of calling to match new element with old head *)


[1;2;3]
[1;2]



(*problem; head is single element -> thus, must recursivly construct the sublist after each headCheck*)


let rec subListConstructor xs ys =
	match ys with
	| [] -> []
	| head :: tail -> headCheck (head :: xs)



















let rec tempAux xs ys =
	match xs with
	| [] -> []
	| head :: tail -> head;;
 


