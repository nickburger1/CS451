%1
isMember(_, []) :- fail.
isMember(X, [X|_]).
isMember(X, [_|Tail]) :- isMember(X, Tail).

%2
addElem(X, List, [X|List]).
addElem(X, [Head|Tail], [Head|NewTail]) :- addElem(X, Tail, NewTail).

%3
delElem(X, [X|Xs], Xs).
delElem(X, [Y|Ys], [Y|Zs]) :- dif(X, Y), delElem(X, Ys, Zs).
delElem([], L, L).
delElem([X|Xs], L, Zs) :- delElem(X, L, Ys), delElem(Xs, Ys, Zs).

%4
prodList([], 1).
prodList([X], X).
prodList([X|Xs], P) :- prodList(Xs, P1), P is X * P1.

%5
prodScalar([], [], 0).
prodScalar([X|Xs], [Y|Ys], P) :- prodScalar(Xs, Ys, Q), P is X*Y + Q.

%6
prodVector([], [], []).
prodVector([X|Xs], [Y|Ys], [Z|Zs]) :- Z is X * Y, prodVector(Xs, Ys, Zs).

%7
unionList([], L, L).
unionList([X|L1], L2, [X|L3]) :- \+ isMember(X, L2), unionList(L1, L2, L3).
unionList([X|L1], L2, L3) :- isMember(X, L2), unionList(L1, L2, L3).

%8
getDices(Sum, N, Res) :- length(Res, N), fillDices(Sum, Res).

fillDices(0, []).
fillDices(Sum, [X|Xs]) :-
    between(1, 6, X),
    Sum1 is Sum - X,
    fillDices(Sum1, Xs).

%9
maxList([X], X).
maxList([X, Y | Tail], Max) :- X >= Y, maxList([X | Tail], Max).
maxList([X, Y | Tail], Max) :- X < Y, maxList([Y | Tail], Max).

%10
sumList([], 0).
sumList([X|Xs], Sum) :- sumList(Xs, Rest), Sum is X + Rest.

sumOfOthers(List) :- select(X, List, Rest), sumList(Rest, Sum), X =:= Sum.
sumOfOthers([]) :- false.

%11
sumBefore(List) :-
    sumBefore(List, 0).

sumBefore([Head|_], Sum) :-
    Head = Sum.

sumBefore([Head|Tail], Sum) :-
    NewSum is Sum + Head,
    sumBefore(Tail, NewSum).
