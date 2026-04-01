### March 19, 2026
Did basic setup of my ArrayStack.h and declared methods and functions.

### March 30, 2026
Completed empty() and push() and tested both to make sure they work properly. I then moved onto pop() and ran into and error when calling it while there is nothing in the stack. The program would not terminate, so I added a if statement to check if the stack is empty, before removing anything. If the stack is empty, it will then throw an out of range exception. 

### March 30, 2026
Completed and tested all of ArrayStack.h so it all works as expected.

### March 31, 2026
Finished tokenize() in main.ppp, however in doing so ran into an error. Once I thought I was done, I tested it to see if it worked, and for the most part it did. It wasn't until I ran an expression where the operator was directly next to the number where it failed. For example, running "3 + 4" would work as intended, however "3+ 4" or "3+4" would only give the numbers, and no operator. I realized this was because in the function, there is a while loop in which it checks if the number has multiple numbers, such as "35" instead of just "3". In this while loop, it increments "i" to go to the next value and check if it is a number. After the loop, though, it never decrements "i", causing it to skip over the next value and not work as expected. To fix this problem, I simply added a decrement "i--" after the while loop, to allow it to work as intended.

### March 31, 2026
Completed precedence(), isValidPostfix(), and isValidInfix() and ran many test cases to make sure they all work properly. With some slight syntax errors and mini fixes, it all worked as intended.

### March 31, 2026
Completed infixToPostfix() as well as evalPostfix(), however ran into some errors while testing. The first thing I noticed is that when I put in "3*2+6" I got 11 instead of 12, as it added it all up. I fixed this, as in my infixToPostfix() function, I was pushing the current token of "s" instead of the top of the operators stack. This caused a mix-up and caused it to use the other operator twice. The second problem I ran into while testing is whenever I would divide something by 0, the answer became "inf" instead of "0". This is because I forgot to add a check in the evalPostfix() function for this. The final problem was involving parentheses, inn which each time I used them, it tried to use one as an operator, like "+, -, *, /", which is not possible. To fix this, I had to change a few things in infixToPostfix(). I had to add a check in the while loop for isOperator(s) to make sure it doesn't pop past the parentheses. I then had to change the while loop for the parentheses to instead of using "== "("" , I had to do "!= "("" .
