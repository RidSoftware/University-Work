public class huffmanHeap {

    private class huffmanHeapNode {

        private boolean leaf, head;
        private int priority;
        private huffmanHeapNode leftNode, rightNode;

        public huffmanHeapNode(boolean h, boolean l, int p, huffmanHeapNode rn, huffmanHeapNode ln) {

            head = h;
            leaf = l;
            priority = p;
            leftNode = ln;
            rightNode = rn;

        }        

        //only instance creation implemented


    }


    public huffmanHeap(int[] distinctIntegers){






        return huffmanHeapNode(true, true, 0, null, null);
    }






}



