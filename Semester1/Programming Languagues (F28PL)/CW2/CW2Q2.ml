(** CW2, QUESTION 2 **)

(* a. (2 marks) *)
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
