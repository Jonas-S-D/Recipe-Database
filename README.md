# Recipe-Database

### Sådan køre du programmet
For at køre programmet skal du køre filen [app.c](src/app.c)

### Kompiler
Nyeste version af GCC (Gnu Compiler Collection)

### Brugs instruktioner
Efter du har startet programmet vil du blive mødt af en introduktion
til programmet og muligheden for at vælge næste skridt ved at indtaste 'i'
for at gå til indtastning af ingredienser, 'k' for indtastning af kategorier af
opskrifter du er interesseret i, 's' for at søge efter specifikke opskrifter, 'f' når du er færdig med at indtaste ingredienser og kategorier,
og 'q' for helt at afslutte programmet. Vælges 'i' vil du blive mødt af
en prompt for at indtaste ingredienser og indtaste 'f' når du er færdig.
Når en ingrediens er indtastet vil du blive spurgt efter hvor meget du har og
hvilken enhed du har den i. Tilladte enheder er 'g' 'stk' 'dl' 'ml' 'l' 'kg'.
Vælges 'k' ude på hovedmenuen vil du blive mødt af en prompt der fortæller dig
at du kan indtaste 'i' for en liste of tilgængelige kategorier og skal indtaste 'f'
når du er færdig. Kun tilladte kategorier godtages af programmet.
Indtastes 's' på hoved menuen, vil du få en prompt der forklare dig at du kan indtaste 'l'
for at se en liste over alle opskrifter i programmet, og 'f' for at afslutte søgefunktionen
indtastes et navn på en opskrift vil du enten få printet opskriften ud hvis den er i
program biblioteket eller få at vide at opskriften ikke er i biblioteket og få at vide at
du skal indtaste 'j' for at søge igen eller 'f' for at vende tilbage til hovedmenuen.
Indtaster du 'f' i hovedmenuen og har indtastet minimum 1 ingrediens vil programmet
give dig de 3 opskrifter der har mindst en af de kategorier du indtastede, hvis nogen, og
mangler færrest ingredienser med hensyn til hvilke ingredienser der er tastet ind.
Vælg opskrift ved at taste 1-3 ind og programmet vil så give dig opskriften og fortælle
dig hvilke ingredienser du mangler og hvor de kan købes billigst.

