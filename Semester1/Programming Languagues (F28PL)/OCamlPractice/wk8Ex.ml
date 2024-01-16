(* Arithmetic expressions *)

type var = string;;

type aexp =
	 Var of var
	|Num of int
	|Neg of aexp
	|Sum of aexp * aexp
	|Prod of aexp * aexp;;

let max x y =
	if x>y
	then x
	else y;;

(* 1 *)

let rec numLits aexp =
	match aexp with
	|Var _ -> 0
	|Num _ -> 1
	|Neg n -> numLits n
	|Sum (e1, e2) -> numLits e1 + numLits e2 
	|Prod (e1, e2) -> numLits e1 + numLits e2;;


 
let rec mulDepth aexp =
	match aexp with
	|Var _ -> 0
	|Num _ -> 1
	|Neg e -> mulDepth e
	|Sum (e1, e2) -> max (mulDepth e1) (mulDepth e2)
	|Prod (e1, e2) -> max (mulDepth e1) (mulDepth e2);;

(* 2 *)

let parens s = "("^ s ^")";;

let rec printAExp aexp =
	match aexp with
	|Var v -> v
	|Num n -> Int.to_string n
	|Neg e -> parens (" - " ^ printAExp e)
	|Sum (e1, e2) -> parens (printAExp e1 ^ " + " ^ printAExp e2)
	|Prod (e1, e2) -> parens (printAExp e1 ^ " * " ^ printAExp e2);;



(* 3 *)

type env = (var * int) list


let rec lookup env x =
	match env with
	|[] -> failwith "Not Found"
	|(v, i)::tl -> 
		if v = x
		then i
		else lookup tl x;;


let rec eval env ae =
	match ae with
	|Var v -> lookup env v
	|Num n -> n
	|Neg e -> - (eval env e)
	|Sum (e1, e2) -> (eval env e1) + (eval env e2)
	|Prod (e1, e2) -> (eval env e1) * (eval env e2);;
	

(* Parsing and printing fully-parenthisised exrpression *)


type sexp =
	 Id of string
	|Num of int
	|Comb of sexp list;;
(*
Comb [Id "div"; Id "Title";
		Comb [Id "par"; Id "Part"; Id "of"; Id "content"];
		Comb [Id "par"; Id "Some"; Id "more"; Id "content"]]
*)

(* 1 *)


let rec append xs ys =
	match ys with
	| [] -> []
	| x :: xs -> append xs (x :: ys);;






let rec printSExp sexp =
	let rec concat acc exp =
	acc ^ " " ^ printSExp exp in
  match sexp with
  | Id(s) -> s
  | Num(n) -> Int.to_string n
  | Comb(lst) -> 
  		parens (fold_left concat "" lst);;






































