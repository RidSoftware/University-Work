(* LN *)


type 'a tree = Lf | Br of 'a * 'a tree * 'a tree;;








let tree1 = Br(1, Br(2, Br(4, Br(8 , Lf, Lf), Br(9 , Lf, Lf))
							
								Br(5, Br(10, Lf, Lf), Br(11, Lf, Lf))
							),
						Br(3, Br(6, Br(12, Lf, Lf), Br(13, Lf, Lf))
							
							 	Br(7, Br(14, Lf, Lf), Br(15, Lf, Lf))
							))
							
					
;;


(*
                1
              /   \
             /     \
            2       3
           / \     / \
          /  /     \  \
         4   5     6   7
		  / \ / \	/ \ / \    
		 /  / \  \ /  / \  \
		/  /  /  / \  \  \  \
	  8  9  10 11 12 13 14 15

*)








let t1 = Br (4, Br (6, Br (1, Lf, Lf),
					  		  Br (9, Lf, Lf))
				    Br (8, Br (3, Lf, Lf),
					        Br (200, Lf, Lf)));;

(*
                4
              /   \
             /     \
            6       8
           / \     / \
          1   9   3   200
*)

let t2 = Br (4, Br (6, Lf
					   Br (9, Lf, Lf))
				   (8, Br (3, Br (19, Lf, Lf)
							  Lf),
				   	   Br (200, Lf, Lf))));;

(*
              4
            /   \
           /     \
          6       8
           \     / \
            9   3   200
               /
              19
*)

let t3 = Br (0, Lf,
				Br (5, Lf,
					   Br (4, Br (8, Lf, Lf),
					   		  Lf));;


(*
          0
         / \
        _   5
           / \
          _   4
             / \
            8   _
*)

let rec size t =
	match t with
	| Lf -> 0
	| Br (_, t1, t2) -> 1 + size t1 + size t2;;

let max x y =
	if x >= y
	then x
	else y;;

let rec depth t =
	match t with
	| Lf -> 0
	| Br (_, t1, t2) -> 1 + max (depth t1) (depth t2);;
		



(* Q1 *)

let rec sumT t =
	match t with
	| Lf -> 0
	| Br(v, t1, t2) -> v + sumT t1 + sumT t2;; 


(* Q2 *)

let rec mirror t =
	match t with
	| Lf -> Lf
	| Br(v, t1, t2) -> Br(v, mirror t2, mirror t1);;

(* Q3 *)

let rec member x t =
	match t with
	| Lf -> false
	| Br(v, t1, t2)-> 
		if v = x
		then true
		else member x t1 || member x t2;;


(* Q4 *)

let rec mapT f t =
	match t with
	| Lf -> Lf
	| Br(v, t1, t2) -> Br(f v, mapT f t1, mapT f t2);; 


(* Q5 *)

let rec dft t = match t with
    | Lf -> []
    | Br(v, t1, t2) -> v :: append (dft t1) (dft t2);;

let rec dftAux t acc =
	match t with
	(*?tf do i integrate acc?*)
	| Lf -> acc

	(* iterate from one end then come out and recurse through the other? *)
	
	| Br(v, t1, t2) -> v :: dftAux t1 [] :: dftAux t2 [];;



let dftFast t =
	dftAux t [];;


































