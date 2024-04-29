(* Programming Languages: Coursework 1/Q3 *)

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
type move = Fill of int | Drain of int | Transfer of int * int;;

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
			then
				setVolume fillN (currentM - emptySpaceIn_n) m
			(* if m wouldnt overflow/fill n,
				recursively drains m
				then sets the new content of n by adding the content of m *)
			else setVolume drainM (currentN + currentM) n;;



(* Q3 1b *)
(* simple recursive function that matches the head of each list passed through to see if it = target value
	if not found then, returns false *)

let rec check target xs =
	match xs with
	| [] -> false
	| head :: tail -> 
		if head = target
		then true
		else check target tail;;

(* Q3 1c *)
(*  *)

let rec length xs =
    match xs with
	| [] -> 0
	| _ :: xs -> 1 + length xs;;

let rec createEmptyJars n acc =
  if n <= 0 then
    acc
  else
    createEmptyJars (n - 1) (0 :: acc);;

let rec run xs target movelist =
	let currentJars = createEmptyJars (length xs) [] in
	match movelist with 
	| [] -> check target xs
	| head :: tail -> 
		(doMove xs currentJars head) 
		run xs target tail;;

let rec run xs target movelist =
	let currentJars = createEmptyJars (length xs) [] in
	match movelist with 
	| [] -> check target 
	| head :: tail -> 
		doMove xs jarContents head :: run xs target;;

