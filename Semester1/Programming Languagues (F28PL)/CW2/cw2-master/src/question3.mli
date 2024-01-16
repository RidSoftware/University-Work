(* This is an *interface* file, which specifies the types of top-level
   functions exported from its analogue for usage and testing: do not touch! *)

(* Note: do not touch, even after you figured out your representation:
   this declaration makes the implementation details invisible to
   parts of the program that *use* your library *)
type 'a place

val getPlace : 'a list -> int -> 'a place

val collapse : 'a place -> 'a list

val isStart : 'a place -> bool

val isEnd : 'a place -> bool

val next : 'a place -> 'a place

val prev : 'a place -> 'a place

val lookup : 'a place -> 'a

val delete : 'a place -> 'a place

val insert : 'a -> 'a place -> 'a place
