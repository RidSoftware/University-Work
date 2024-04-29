(* Programming Languages: Coursework 1/Q2 *)


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