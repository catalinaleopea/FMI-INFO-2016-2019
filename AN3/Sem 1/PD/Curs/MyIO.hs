module MyIO(MyIO, myPutChar, myGetChar, convert) where

import Data.Char

type Input = String
type Output = String

newtype MyIO a =
  MyIO { runMyIO :: Input -> (a, Input, Output) }

myPutChar :: Char -> MyIO ()
myPutChar c = MyIO (\ input -> ((), input, [c]))

myGetChar :: MyIO Char
myGetChar = MyIO (\ (ch:input') -> (ch, input', ""))

runIO command input = third (runMyIO command input)
                      where third (_, _, x) = x
                      

myPutStr = foldr (>>) (return ()) . map myPutChar


myPutStrLn s = myPutStr s >> myPutChar '\n'       

myGetLine = do
    x <- myGetChar
    if  x == '\n'
      then return []
      else do
        xs <- myGetLine
        return (x:xs)

echo1 = do {x<- myGetChar ; myPutChar x}
 
echo2 =  do {x<- myGetLine ; myPutStrLn x}    

echo = do
   line <- myGetLine
   if line == ""
     then return ()
     else do
       myPutStrLn (map toUpper line)
       echo    

convert :: MyIO () -> IO ()
convert = interact . runIO
--convert m = interact (\ input ->
--                let ((), _, output) = runMyIO m input
--                 in output)

instance Monad MyIO where
  return x = MyIO $ \ input -> (x, input, "")
  m >>= k  = MyIO $ \ input ->
    let (x, inputx, outputx) = runMyIO m input
        (y, inputy, outputy) = runMyIO (k x) inputx
     in (y, inputy, outputx ++ outputy)

instance Applicative MyIO where
  pure      = return
  mf <*> ma = do
      f <- mf
      a <- ma
      return (f a)

instance Functor MyIO where
  fmap f ma = do  --    ma >>= return . f
      a <- ma
      return (f a)
