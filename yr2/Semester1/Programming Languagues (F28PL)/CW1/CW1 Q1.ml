(* Programming Languages: Coursework 1/Q1 *)
(* Used Functions *)

let isEven n =
n mod 2 = 0;;

let rec foldRight f xs acc =
	match xs with
	| [] -> acc
	| head :: tail -> f head (foldRight f tail acc);;

let rec foldLeft f acc xs =
	match xs with
	| [] -> acc
	| head :: tail -> foldLeft f (f acc head) tail;;



(* Q1a *)
(* p is a function, xs is a list recursive function, which checks every element of the list to see if it satisfies a predicate function, if it reaches the base case, then it satisfies the predicate for each element *)

let rec all p xs =
	match xs with
	| [] -> true
	| head :: tail -> 
		if p head 
		then all p tail
		else false;;


(* Q1b *)
(* similar to Q1a,
	var p = predicate function
	var xs = list to be evaluated against predicate
	var acc = accumulator to pass if predicate is satisfied
	var element = element to be checked against the predicate

	exists gives the function checkPredicate to foldLeft,
	where if p element is satisfied; true is returned,
	else foldLeft will continue until either p is satisfied,
	or all elements have been checked then returning false *)

let exists p xs =
	let checkPredicate acc element =
		if p element 
		then true 
		else acc
	in foldLeft checkPredicate false xs;;


(* Q1c *)
(* same as exists;
	but inverses the fold to continue until,
	it finds a case that doesnt satisfy the predicate *)

let allF p xs =
	let checkPredicate acc element =
		if p element 
		then acc 
		else false
	in foldLeft checkPredicate true xs;;

(* all and allF behave the same on inputs
	with the exception of [] - an empty list
	the all function handles the case of an empty list seperately from all other cases
	whereas allF treats it the same as all other inputs and outputs the acc as

	to make allF match the behaviour of all
	allF should handle [] case seperately with:
	
	let allF p xs =
		match xs with
		| [] -> true
		| _ -> let checkPredicate acc element =
					if p element 
					then acc 
					else false
				in foldLeft checkPredicate true xs;; *)


(* Q1d *)
(* member matches each element of the list with the element x
	if they match then return true,
	otherwise it will iterate through each element of the list *)

let rec member x xs =
	match xs with
	| [] -> false
	| head :: tail -> 
		if x = head
		then true
		else member x tail;;

(* takes a perdicate function and a list,
	runs either all or exists function
	with the args; a function that evaluates if each element
	is a member of the list AND if it satisfies the predicate*)

let allSpec p xs =
	all (function x -> member x xs && p x) xs;;

(* type of var allSpec: ('a -> bool) -> 'a list -> bool *)

let existsSpec p xs =
	exists (function x -> member x xs && p x) xs;;

(* type of var existsSpec: ('a -> bool) -> 'a list -> bool *)
