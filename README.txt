Huffman coding

I've started by first reading in a file. The file's characters are then counted and added to a linked list.
The linked list holds the frequency that the characters appear in, if it is not in the list then it is addded.
This allows any valid character to be coded.

The frequency list is then converted into huffman nodes and also insertion sorted.

Unfortunatly, this task proved to be much harder than I anticipated so I couldn't finish it off.
After the sorting I plan to use a iterative formular to peg the smallest node on to the tree.
The node will then be added back to the huffman nodes list with it's leaf's removed.
This will then be sorted again.

By doing this it will leave the the huffman nodes list with only nodes that can be put upon another.
This will be done until there is only one node left, the start node.

No pointers will be lost as the huffman nodes will hold the pointers to the branches.

The program currently is leaky. I cannot find the fix.

The use of my linked list module proved to be quite difficult as conflicting names for the nodes and
items had me refactoring a lot of code by hand. The lists proved to work quite well, but I'm
starting to doubt the usefulness of implementing it in such a way.

But over all I think I've practiced my use of pointers and structures greatly.
The tests I've created are too extensive in my opinion, more of my timse should have been put on
planning and programming.
