Formula: $\mathscr{L}\{f(t)\} = \int_0^\infty e^{-st} f(t) dt = f(s)$

## Find the Laplace transform of $f(t)$, where: 
$$f(t) = 3, 0<t<5$$
$$f(t) = 0, t>5$$

$t>5$ value is $f(t) = 0$ that why here $(0)dt$ given.
$$\mathscr{L}\{3\} = \int_0^5 e^{-st} (3)dt +\int_5^\infty e^{-st}(0)dt$$

Because $(0) \over \int_5^\infty$ is $0$

$3$ is [Constant](../Definition#definition-of-constant) that way $3$ comes outside.

$$= 3 \int_0^5e^{-st}dt$$

$$= 3\left[e^{-st}\over -S\right]^5_0$$

$$F(s) = \frac{3(e^{-5s} - 1)}{s}$$
