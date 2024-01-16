LN)
(* if i want to campare elements i need a seperate function to breack off a element and give it to me *)


let append xs ys =
	match ys with
	| [] -> []
	| x :: xs -> append xs (x :: ys)




let rec quickSort xs =
	match xs with
	| [] -> []
	| xHead :: xs ->
		let small = keepSmaller xHead xs in
		let large = keepLarger xHead xs in
		let ssmall = quickSort small in
		let slarge = quickSort large in
		append small (xHead :: slarge)
		
let rec keepSmaller p xs =
	match xs with
	| [] -> []
	| head :: tail -> if p > head then
				keepSmaller head tail
			else keepSmaller p tail
	
	
	
	
let rec keepLarger p xs =
	match xs with
	| [] -> []
	| head :: tail -> if p < head then
				keepSmaller head tail
			else keepSmaller p tail
	
let rec filter p xs =
	match xs with
	| [] -> []
	| x :: xs ->
		if p x
		then x :: filter p xs
		else filter p xs
		
let add n =
	n mod 2 <> 0 ;;
	
	
	
	










































