
Triangle
By starting at the top of the triangle and moving to adjacent numbers on the row below, the maximum total from top to 
bottom is 27.

        5
      9   6
    4   6   8
  0   7   1   5

I.e. 5 + 9 + 6 + 7 = 27.

Write a program in a language of your choice to find the maximum total from top to bottom in triangle.txt, a text file 
containing a triangle with 100 rows. 
Send your solution and resume to [123456 AT yodle dot com], replacing 123456 with the maximum sum for the triangle. 


/* UPDATE 02/26/204
   After looking at this problem more carefully, I realized I need to traverse all possible paths in order to get the
   maximum total. I made some assumptions about the initial problem that didn't tell the whole story.
   If in the tree example above we change 8 -> 81, the current algorithm will not visit that node and not give us the 
   max value we are looking for:

        5
      9   6
    4   6   81
  0   7   1   5

I.e. 5 + 9 + 81 + 5 = 100

*/

// TriangleTree.cpp : Defines the entry point for the console application.
