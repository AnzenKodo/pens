Laplace transform is used because it converts or reduces a differential equation into an algebraic equation.

The formula of Laplace:
$$\mathscr{L}\{f(t)\} = \int_0^\infty e^{-st} f(t) dt = f(s)$$


The $\mathscr{L}\{f(t)\}$ is function which is converted into $F(s)$
$$\mathscr{L}\{f(t)\} \to F(s)$$

Intergal explain
- Lets say $A \to \infty$ ($A$ is infinty).
- So that is same as $\int_a^\infty$

## Example

$$\mathscr{L}\{f(t)\} = \int_0^\infty e^{-st} f(t) dt$$

Now we have taken $1$ as $f(t)$ (function of $t$)
$$\mathscr{L}\{1\} = \int_0^\infty e^{-st} 1 dt$$

$$= \Big({e^{-st} \over -s}\Big)^\infty_0$$

$$= {e^{-\infty} - e^{-0} \over -s}$$

The $e$ power - infinty is 0 ($e^{-\infty} = 0$)

$$= {0 - e^{-0} \over -s}$$
$$= {1  \over s}$$

## Reference

- [Laplace transform 1](https://www.khanacademy.org/math/differential-equations/laplace-transform/laplace-transform-tutorial/v/laplace-transform-1)
- [Formula of Laplace Transform and Inverse Laplace Transform | By Gp Sir](https://www.youtube.com/watch?v=EDVJotmT584)
- [Introduction to Laplace transform Full Basic Concept in Hindi | Maths 3 Lectures](https://www.youtube.com/watch?v=n-Yxa9QkVZI)
