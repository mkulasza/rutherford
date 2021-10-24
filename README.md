# rutherford
C++ symbolic expressions for modeling and implicit numerical integration

I have just started developing this as a standalone project. Progress will be slow as I finish my writing my thesis.

Variable step implicit integration is one of the most important tools for the future of power system simulation. The main drawback? It requires a Jacobian. And you can't estimate it - the systems are incredibly sparse. Less than 0.15 percent fill for smaller models. And what does a directly calculated Jacobian require?

Math, and a lot of it. Sure you could use a symbolic package to generate the equations for you. But then you have to write the code for them. Then debug that code because it's almost impossible to get the entries right on the first try for complicated models like machines and HVdc systems. And what if your model depends on external signals and resources? There just isn't enough time for this type of work when you also need to add your model to a client's base case, test and validate it, then deliver your client's model and documentation.

All of these complications are the reasons why fixed-step explicit integration remains the method of choice.

But what if we could make writing code for models easy while also using advanced integration methods? What if the equations developed on paper for your models just appeared directly in your code?

Symbolic math can do that for us.
