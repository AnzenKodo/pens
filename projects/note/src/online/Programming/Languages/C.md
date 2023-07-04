# C

- In fact, you should use the main() to do very little except call each of the other functions.
- A good rule of thumb is that a function should not take more lines than will fit on a single screen. If the function is longer than that, you’re probably making it do too much.
- The difference between local and global variables:
    - A variable is global only if you define the variable (such as inti;) before a function name.
    - A variable is local only if you define it after an opening brace. A function always begins with opening braces. Some statements, such as while, also have opening braces, and you can define local variables within those braces as well.
- Local variables are safer than global variables.
- Don’t define global variables in the middle of a program. They’re too hard to locate if you do.
