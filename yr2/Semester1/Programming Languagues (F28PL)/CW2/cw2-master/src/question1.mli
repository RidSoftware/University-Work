(* This is an *interface* file, which specifies the types of top-level
   functions exported from its analogue for usage and testing: do not touch! *)

type ftree = Dir of string * ftree list
           | File of string

type path = string list

val fs : ftree
val fs2 : ftree
val fs3 : ftree

val numFiles : string -> ftree -> int

val numDirs : ftree -> int

val validpath : path -> ftree -> bool

val nodupes : 'a list -> bool

val validFTree : ftree -> bool

val allFiles : ftree -> path list
