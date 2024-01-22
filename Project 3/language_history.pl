% Facts
created(fortran1, 1956).  
created(lisp, 1958).
created(cobol, 1959).
created(algol60, 1960).
created(pl1, 1964).
created(pascal, 1970).
created(ml, 1973).
created(smalltalk, 1976).
created(ada, 1983).       
created(cpp, 1985).       
created(scheme, 1985).
created(tcl, 1988).
created(swift, 2014).
created(rust, 2010).
created(commonlisp, 1984).
created(fortran77, 1977).
created(smalltalk80, 1980).
created(c_kr, 1978).      
created(ada83, 1983).
created(perl, 1987).
created(eiffel, 1985).
created(perl5, 1994).
created(python, 1990).
created(ruby, 1995).
created(fortran90, 1991).
created(python2, 2000).
created(haskell98, 1998).
created(csharp, 2000).
created(java, 1995).
created(javascript, 1995).
created(cpp_iso, 1998).   
created(java5, 2004).
created(csharp2, 2005).
created(csharp5, 2012).
created(java8, 2014).
created(javascript_es2017, 2017).
created(go, 2007).
created(camll, 1985).     
created(sml, 1983).
created(scheme_r5rs, 1998).
created(haskell2010, 2010).
created(ocaml, 1996).

% Parent-Child Relationships
parent(fortran1, algol60).
parent(fortran1, pl/1).
parent(fortran1, fortran77).
parent(algol60, tcl).
parent(algol60, cpp).
parent(algol60, c_kr).
parent(algol60, smalltalk).
parent(algol60, perl).
parent(algol60, scheme).
parent(algol60, pl/1).
parent(cobol, pl/1).
parent(lisp, scheme).
parent(lisp, commonlisp).
parent(pl/1, pascal).
parent(fortran77, fortran90).
parent(cpp, java).
parent(cpp, cpp_iso).
parent(cpp, rust).
parent(cpp, python).
parent(c_kr, cpp).
parent(c_kr, python).
parent(smalltalk, smalltalk80).
parent(perl, ruby).
parent(perl, perl5).
parent(scheme, scheme_r5rs).
parent(scheme, commonlisp).
parent(pascal, python).
parent(pascal, ada83).
parent(java, java5).
parent(java, csharp).
parent(java, javascript).
parent(cpp_iso, csharp).
parent(rust, swift).
parent(python, python2).
parent(python, ruby).
parent(smalltalk80, go).
parent(smalltalk80, ruby).
parent(ada83, eiffel).
parent(eiffel, ruby).
parent(java5, java8).
parent(java5, kotlin).
parent(csharp, csharp2).
parent(javascript, kotlin).
parent(javascript, javascript_es2017).
parent(python2, swift).
parent(python2, go).
parent(ruby, swift).
parent(scheme_r5rs, rust).
parent(csharp2, kotlin).
parent(csharp2, csharp5).
parent(csharp2, rust).
parent(csharp5, javascript_es2017).
parent(ml, haskell98).
parent(ml, sml).
parent(haskell98, rust).
parent(haskell98, haskell2010).
parent(haskell2010, swift).
parent(sml, caml).
parent(caml, ocaml).
parent(ocaml, rust).

% Ancestor: A is an ancestor of D if a path can be followed from A to D.
ancestor(A, D) :- 
    parent(A, D).
ancestor(A, D) :- 
    parent(A, X), 
    ancestor(X, D).

% Descendant: D is a descendant of A if A is an ancestor of D.
descendant(D, A) :- 
    ancestor(A, D).

% Sibling: X and Y are siblings if they have the same parent.
sibling(X, Y) :- 
    parent(P, X), 
    parent(P, Y), 
    X \= Y.

% Cousin: X and Y are cousins if they both share the same ancestor.
cousin(X, Y) :- 
    ancestor(A, X), 
    ancestor(A, Y), 
    X \= Y.

% I used set here to avoid duplications
cousins_of_cpp(Set) :- 
    setof(Y, cousin(cpp, Y), Set).
