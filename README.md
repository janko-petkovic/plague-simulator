# Plague
Modern plague simulator.
Sort of.

So basically for now we have:

Headers:
- Plague.h : infection model class. The class should contain the two core methods Flux and Simulate that should compute the ideal, continuous probability developement the disease and the actual Monte Carlo simulation. For now it contains
    - class PlagueModel
    - struct statusChange

Implementation:
- Plague.cpp : implementation of Plague.h
- utils.cpp : utility methods that are not substantial part of a Plague class

Mains:
- main.cpp
- check.cpp : random cpp that I use to check the single methods. Could revrite it every time but its sort of easier to have it here.
