# r, d, p, q + "unif" (de la uniform) -> runif, dunif, punif, qunif
# d = densitatea
# p = functia de repartitie
# r = genereaza observatii independente din repartitia data
# q = functia cuantila

# x repartizat uniform pe [1,9]

# probab ca x sa apartina multimii {1,3,5,7,9}
0

# prob x apartine [3,5]
punif(5, 1, 9) - punif(3, 1, 9)

# prob ca x<3 si prob x<=3
punif(3, 1, 9)

# prob x apartine [1,3] *reunit* [4,7]
punif(3,1,9) + punif(7, 1, 9) - punif(4, 1, 9)
5/8

# ex: generati n obs indep. 
# trasati histograma(de densitate) acestor obs pe intervalul 1, 6, bare gri.
# suprapuneti pe acest grafic densitatea teoretica cu rosu punctat, grosime 2
n=150
hist(runif(n, 2, 5), 
     freq = FALSE,
     xlim = c(1, 6),
     col = "grey",
     xlab = "X",
     ylab = "Densitate"
      )
z = seq(1, 6, length.out=100)
lines(z,
      dunif(z, 2, 5),
      col= "red",
      lty = 2,
      lwd = 2
        )

x = runif(150, 2, 7)

# returnam cuartilele pentru x
quantile(x, probs = c(0.25, 0.5, 0.75))

# pentru mediana separat:
median(x)

#min si max: 
min(x) 
max(x)

#functii pentru observatii:
mean(x) # media aritmetica a observatiilor (x1+x2+...+xn) / n
var(x) # varianta 
sd(x) # abaterea standard
range(x) # intervalul de valori

#q + *nume* -> calculeaza fct cuantila corespunazoare ditributiei *nume*

# BOXPLOT:
# reprezentare grafica a distributiei unui set de date
mtcars
boxplot(mtcars$wt, horizontal = TRUE)
q1 = quantile(mtcars$wt, 0.25)
q2 = quantile(mtcars$wt, 0.5)
q3 = quantile(mtcars$wt, 0.75)

#formula: y(var numerica) ~ grup(var discreta)
boxplot(mtcars$hp ~ mtcars$cyl)

cars = mtcars$hp[mtcars$cyl == 6]
q1 = quantile(cars, 0.25)
q2 = quantile(cars, 0.5)
q3 = quantile(cars, 0.75)
md = q3 + 1.5*(q3 - q1)
max(cars[cars <= 142])

cars = mtcars[mtcars$cyl == 8,]
q1 = quantile(cars$wt, 0.25)
q2 = quantile(cars$wt, 0.5)
q3 = quantile(cars$wt, 0.75)
md = q3 + 1.5*(q3 - q1)
rownames(cars)[cars$wt>md]
