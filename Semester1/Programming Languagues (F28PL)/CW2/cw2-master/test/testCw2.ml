open QCheck

(* utility functions *)
(*
let rec member y xs =
  match xs with
  | [] -> false
  | x :: xs -> y = x || member y xs

let sum xs =
  let rec aux n xs =
    match xs with
    | [] -> n
    | x :: xs -> aux (n + x) xs
  in aux 0 xs

let rec map f xs =
  match xs with
  | [] -> []
  | x :: xs -> f x :: map f xs

let rec insAll y xs =
  (y :: xs) ::
    match xs with
    | [] -> []
    | x :: xs -> map (fun ys -> x :: ys) (insAll y xs)

let rec islb m xs =
  match xs with
  | [] -> true
  | x :: xs -> m <= x && islb m xs

let rec isSorted xs =
  match xs with
  | [] -> true
  | x :: xs -> islb x xs && isSorted xs
 *)

(* Question 1 *)
let _ = print_string ("================================================================================\n"
                    ^ "=== Testing Question 1 =========================================================\n")

module Q1 = Cw2.Question1

let q1ae1 = 
    Test.make 
    ~name:"Q1a example 1"
    ~count:1 unit (fun _ -> Q1.numFiles "notes" Q1.fs = 2)

let q1ae2 = 
    Test.make 
    ~name:"Q1a example 2"
    ~count:1 unit (fun _ -> Q1.numFiles "doc1" Q1.fs = 1)

let q1ae3 = 
    Test.make 
    ~name:"Q1a example 3"
    ~count:1 unit (fun _ -> Q1.numFiles "desktop" Q1.fs = 0)

let q1ae4 = 
    Test.make 
    ~name:"Q1a example 4"
    ~count:1 unit (fun _ -> Q1.numDirs Q1.fs = 4)

let p1 = ["root"]
let p2 = ["root"; "desktop"]
let p3 = ["root"; "desktop"; "trash"]
let p4 = ["root"; "documents"; "doc1"]
let p5 = ["gibberish"]

let q1be1 = 
    Test.make 
    ~name:"Q1b example 1: [root] is a valid path in fs"
    ~count:1 unit (fun _ -> Q1.validpath p1 Q1.fs = true)

let q1be2 = 
    Test.make 
    ~name:"Q1b example 2: [root;desktop] is a valid path in fs"
    ~count:1 unit (fun _ -> Q1.validpath p2 Q1.fs = true)

let q1be3 = 
    Test.make 
    ~name:"Q1b example 3: [root;desktop;trash] is not a valid path in fs"
    ~count:1 unit (fun _ -> Q1.validpath p3 Q1.fs = false)

let q1be4 = 
    Test.make 
    ~name:"Q1b example 4: [root;documents;doc1] is not a valid path in fs"
    ~count:1 unit (fun _ -> Q1.validpath p4 Q1.fs = false)

let q1be5 = 
    Test.make 
    ~name:"Q1b example 5: [gibberish] is not a valid path in fs"
    ~count:1 unit (fun _ -> Q1.validpath p5 Q1.fs = false)

let q1be6 = 
    Test.make 
    ~name:"Q1b example 6: the empty path is not a valid path in fs"
    ~count:1 unit (fun _ -> Q1.validpath [] Q1.fs = false)

let q1ce1 = 
    Test.make 
    ~name:"Q1c example 1: fs is a valid ftree"
    ~count:1 unit (fun _ -> Q1.validFTree Q1.fs = true)

let q1ce2 = 
    Test.make 
    ~name:"Q1c example 2: fs2 is not a valid ftree"
    ~count:1 unit (fun _ -> Q1.validFTree Q1.fs2 = false)

let q1ce3 = 
    Test.make 
    ~name:"Q1c example 3: fs3 is not a valid ftree"
    ~count:1 unit (fun _ -> Q1.validFTree Q1.fs3 = false)

let q1de1 = 
    let files = [ [ "root" ; "desktop" ; "doc1" ]
                ; [ "root" ; "desktop" ; "notes" ]
                ; [ "root" ; "documents" ; "notes" ]
                ; [ "root" ; "documents" ; "text1" ]
                ; [ "root" ; "file1" ]
                ; [ "root" ; "file2" ]
                ]
    in Test.make 
       ~name:"Q1d example 1: listing all files in fs"
       ~count:1 unit (fun _ -> List.sort compare (Q1.allFiles Q1.fs) = files)

let q1de2 = 
    let fs' = Q1.Dir ("root", []) 
    in Test.make 
       ~name:"Q1d example 2: listing all files in an empty filesystem"
       ~count:1 unit (fun _ -> Q1.allFiles fs' = [])

let q1de3 = 
    let fs' = Q1.Dir ("root", [ Q1.Dir ("empty1", [])
                              ; Q1.Dir ("desktop", [ Q1.Dir ("empty2", [])
                                                   ; Q1.Dir ("empty3", [])
                                             ])
                           ]) 
    in Test.make 
       ~name:"Q1d example 3: listing all files in a filesystem of only directories"
       ~count:1 unit (fun _ -> Q1.allFiles fs' = [])

let rec removeAdj xs = match xs with
  | [] -> []
  | [x] -> [x]
  | x::y::xs -> if x = y then removeAdj (y::xs) else x::(removeAdj (y::xs))

let nodupesSpec xs = if Q1.nodupes xs
                     then let l = List.sort compare xs
                          in  l = removeAdj l
                     else true

let testDupes = Test.make ~name:"nodupes: sorting a list with no dupes = sorting then removing adjacent equal elements"
                  (list int) nodupesSpec



let n1 = QCheck_runner.run_tests ~out:stdout
           [ q1ae1 ; q1ae2 ; q1ae3 ; q1ae4 
           ; q1be1 ; q1be2 ; q1be3 ; q1be4 ; q1be5 ; q1be6 
           ; q1ce1 ; q1ce2 ; q1ce3 
           ; q1de1 ; q1de2 ; q1de3 
           ; testDupes
           ]

(* Question 2 -- not tested, based purely on types *)

(* Question 3*)

let _ = print_string ("================================================================================\n"
                    ^ "=== Testing Question 3 =========================================================\n")

module Q3 = Cw2.Question3

let q3e1 = 
    Test.make 
    ~name:"Q3 example 1"
    ~count:1 unit (fun _ -> Q3.getPlace [] 0 |> Q3.insert 1 |> Q3.insert 2 |> Q3.collapse = [1;2])

let q3e2 = 
    Test.make 
    ~name:"Q3 example 2"
    ~count:1 unit (fun _ -> Q3.getPlace [1;2;2;3] 2 |> Q3.delete |> Q3.collapse = [1;2;3])

let q3e3 = 
    Test.make 
    ~name:"Q3 example 3"
    ~count:1 unit (fun _ -> Q3.getPlace [1;2;2;3] 2 |> Q3.delete |> Q3.lookup = 3)

let q3e4 = 
    Test.make 
    ~name:"Q3 example 4"
    ~count:1 unit (fun _ -> Q3.getPlace [1;2;2;3] 0 |> Q3.next |> Q3.delete |> Q3.next |> Q3.next |> Q3.isEnd)

let rec all p xs = match xs with
  | [] -> true
  | x::xs -> if p x then all p xs else false

let rec append xs ys = match xs with
  | [] -> ys
  | x::xs -> x :: (append xs ys)

let rec range n = if n = 0 then [0] else append (range (n-1)) [n]

let example5 xs = let l = List.length xs in
  let f n = Q3.getPlace xs n |> Q3.insert 57 |> Q3.prev |> Q3.lookup = 57 in
  all (fun x -> x) (List.map f (range l))

let q3e5 = 
    Test.make 
    ~name:"Q3 example 5"
    (small_list int) example5

let n3 = QCheck_runner.run_tests ~out:stdout
          [ q3e1 ; q3e2 ; q3e3 ; q3e4 ; q3e5 ]

(* error code is the number of failed/errored tests *)
let _ = print_int (n1 + n3); exit (n1 + n3)
