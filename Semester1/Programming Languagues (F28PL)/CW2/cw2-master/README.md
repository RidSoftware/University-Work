# Coursework 2 

This is the repository with the stubs of the implementation for
Coursework 2 in F28PL. In order to submit the coursework, you will
need to *fork* this repository, creating your own, private version on
GitLab, clone your fork onto your local machine, create your solution
within your repository and push the solutions to your own fork of the
project. The instructions below follow the ones for Coursework 1.

## Getting started

The first steps to get you to the point of being able to create your
own solution are as follows:

1. Fork the project. To do this, find the "Fork" button in the
   top-right of the project's web-page, click it, and follow the
   instructions. Remember to set your fork as private (the markers
   should be added to your project automatically, so you do not need
   to worry about their access).

2. Clone your fork to create an image of the repository on your local
   machine, attached to your fork. To do this, you will need a working
   `git` installation. (Note: if you're developing the coursework
   under WSL, your working `git` installation should also be on
   WSL. You should be able to get `git` working on your Linux
   subsystem using something like `sudo apt-get install git`.)

3. Develop your coursework. At this point, you can start developing
   your coursework. To avoid data loss, it is wise to periodically
   *commit* your changes to your local repository, and *push* them to
   your fork. (This will also allow you to work across multiple
   machines if, for instance, you have both a laptop and desktop
   computers.)

4. Remember to push your the solution of the coursework problems to
   your fork of the project *before the deadline*!

## Developing your project

Once you clone the repository, you may notice that there are quite a
few files. Some of them are provided to make the development and
testing process more streamlined, and you shouldn't need to worry
about them too much. The most important part, the solution files, live
in the `src` subdirectory of the project, and that is where you should
keep them. The source files are called `question1.ml`, `question2.ml`,
`question3.ml`, `question4.py`, and `question5.py` respectively, and
provide templates for the solution of each question. The files are
self-contained, so you should be able to work on the solutions using
an editor and an evaluator, as usual. Make sure to provide both the
implementation and explanations that detail how your code should work,
and why you designed it the way you did, as well as answers to
questions that do not require coding.

The `.mli` files present in the `src` subdirectory are there to ensure
that the types of your definitions match the specification when you
compile the project. You should not modify these under any
circumstances.

The project is equipped with automated compilation and testing
features. You don't need to worry about these too much; if you want to
use them, running `dune build` in the top-level directory of the
project will compile the project, and `dune runtest` (you can use
`dune runtest -f` to force a new seed) will run the tests (after you
compile successfully). Running `dune build` on the freshly forked
version of the project, you should see a whole bunch of warnings:
these signal that parameters of the functions that you are to define
are not used --- and thus should start to go away as you implement
your solutions.

The tests make use of `qcheck`; at first, you will see that all the
tests error out: this is because the solutions are not yet
implemented. As you develop your solutions, you should see more and
more tests passing. Note that passing the tests is not a guarantee of
full marks, since we will be reading and assessing your code (and the
tests do not necessarily enforce full correctness, either). You should
*not* modify any files in the `test` subdirectory of the project.
Pushing the project to your fork will automatically compile it and run
the tests, and will let the markers know what the result of the tests
is.
