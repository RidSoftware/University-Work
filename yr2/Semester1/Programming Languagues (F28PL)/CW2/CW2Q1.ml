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


let rec numFiles targetFilename fs =
	match fs with
	|File fn -> 
		if fn = targetFilename
		then 1 else 0
	|Dir (fn, sfs) ->
		foldLeft (fun f -> acc + numFiles filename f) 0 sfs
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
