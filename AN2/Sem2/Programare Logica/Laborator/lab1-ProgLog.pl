name(tywin_lannister).
name(cersei_baratheon).
name(janos_slynt).
name(tyrion_lannister).
name(grand_maester_pycelle).
name(varys).
name(petyr_baelish).

/* x la dreapta lui y */
right(tyrion_lannister,janos_slynt).
right(janos_slynt,cersei_baratheon).
right(cersei_baratheon,tywin_lannister).
right(tywin_lannister,petyr_baelish).
right(petyr_baelish,varys).
right(varys,grand_maester_pycelle).
right(grand_maester_pycelle,tyrion_lannister).

sits_right_od(X, Y) :- X\==Y, right(X, Y).
sits_left_of(X, Y) :- X\==Y, sits_right_of(Y, X).
are_neighbors_of(X, Y, Z) :- X\==Y, X\==Z, Y\==Z, sits_right_of(Y, Z), sits_left_of(X,Z).
next_to_each_other(X, Y) :- X\==Y, (sits_right_of(Y, X);sits_left_of(X, Y)).
places(X, Y, Z) :- sits_left_of(X, Y), sits_left_of(Y, Z), write(Z).