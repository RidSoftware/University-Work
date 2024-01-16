(* This is an *interface* file, which specifies the types of top-level
   functions exported from its analogue for usage and testing: do not touch! *)

val f1 : ('a -> 'b -> 'c ) -> 'b -> 'a -> 'c

val f2 : (('a -> 'b) -> 'a) -> ('a -> 'b) -> 'b
