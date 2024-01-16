(* Programming Languages: Coursework 1 *)
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
	| x :: xs -> 
		if p x 
		then all p xs
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



(* Q2a *)
(* extract min function that uses seperate modular functions for each process *)

(* append and reverseList funcions for reversing the list *)

let rec append xs ys =
    match xs with
    | [] -> ys
    | head :: tail -> head :: (append tail ys);;

let rec reverseList xs =
    match xs with
    | [] -> []
    | head :: tail -> append (reverseList tail) [head];;

(* findMind takes in an accumulator and a list
	and outputs the smallest element in the list *)

let rec findMin acc xs =
	match xs with
	| [] ->  acc
	| head :: tail -> 
		if head < acc
		then findMin head tail
		else findMin acc tail;;

(* removeMin takes a value, a list and an accumulator list,
	from head to tail, it removes any elements lower than the min argument
	and returns the list without the smallest element *)

let rec removeMin min xs accList =
	match xs with
	| [] -> accList
	| head :: tail -> 
		if head > min
		then removeMin min tail (head :: accList)
		else removeMin min tail accList;;

(* extractMin takes a list,
	will use the above functions to find and remove the smallest element in a list
	it then outputs a touple of the smallest element and the rest of the list *)

let extractMin xs =
	match xs with
	| [] -> failwith "empty list"
	| head :: tail -> 
		let min = findMin head tail in
		(min, reverseList (removeMin min xs []));;


(* compact form of extractMin function that is entirely self contained,
	but isn't modular, is less readable, and actively mutates the list during the program *)

let rec extractMinCompact xs =
	match xs with
	| [] -> failwith "empty list"
	| [x] -> (x, [])
	| head :: tail ->
		let (smallest, rest) = extractMinCompact tail in
			if head < smallest
			then (head, tail)
			else (smallest, head :: rest);;

(* I prefer the first implementation as it is more modular and readable *)


(* Q2b *)
(* extractSort takes output from extractMin and appends the smallest at the start of the list,
	then iterates the same down the rest of the list *)

let extractSort xs =
	match xs with
	| [] -> []
	| _ ->
		let (smallest, rest) = extractMin xs in
		smallest :: extractSort rest;;


(* Q2c *)

(* 
	extractSort [2; 3; 1];;
	
		this calls; extractMin [2; 3; 1]
		which calls; findMin 2 [3; 1]
			this iterates to the base case and returns the value 1
		then removeMin 1 [2; 3; 1] [] is called,
		which returns [3; 2]
		then extractMin returns (1, [3; 2])
		
	extractSort then starts a list with [1]
	the recursive call then calls extractSort [3; 2]

		the same functions apply,
		where extractMin [3; 2] returns (2, [3])

	extractSort then adds 2 onto the list, thus [1; 2]
	the recursive call then calls extractSort [3]

		the same functions apply,
		where extractMin [3] returns (3, [])

	extractSort then adds 3 onto the list, thus [1; 2; 3]
	the recursive call then calls extractSort []

		the base case returns []

	the sorted list thus outputs [1; 2; 3]
 *)


(* Q2d *)

(* 
	extractMin

		tail recursion: extractMin is tail recursive because the recursive call is the last
						operation, and there isn't any operations pending after the recursive call
		
		garbage: it does create garbage as it creates a new list for each recursive call
				and it also creates new parameters and variables in each recursive call






	extractSort

		tail recursion: extractSort is tail recursive because the recursive call is the last
						operation, and there isn't any operations pending after the recursive call

		garbage: it does create garbage as it creates a new list for each recursive call
				and it also creates new parameters and variables in each recursive call
*)



(* Part 1 Q3a *)


(* function to find the volume capacity of the specified jar *)
let rec extractVolume xs n =
	match xs with
	| [] -> failwith "empty list"
	| head :: tail -> 
		if n = 0 
		then head
		else extractVolume tail (n-1);;

(* function to change the current volume within a specified jar *)
let rec setVolume xs targetVolume n =
	match xs with
	| [] -> []
	| head :: tail ->
		if n = 0
		then targetVolume :: tail
		else head :: setVolume tail targetVolume (n-1);;


(* creates a type, with 3 possibilies, 2 that take an integer and another that takes a touple of int's *)
type move = Fill of int | Drain of int | Transfer of int * int

(* pattern matches for the type move *)
let rec doMove jarVolumes jarContents move =
	match move with
	| Fill n -> 
		(* sets the volume of the target jar, to the maximum capacity of that jar *)
		setVolume jarContents (extractVolume jarVolumes n) n
	| Drain n -> 
		(* simply sets the contents of the jar to empty *)
		setVolume jarContents 0 n
	| Transfer (m, n) ->
		(* defined a couple nested functions to make the if then else statement more readable *)

		(* calculates the empty space left in the jar n *)
		let emptySpaceIn_n = ((extractVolume jarVolumes n) - (extractVolume jarContents n)) in

		(* finds the current contents  in m and n *)
		let currentM = extractVolume jarContents m in
		let currentN = extractVolume jarContents n in

		(* creates simple functions to fill n and drain m *)
		let fillN = doMove jarVolumes jarContents (Fill n) in
		let drainM = doMove jarVolumes jarContents (Drain m) in

			(* checks if the contents of m would fill/overflow n *)
			if (currentM - emptySpaceIn_n)>= 0
			(* if m would overflow n, 
				recursively call to fill n to the max
				then set new content of m by subtracting ammount used to fill n *)
			then setVolume fillN (currentM - emptySpaceIn_n) m
			(* if m wouldnt overflow/fill n,
				recursively drains m
				then sets the new content of n by adding the content of m *)
			else setVolume drainM (currentN + currentM) n;;