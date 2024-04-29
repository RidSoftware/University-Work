(*CW2*)

(* types for file directories *)
type ftree = Dir of string * ftree list
			|File of string;;

type path = string list;;


let fs =
Dir (" root " ,
[ Dir (" desktop " , [ Dir (" emptydir " , [])
; File " doc1 "
; File " notes "
])
; Dir (" documents " , [ File " notes "
; File " text1 "
])
; File " file1 "
; File " file2 "
])


let rec foldLeft f acc lst =
    match lst with
    | [] -> acc
    | head :: tail -> foldLeft f (f acc head) tail
;;



(* Q1a *)

(* count the amount of files with the desired filename *)
let rec numFiles (filename: string) (fs: ftree) =
	(* helper function  *)
	let helper acc f = acc + numFiles filename f in
	match fs with
	|File fn -> 
		if filename = fn
		then 1
		else 0
	|Dir (fn, sfs) ->
		foldLeft helper 0 sfs
;;

(* function to count the number of directories in the filesystem in total *)
let rec numDirs (fs: ftree) =
	let helper acc f =
		acc + numDirs f
	in

	match fs with
	|Dir (name,sfs) -> 1 + foldLeft helper 0 sfs
	|_ -> 0
;;


(* Q1b *)

(* checks if a given path is avalid for the sepcified file system *)
let rec validPath (p: path) (fs: ftree) =
	match p with
	|[] -> false
	|[name] -> 
		(match fs with
		|File fn -> fn = name
		|Dir (dn, sfs) -> dn = name)

	|hd :: tl -> 
		(match fs with
		|File fn -> 
			fn = hd && validPath tl fs

		|Dir (fn, sfs) -> 
			if fn = hd
			then validPath tl fs
			else false)
;;


(* Q1c *)

(* return true if an element is found within the list *)
let rec mtch (e: 'a) (lst: 'a list) =
	match lst with
	|[] -> false
	|hd :: tl -> 
		if e = hd
		then true
	else mtch e tl
;;


(* checks if there are any duplicates in the list, returns true if no duplicates *)
let rec nodupes (lst: 'a list) =
	match lst with
		|[] -> true
		|hd :: tl ->
			if (mtch hd tl)
			then false
			else nodupes tl
;;


(* check that nodupes is true for a subsection of the file system *)
let rec validFileSystemLocal (fs: ftree list) accDn accFn =
	match fs with
	|[] -> nodupes(accDn) && nodupes(accFn)
	|hd :: tl ->
		match hd with
		|File fn ->
			validFileSystemLocal tl accDn (fn :: accFn)
		|Dir (dn, _) -> 
			validFileSystemLocal tl (dn::accDn) accFn
;;

(* controls when to run validFileSystemLocal as it traverses through the filetree *)
let rec validFileSystem (fs: ftree list) =
	if (validFileSystemLocal fs [] [])
	then 
		(match fs with
			|[] -> true
			|hd :: tl ->
				validFileSystem tl &&
				(match hd with
				|Dir (dn, sfs) -> 
					validFileSystem sfs
				|File fn -> true))
	else false
;;

(* basic front facing function for validTree *)
let rec validTree (fs: ftree) =
	match fs with
	|File fn -> true
	|Dir (dn, sfs) ->
		validFileSystem sfs
;;


(* Q1d *)

(* helper function to append lists *)
let rec listAppend lst1 lst2 =
	match lst1 with
	|[] -> lst2
	|hd :: tl -> hd :: (listAppend tl lst2)
;;

(* helper function to reverse contents of list *)
let rec reverseList lst =
	let rec aux acc lst =
		match lst with
		|[] -> acc
		|hd :: tl ->
			aux (hd :: acc) tl
		in
	aux [] lst
;;

(* traverses through a given file tree and produce list of the path traversed *)
let rec traverser (accPath: path) (sfs: ftree) : path list =
	match sfs with
	|File fn -> [reverseList (listAppend [fn] accPath)]	
	|Dir (dn, sfs)->
			foldLeft (fun acc s -> 
				listAppend acc (traverser (listAppend [dn] accPath) s)
			)	[] sfs		
;;


(* top level function to append the results of the traverser together *)
let rec allFiles fs =
	match fs with
	|Dir (dn, sfs) ->
		foldLeft (fun acc subtree ->
			listAppend acc (traverser [dn] subtree)
		)	[] sfs
	|File _ -> []
;;



(* Q2a *)
(* f1 : ('a -> 'b -> 'c ) -> 'b -> 'a -> 'c *)
let f1 (f: 'a -> 'b -> 'c) (x: 'b) (y: 'a) = 
    f y x;;

(* f2 : (('a -> 'b) -> 'a) -> ('a -> 'b) -> 'b *)
let f2 (ff: ('a -> 'b) -> 'c) (f: 'a -> 'b) = 
    f (ff f);;


(* b. (3 marks) *)
(* Provide your answer in this comment block
    f1)
        The function returns a value of type 'c,
        thus the natural implementation would start by calling a function returning a value of type 'c
        so I start by calling the function f that returns type 'c.

        Then I pass the arguments x and y, in order y x, into the f function call,
        because they are of the required type 'a and 'b that the function needs.

        This is a natural implementation as it uses every value.


    f2)
        The function returns a value of type 'b,
        thus the natural implementation would start by calling a function returning a value of type 'b
        so I start by calling the function f that returns type 'b.

        The function f requires a single value as an input, 
        thus I provide the function ff as an argument as it will return a single value,
        the function ff takes a function of type ('a -> 'b) as an arguement, 
        so it follows that I should give it f as an input.

 *)

(* Q3a *)
(* a tuple of 2 lists, representing th place of the pointer being inbetween the 2 lists *)
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


let rec foldLeft f acc lst =
    match lst with
    | [] -> acc
    | head :: tail -> foldLeft f (f acc head) tail
;;

 (* Q4a *)
let threatening (s1, s2) =
	(* list of moves a knight can do *)
	let knightMoves = [(1, 2); (2, 1); (2, -1); (1, -2); (-1, -2); (-2, -1); (-2, 1); (-1, 2)] in	
	
	(* assigns x,y for each point *)
	let (x1, y1) = s1 in
	let (x2, y2) = s2 in
	
	(* checks rook moves by checking for matching x or y *)
	let rookMoveCheck =
		if x1 = x2 || y1 = y2
		then true
		else false 
	in

	(* checks against all variations of knight moves *)
	let rec knightMoveCheck lst =
		match lst with
		|[] -> false
		|(mx,my) :: tl -> 
			if (x1 + mx, y1 + my) = s2
			then true
			else knightMoveCheck tl
	in

	(* returns true if either condition is met *)
	rookMoveCheck || knightMoveCheck knightMoves
;;


(* Q4b *)
let rec safeConfig lst =
	match lst with
	|[] -> true
	|hd1 :: tl -> 
		match tl with
		|[] -> true
		|hd2 :: _ -> 
			(* checks if the 1st and 2nd knooks are threatening *)
			if threatening (hd1, hd2)
			then false
		(* if not, then recursively traverse the list until either a pair is threatened,
			or if it is safe *)	
		else safeConfig tl
;;
