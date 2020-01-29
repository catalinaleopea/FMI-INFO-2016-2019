
import           Data.List     (sort)
 
type Linie = Integer
type Coloana = Integer


type Partida = [(Linie, Coloana)]
 
exemplu1 :: Partida
exemplu1 = [ (2, 2), (1, 3), (2, 3), (2, 4), (3, 5), (0, 2), (2, 1), (1, 4)
           , (2, 0), (1, 2), (3, 1), (1, 0)
           ]

test11 :: Bool
test11 = 
  separaX0 exemplu1
  ==  ( [(2,2),(2,3),(3,5),(2,1),(2,0),(3,1)]
      , [(1,3),(2,4),(0,2),(1,4),(1,2),(1,0)])
 
separaX0 :: [a] -> ([a], [a])
separaX0 [] = ([], [])
separaX0 (a:as) = (a:as2, as1)
  where (as1, as2) = separaX0 as

test12 :: Bool
test12 = 
  maxLista [[1,2,3], [4,5], [6], [7, 8, 9, 10], [11, 12, 13]]
  == [7, 8, 9, 10]
 
maxLista :: [[a]] -> [a]
maxLista l = l !! pozMax
  where
    lungimiPozitii = [(length x, px) | (x, px) <- l `zip` [0..]]
    (_, pozMax) = maximum lungimiPozitii

test130, test13X :: Bool
test130 =
  grupeazaUnite (sort [(1,3),(2,4),(0,2),(1,4),(1,2),(1,0)])
  == [[(0,2)],[(1,0)],[(1,2),(1,3),(1,4)],[(2,4)]]
test13X =
  grupeazaUnite (sort [(2,2),(2,3),(3,5),(2,1),(2,0),(3,1)])
  == [[(2,0),(2,1),(2,2),(2,3)],[(3,1)],[(3,5)]]

grupeazaUnite :: Partida -> [Partida]
grupeazaUnite =
  grupeazaDupa (\(l,c) (l',c') -> l == l' && c' == c+1 )

grupeazaDupa :: (a -> a -> Bool) -> [a] -> [[a]]
grupeazaDupa test = foldr go []
  where
    go a [] = [[a]]
    go a ((a':l):ls)
      | test a a' = (a:a':l):ls
      | otherwise = [a]:(a':l):ls

test14 :: Bool
test14 =
  maxInLinie exemplu1 == ([(2,0),(2,1),(2,2),(2,3)], [(1,2),(1,3),(1,4)])
 
maxInLinie :: Partida -> (Partida, Partida)
maxInLinie partida = (maxSecventa ics, maxSecventa zero)
  where
      (ics, zero) = separaX0 partida
      maxSecventa = maxLista . grupeazaUnite . sort

data Binar a = Gol | Nod (Binar a) a (Binar a)

exemplu2 :: Binar (Int, Float)
exemplu2 =
  Nod 
      (Nod (Nod Gol (2, 3.5) Gol) (4, 1.2) (Nod  Gol (5, 2.4) Gol)) 
      (7, 1.9)
      (Nod Gol (9, 0.0) Gol)

data Directie = Stanga | Dreapta
 
type Drum = [Directie]

test211, test212 :: Bool
test211 = plimbare [Stanga, Dreapta] exemplu2 == Just (5, 2.4)
test212 = plimbare [Dreapta, Stanga] exemplu2 == Nothing
 
plimbare :: Drum -> Binar a -> Maybe a
plimbare _ Gol                      = Nothing
plimbare [] (Nod _ x _)             = Just x
plimbare (Stanga:is) (Nod st _ _)   = plimbare is st
plimbare (Dreapta:is) (Nod _  _ dr) = plimbare is dr

type Cheie = Int
type Valoare = Float

newtype WriterString a = Writer { runWriter :: (a, String) }
 
instance Monad WriterString where
  return x = Writer (x, "")
  ma >>= k =  let (x, logx) = runWriter ma
                  (y, logy) = runWriter (k x)
              in  Writer (y, logx ++ logy)

tell :: String -> WriterString ()
tell s = Writer ((), s)
 
instance Functor WriterString where
  fmap f mx = do { x <- mx ; return (f x) }
 
instance Applicative WriterString where
  pure = return
  mf <*> ma = do { f <- mf ; a <- ma ; return (f a) }

test221, test222 :: Bool
test221 = runWriter (cauta 5 exemplu2) == (Just 2.4, "Stanga; Dreapta; ")
test222 = runWriter (cauta 8 exemplu2) == (Nothing, "Dreapta; Stanga; ")
 
cauta :: Cheie -> Binar (Cheie, Valoare) -> WriterString (Maybe Valoare)
cauta cheie Gol = return Nothing
cauta cheie (Nod st (cheie', valoare) dr)
    | cheie == cheie' = return (Just valoare)
    | cheie < cheie' = do
        tell "Stanga; "
        cauta cheie st
    | otherwise = do
        tell "Dreapta; "
        cauta cheie dr
