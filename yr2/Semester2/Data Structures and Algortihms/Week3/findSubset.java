public class Main {
    //test sets
    int[] a = [1, 2, 3, 4];
    int[] b = [2, 4, 6];
    int[] c = [2, 3];

    //test targets
    int k1 = 5;
    int k2 = 47;

    Boolean findSubset(a, k1);
    
}


//takes a set(array) of ints -> S,
//takes target in -> k,
//finds subset(subarray) of S that sums to k -> returns Bool (true) 

//recursively implemented
public boolean findSubset(int[] S[], int k) {

    if (k == 0) {
        return true;
    }
    if (S[0] == null) {
        return false;
    }

    int s = S[0];

    if (s > k) {
        return findSubset(S, k);
    } else {
        return findSubset(S, (k-s));
    }


    return false;
}
