(* Q3a *)
(* a tuple of 2 lists, representing the place of the pointer being inbetween the 2 lists *)
type 'a place = 'a list * 'a list;;



(* Q3b *)
(* exception for when an index outside the scope of the list is given, of 
	type int to display which index is invalid *)
exception InvalidIndex of int;;

(* implementation of length recursively accumulates +1 for each element of the list *)
let length xs =
	let rec aux xs acc =
		match xs with
		|[] -> acc
		|_::tl -> aux tl (acc+1) 
	in
	aux xs 0
;;

(* recursively counts through list to the index(pointer) and accumulates the list up to the index *)
let getPrevList xs n =
	let rec aux xs n acc accList =
		match xs with
		|[] -> accList
		|hd::tl ->
			if acc = n
			then accList
			else aux tl n (acc+1) (accList @ [hd])
	in
	aux xs n 0 []
;;

(* recusively counts through list to the index(pointer) instead of accumulating a list, the tail after the index is returned *)
let getNextList xs n =
	let rec aux xs n acc =
		match xs with
		|[] -> xs
		|_::tl -> 
			if acc = n 
			then xs
			else aux tl n (acc+1)
	in
	aux xs n 0
;;

(* takes in a list and an index, then constructs a place(tuple) by calling getPrevList and getNextList
	returns exception if index is too big/small *)
let getPlace xs n =
	if n < 0 || n > length xs
	then raise (InvalidIndex n)
	else (getPrevList xs n, getNextList xs n)
;;

(* simply appends the 2 lists in the place(tuple) together into a list *)
let collapse p =
	match p with
	(prevList, afterList) -> prevList @ afterList
;;

(* checks if the prevList of the place is empty *)
let isStart p =
	match p with
	|([], _) -> true
	|_ -> false
;;

(* checks if the afterList of the place is empty *)
let isEnd p =
	match p with
	|(_, []) -> true
	|_ -> false
;;

(* exceptions for if a function is performed outside the scope of the list *)
exception EndOfList;;
exception StartOfList;;

(* implementation of a recursive list reverser *)
let reverseList xs =
	let rec aux xs accList =
		match xs with
		|[] -> accList
		|hd::tl -> aux tl (hd::accList)
	in 
	aux xs []
;;

(* returns the place after the place given, by appending the head of the afterList onto the end of the prevList
	then setting the tail of the afterList as the new afterList *)
let next p = 
	match p with
	|(_, []) -> raise EndOfList 
	|(prevList, hd::tl) -> 
		(prevList @ [hd], tl)
;;

(* returns the place before the place given, by setting the tail of the reversed prevList as the new prevList
	then appnding the head at the front of the afterList as the new afterList *)
let prev p =
	match p with
	|(prevList, afterList) ->
		match reverseList prevList with
		|[] -> raise StartOfList
		|hd::tl -> (tl, hd::afterList)
;;

(* returns the head of the afterList as the element after the place *)
let lookup p =
	match p with
	|(_, []) -> raise EndOfList
	|(_, hd::_) -> hd
;;

(* returns updated place, with the head of the afterList removed *)
let delete p =
	match p with
	|(_, []) -> raise EndOfList
	|(prevList, hd::tl) -> (prevList, tl)
;;

(* appends x onto the end of the prevList and returns the updated place *)
let insert x p =
	match p with
	|(prevList, afterList) -> (prevList @ [x], afterList)
;;

(* Q3c *)
(* I chose to represent 'a place as a tuple of two lists 
	as the place is meant to represent the point between 2 elements,
	thus spliting the list into 2 at the point of the place is logical.

	It enables efficient implementation of the functions required as most 
	functions require access to the elements immediately preceeding/after the place
	so storing the place as to lists mean that evaluating the head of the lists gives access
	to the elements most often needed to work with
 *)