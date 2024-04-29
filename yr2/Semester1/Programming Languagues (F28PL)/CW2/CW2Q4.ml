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
