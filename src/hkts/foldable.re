open Higher;

/* class Foldable (t :: * -> *) where */
/*   Data.Foldable.foldr' :: (a -> b -> b) -> b -> t a -> b */
/*   Data.Foldable.foldl' :: (b -> a -> b) -> b -> t a -> b */
/*   foldr1 :: (a -> a -> a) -> t a -> a */
/*   foldl1 :: (a -> a -> a) -> t a -> a */

/*   foldMap :: Monoid m => (a -> m) -> t a -> m */
/*   elem :: Eq a => a -> t a -> Bool */
/*   maximum :: Ord a => t a -> a */
/*   minimum :: Ord a => t a -> a */
/*   sum :: Num a => t a -> a */
/*   product :: Num a => t a -> a */
/*   Data.Foldable.fold :: Monoid m => t m -> m */


class virtual foldable_ ('f) = {
  as self; /* minimal interface */
  pub virtual foldr: 'a 'b .(('a, 'b) => 'b, 'b, app('a, 'f)) => 'b; /* can override */
  pub virtual foldl: 'a 'b .(('b, 'a) => 'b, 'b, app('a, 'f)) => 'b;
  pub foldl = (g) => self#foldr((a, b) => g(b, a));
  pub virtual null: 'a .app('a, 'f) => bool;
  pub null = self#foldr((_, _) => true, false);
  pub virtual toList: 'a .app('a, 'f) => list('a);
  pub toList = self#foldr((a, b) => [a, ...b], []);
  pub virtual length: 'a .app('a, 'f) => int;
  pub length = self#foldr((_, b) => 1 + b, 0);
};